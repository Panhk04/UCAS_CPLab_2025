#include "ASTtoIRVisitor.h"
#include "antlr4-runtime.h"
#include "llvm/IR/Verifier.h" // For verifying functions
#include <iostream>
#include <numeric> // For std::accumulate

// Constructor
ASTtoIRVisitor::ASTtoIRVisitor(IRCodeGenerator& generator, GlobalBlock* gb,
                               std::map<antlr4::tree::ParseTree*, BlockInfo*>& contextToScopeMap)
    : irGen(generator), builder(generator.getContext()), globalSymbolTable(gb),
      currentSymbolScope(gb), // Start with global scope
      currentFunctionSymInfo(nullptr), scopeMap(contextToScopeMap) {}

// Helper to convert your DataType to LLVM Type
llvm::Type* ASTtoIRVisitor::getLLVMTypeFromDataType(DataType dt, const std::vector<int>& arrayDimensions, bool isFuncParam) {
    llvm::Type* baseType = nullptr;
    llvm::LLVMContext& context = irGen.getContext();
    switch (dt) {
        case DataType::INT:    baseType = llvm::Type::getInt32Ty(context); break;
        case DataType::FLOAT:  baseType = llvm::Type::getFloatTy(context); break;
        // case DataType::DOUBLE: baseType = llvm::Type::getDoubleTy(context); break; // If you have double
        case DataType::VOID:   baseType = llvm::Type::getVoidTy(context); break;
        case DataType::BOOL:   baseType = llvm::Type::getInt1Ty(context); break; // LLVM uses i1 for bool
        default:
            std::cerr << "Unsupported DataType for LLVM conversion: " << static_cast<int>(dt) << std::endl;
            return nullptr;
    }

    if (!arrayDimensions.empty() && baseType) {
        if (isFuncParam && !arrayDimensions.empty()) {
            // For function parameters, arrays are often passed as pointers.
            // Especially if the first dimension is unsized (represented by 0 or missing in SemanticAnalyzer)
            // Example: int arr[] or int arr[][10] -> int* or int (*)[10]
            // This logic needs to align with how SemanticAnalyzer stores array param dimensions.
            // If arrayDimensions[0] is a placeholder for "any size", it's a pointer.
            llvm::Type* elementType = baseType;
            for (size_t i = arrayDimensions.size() -1 ; i > 0; --i) { // Build inner dimensions if any
                 if(arrayDimensions[i] > 0) elementType = llvm::ArrayType::get(elementType, arrayDimensions[i]);
                 else { /* error or specific handling */ }
            }
            return elementType->getPointerTo();
        } else {
            llvm::Type* currentType = baseType;
            for (auto it = arrayDimensions.rbegin(); it != arrayDimensions.rend(); ++it) {
                if (*it > 0) {
                    currentType = llvm::ArrayType::get(currentType, *it);
                } else {
                    std::cerr << "Error: Non-positive array dimension for non-param: " << *it << std::endl;
                    return nullptr; // Or handle as incomplete type if appropriate
                }
            }
            return currentType;
        }
    }
    return baseType;
}

llvm::Value* ASTtoIRVisitor::getSymbolAddress(const std::string& name) {
    llvm::Value* val = irGen.getNamedValue(name); // Check local LLVM value map first
    if (val) return val;

    // If not in LLVM map, it might be a global or needs to be looked up via symbol table
    // This part is more for ensuring consistency, actual address should be in irGen.namedValues
    // after declaration processing.
    if (currentSymbolScope) {
        SymbolInfo* symInfo = currentSymbolScope->lookUpSymbol(name);
        if (symInfo) {
            // This implies we'd need to map SymbolInfo back to an llvm::Value* if not already done.
            // Generally, after visitVarDef/ConstDef, the llvm::Value* (AllocaInst or GlobalVariable)
            // should be in irGen.namedValues.
             std::cerr << "Symbol " << name << " found in symbol table but not in irGen.namedValues." << std::endl;
        }
    }
    return nullptr;
}

llvm::Constant* ASTtoIRVisitor::getConstSymbolValue(const std::string& name) {
    if (currentSymbolScope) {
        SymbolInfo* symInfo = currentSymbolScope->lookUpSymbol(name);
        if (symInfo && (symInfo->getSymbolType() == SymbolType::CONST || symInfo->getSymbolType() == SymbolType::CONST_ARRAY)) {
            // If it's a simple const, its value might be stored directly or need to be generated.
            // The semantic analyzer stores initial values as strings. We need to parse them.
            // For this example, let's assume namedValues stores the llvm::Constant for consts.
            llvm::Value* val = irGen.getNamedValue(name);
            if (llvm::Constant* constVal = llvm::dyn_cast_or_null<llvm::Constant>(val)) {
                return constVal;
            }
            // If not directly a constant, but an address of a global constant:
            if (llvm::GlobalVariable* GV = llvm::dyn_cast_or_null<llvm::GlobalVariable>(val)) {
                if (GV->isConstant() && GV->hasInitializer()) {
                    return GV->getInitializer();
                }
            }

            // Fallback: try to parse from SymbolInfo if it stores the value directly
            // This part depends heavily on how SymbolInfo stores constant values.
            // Assuming SymbolInfo has a method like getConstantValueAsLLVM()
            // For now, we rely on irGen.namedValues having the llvm::Constant.
            if (symInfo->getInitValue().size() == 1) { // Simple constant
                // This is a simplification. You need a robust way to get the const value.
                // The semantic analyzer stores it as a string.
                // For an integer constant:
                if (symInfo->getDataType() == DataType::INT) {
                    try {
                        int intVal = std::stoi(symInfo->getInitValue()[0]); // Assuming first init value is the one
                         return llvm::ConstantInt::get(irGen.getContext(), llvm::APInt(32, intVal, true));
                    } catch (const std::exception& e) {
                        std::cerr << "Failed to parse const int: " << symInfo->getInitValue()[0] << std::endl;
                    }
                }
                // Add for FLOAT etc.
            }
        }
    }
    std::cerr << "Could not retrieve constant value for: " << name << std::endl;
    return nullptr;
}


std::any ASTtoIRVisitor::visitCompUnit(HelloParser::CompUnitContext *ctx) {
    // Set initial scope to global
    auto it = scopeMap.find(ctx);
    if (it != scopeMap.end()) {
        currentSymbolScope = it->second;
    } else {
        currentSymbolScope = globalSymbolTable; // Fallback or error
        std::cerr << "Warning: No specific scope found for CompUnit, using global." << std::endl;
    }

    for (auto declOrFunc : ctx->declOrFunc()) {
        // In SemanticAnalyzer, declOrFunc is not a rule, but a choice in CompUnit.
        // CompUnit -> (Decl | FuncDef)*
        // So, we iterate through actual Decls and FuncDefs.
        if (declOrFunc->decl())
            visitDecl(declOrFunc->decl());
        else if (declOrFunc->funcDef())
            visitFuncDef(declOrFunc->funcDef());
    }
    return nullptr;
}

std::any ASTtoIRVisitor::visitDecl(HelloParser::DeclContext *ctx) {
    if (ctx->constDecl()) {
        return visitConstDecl(ctx->constDecl());
    } else if (ctx->varDecl()) {
        return visitVarDecl(ctx->varDecl());
    }
    return nullptr;
}

std::any ASTtoIRVisitor::visitFuncDef(HelloParser::FuncDefContext *ctx) {
    std::string funcName = ctx->Ident()->getText();
    FuncInfo* funcSymInfo = globalSymbolTable->lookUpFunc(funcName);

    if (!funcSymInfo) {
        std::cerr << "Error: Function " << funcName << " not found in symbol table." << std::endl;
        return static_cast<llvm::Value*>(nullptr);
    }
    currentFunctionSymInfo = funcSymInfo; // Store for use in return statements etc.

    // Get return type
    llvm::Type *returnType = getLLVMTypeFromDataType(funcSymInfo->getDataType());

    // Get parameter types
    std::vector<llvm::Type*> paramTypes;
    const auto& paramsSymbolInfo = funcSymInfo->getParams(); // Assuming FuncInfo has getParams() -> vector<SymbolInfo*>
    for (const auto& paramSym : paramsSymbolInfo) {
        paramTypes.push_back(getLLVMTypeFromDataType(paramSym->getDataType(), paramSym->getArraySize(), true));
    }

    llvm::Function *func = irGen.createFunction(funcName, returnType, paramTypes);
    // irGen.setCurrentFunction(func); // createFunction might do this already

    // Set names for all arguments.
    unsigned idx = 0;
    for (auto &arg : func->args()) {
        if (idx < paramsSymbolInfo.size()) {
            arg.setName(paramsSymbolInfo[idx++]->getName());
        } else {
            arg.setName("arg" + std::to_string(idx++)); // Fallback name
        }
    }

    // Create entry basic block
    llvm::BasicBlock *entryBlock = irGen.createBasicBlock("entry", func);
    builder.SetInsertPoint(entryBlock);

    // Allocate space for parameters and store their initial values
    idx = 0;
    for (auto &arg : func->args()) {
        if (idx < paramsSymbolInfo.size()) {
            SymbolInfo* paramSym = paramsSymbolInfo[idx];
            llvm::AllocaInst *alloca = builder.CreateAlloca(arg.getType(), nullptr, paramSym->getName() + ".addr");
            builder.CreateStore(&arg, alloca);
            irGen.setNamedValue(paramSym->getName(), alloca); // Store address of param
        }
        idx++;
    }
    
    BlockInfo* oldScope = currentSymbolScope;
    auto it = scopeMap.find(ctx->block()); // The block of the function
    if (it != scopeMap.end()) {
        currentSymbolScope = it->second;
    } else {
        // Fallback: FuncInfo might point to its main BlockInfo
        // currentSymbolScope = funcSymInfo->getEntryBlockInfo(); // Hypothetical
        std::cerr << "Warning: Scope for function " << funcName << " body not found in map." << std::endl;
    }

    visitBlock(ctx->block());

    // Ensure terminator for the last block if not already present (e.g. void func with no return)
    if (returnType->isVoidTy()) {
        if (!builder.GetInsertBlock()->getTerminator()) {
            builder.CreateRetVoid();
        }
    } else {
         // For non-void functions, all paths should ideally have a return.
         // LLVM's verifier will catch functions missing returns on some paths.
         // If the current insert block (likely the last one) doesn't have a terminator,
         // it's often an error in the source or IR generation for that path.
         // Adding a default return here can hide source errors.
        if (!builder.GetInsertBlock()->getTerminator()) {
             std::cerr << "Warning: Non-void function " << funcName << " might be missing a return statement on some path." << std::endl;
             if (returnType->isIntegerTy())
                builder.CreateRet(llvm::ConstantInt::get(returnType, 0, true));
             else if (returnType->isFloatingPointTy())
                builder.CreateRet(llvm::ConstantFP::get(returnType, 0.0));
             else
                // Cannot create a sensible default for other types easily
                std::cerr << "Error: Cannot create default return for type of function " << funcName << std::endl;

        }
    }
    
    currentSymbolScope = oldScope;
    currentFunctionSymInfo = nullptr; // Reset
    
    if (llvm::verifyFunction(*func, &llvm::errs())) {
        std::cerr << "LLVM Function Verification Failed for: " << funcName << std::endl;
        // func->print(llvm::errs()); // Print the problematic function
    }

    return static_cast<llvm::Value*>(func);
}

std::any ASTtoIRVisitor::visitVarDecl(HelloParser::VarDeclContext *ctx) {
    // DataType is set on VarDef by SemanticAnalyzer
    for (auto varDefCtx : ctx->varDef()) {
        // The SemanticAnalyzer should have set varDefCtx->dataType
        // If not, we'd need to get it from ctx->btype() and pass it down.
        // SymbolInfo* sym = currentSymbolScope->lookUpSymbol(varDefCtx->Ident()->getText());
        // DataType dt = sym->getDataType(); // More robust
        visitVarDef(varDefCtx);
    }
    return nullptr;
}

std::any ASTtoIRVisitor::visitVarDef(HelloParser::VarDefContext *ctx) {
    std::string varName = ctx->Ident()->getText();
    SymbolInfo* symInfo = currentSymbolScope->lookUpSymbol(varName);

    if (!symInfo) {
        std::cerr << "Error: Variable " << varName << " not found in symbol table." << std::endl;
        return static_cast<llvm::Value*>(nullptr);
    }

    llvm::Type* varLLVMType = getLLVMTypeFromDataType(symInfo->getDataType(), symInfo->getArraySize());
    if (!varLLVMType) return static_cast<llvm::Value*>(nullptr);

    llvm::Value* varAllocation;

    if (currentFunctionSymInfo) { // Local variable
        // Create alloca in the entry block of the function for SSA
        llvm::Function* llvmFunc = irGen.getModule().getFunction(currentFunctionSymInfo->getName());
        llvm::IRBuilder<> entryBuilder(&llvmFunc->getEntryBlock(), llvmFunc->getEntryBlock().begin());
        varAllocation = entryBuilder.CreateAlloca(varLLVMType, nullptr, varName);
    } else { // Global variable
        llvm::Constant* initializer = nullptr;
        if (symInfo->getArraySize().empty() && varLLVMType->isSingleValueType()) { // Not an array
             initializer = llvm::Constant::getNullValue(varLLVMType); // Default init to zero/null
        } else if (varLLVMType->isArrayTy()){
            // For global arrays, they are zero-initialized by default if no explicit initializer
            initializer = llvm::ConstantAggregateZero::get(varLLVMType);
        } else {
             std::cerr << "Cannot determine default initializer for global " << varName << std::endl;
             return static_cast<llvm::Value*>(nullptr);
        }
        
        // If there's an explicit initializer in VarDef for a global
        if (ctx->constInitVal()) { // Note: VarDef uses ConstInitVal in your grammar for init
            // Global variable initializers must be constant expressions.
            // visitConstInitVal should return an llvm::Constant.
            llvm::Value* initVal = std::any_cast<llvm::Value*>(visitConstInitVal(ctx->constInitVal()));
            if (auto constInit = llvm::dyn_cast_or_null<llvm::Constant>(initVal)) {
                initializer = constInit;
            } else {
                std::cerr << "Error: Global variable " << varName << " initializer is not constant." << std::endl;
                // Fallback to default or error
            }
        }

        varAllocation = new llvm::GlobalVariable(
            irGen.getModule(), varLLVMType, false, // false for isConstant (vars are mutable)
            llvm::GlobalValue::ExternalLinkage, // Or other linkage
            initializer,
            varName
        );
    }
    irGen.setNamedValue(varName, varAllocation); // Store address

    // Handle local variable initialization if not global and has initializer
    if (currentFunctionSymInfo && ctx->constInitVal()) {
        llvm::Value* initVal = std::any_cast<llvm::Value*>(visit(ctx->constInitVal())); // visitConstInitVal or visitInitVal
        if (initVal) {
            builder.CreateStore(initVal, varAllocation);
        } else {
            // Default initialize if needed (e.g. to zero), though C/C++ doesn't always do this for locals
            // builder.CreateStore(llvm::Constant::getNullValue(varLLVMType), varAllocation);
        }
    } else if (currentFunctionSymInfo && !ctx->constInitVal() && symInfo->getArraySize().empty()) {
        // Optional: Default initialize local scalar variables if your language requires
        // builder.CreateStore(llvm::Constant::getNullValue(varLLVMType), varAllocation);
    }


    return varAllocation;
}


std::any ASTtoIRVisitor::visitConstDecl(HelloParser::ConstDeclContext *ctx) {
    for (auto constDefCtx : ctx->constDef()) {
        visitConstDef(constDefCtx);
    }
    return nullptr;
}

std::any ASTtoIRVisitor::visitConstDef(HelloParser::ConstDefContext *ctx) {
    std::string constName = ctx->Ident()->getText();
    SymbolInfo* symInfo = currentSymbolScope->lookUpSymbol(constName);

    if (!symInfo) {
        std::cerr << "Error: Constant " << constName << " not found in symbol table." << std::endl;
        return static_cast<llvm::Value*>(nullptr);
    }

    llvm::Value* constLLVMVal = std::any_cast<llvm::Value*>(visitConstInitVal(ctx->constInitVal()));
    llvm::Constant* llvmConstant = llvm::dyn_cast_or_null<llvm::Constant>(constLLVMVal);

    if (!llvmConstant) {
        std::cerr << "Error: Initializer for const " << constName << " is not an LLVM constant." << std::endl;
        return static_cast<llvm::Value*>(nullptr);
    }
    
    // For constants, we can store the llvm::Constant directly in namedValues if it's simple.
    // Or, for global constants, create a GlobalVariable marked as constant.
    if (!currentFunctionSymInfo) { // Global constant
        llvm::Type* constLLVMType = getLLVMTypeFromDataType(symInfo->getDataType(), symInfo->getArraySize());
        if (!constLLVMType) return static_cast<llvm::Value*>(nullptr);

        // Ensure the initializer's type matches the symbol's declared type
        if (llvmConstant->getType() != constLLVMType) {
            // This might happen if e.g. an integer constant is assigned to a float const without explicit cast
            // Or array initializers. For arrays, visitConstInitVal needs to build ConstantArray/ConstantDataArray
            std::cerr << "Warning: Constant " << constName << " initializer type mismatch. Declared: ";
            // constLLVMType->print(llvm::errs());
            std::cerr << " Initializer: ";
            // llvmConstant->getType()->print(llvm::errs());
            std::cerr << std::endl;
            // Attempt to fix or error out. For now, we proceed, but this is a potential issue.
        }


        llvm::GlobalVariable* gv = new llvm::GlobalVariable(
            irGen.getModule(),
            llvmConstant->getType(), // Use type from initializer, should match declared type
            true, // isConstant = true
            llvm::GlobalValue::PrivateLinkage, // Or appropriate linkage
            llvmConstant,
            constName
        );
        irGen.setNamedValue(constName, gv); // Store address of global constant
        return static_cast<llvm::Value*>(gv);
    } else {
        // Local constants: LLVM doesn't have a direct "local constant" variable in the same way.
        // Their values are often directly embedded (if used as rvalue).
        // If you need an address (e.g. const int x = 5; int* p = &x;), then you need an alloca.
        // For now, store the llvm::Constant itself. If an address is taken, it's more complex.
        irGen.setNamedValue(constName, llvmConstant);
        return llvmConstant;
    }
}


std::any ASTtoIRVisitor::visitConstInitVal(HelloParser::ConstInitValContext *ctx) {
    // ConstInitVal -> ConstExp | '{' ( ConstInitVal ( ',' ConstInitVal )* )? '}'
    if (ctx->constExp()) {
        // ConstExp should evaluate to a compile-time constant.
        // The visit method for ConstExp needs to return an llvm::Constant.
        return visitConstExp(ctx->constExp());
    } else { // Array initializer: '{ ... }'
        std::vector<llvm::Constant*> elements;
        SymbolInfo* currentSymbolForInit = nullptr; // Need to know which symbol this init is for, to get type
        // This is tricky: ConstInitVal doesn't know its parent ConstDef/VarDef directly.
        // The caller (visitConstDef/VarDef) should pass type information.
        // For now, let's assume we can get the element type.
        // This part needs the expected array type to correctly build llvm::ConstantArray.
        // Let's assume the current symbol being initialized is somehow known, or type is passed.
        // This is a placeholder for robust array init.
        std::cerr << "Array constant initializer IR generation is complex and not fully implemented." << std::endl;
        // You'd iterate ctx->constInitVal(i), recursively call visit, collect llvm::Constant*,
        // then create llvm::ConstantArray::get().
        // For now, returning a dummy value or nullptr.
        // Example: if expecting int array:
        // llvm::Type* elemType = llvm::Type::getInt32Ty(irGen.getContext());
        // for (auto initCtx : ctx->constInitVal()) {
        //    elements.push_back(llvm::dyn_cast<llvm::Constant>(std::any_cast<llvm::Value*>(visitConstInitVal(initCtx))));
        // }
        // llvm::ArrayType* arrayType = llvm::ArrayType::get(elemType, elements.size());
        // return llvm::ConstantArray::get(arrayType, elements);
        return static_cast<llvm::Value*>(nullptr);
    }
}

std::any ASTtoIRVisitor::visitConstExp(HelloParser::ConstExpContext *ctx) {
    // ConstExp -> AddExp (in SysY grammar, AddExp here is actually AddExpConst)
    // This must evaluate to an llvm::Constant.
    // This requires a sub-visitor or logic that only deals with constant folding.
    // For simplicity, if AddExp can return a Constant, we use it.
    // A true const expression evaluator would be separate.
    // Here, we assume visitAddExp (or a specialized visitAddExpConst) can yield an llvm::Constant.
    if (ctx->exp()) { // Assuming your grammar has ConstExp -> Exp
        // The semantic analyzer should ensure this Exp is constant-foldable.
        // The visitExp method, when called for a const context, should try to produce a constant.
        llvm::Value* val = std::any_cast<llvm::Value*>(visitExp(ctx->exp()));
        if (llvm::Constant* C = llvm::dyn_cast<llvm::Constant>(val)) {
            return C;
        }
        std::cerr << "ConstExp did not evaluate to an LLVM constant." << std::endl;
        // Return a dummy constant or handle error
        return static_cast<llvm::Value*>(llvm::ConstantInt::get(llvm::Type::getInt32Ty(irGen.getContext()), 0));
    }
    std::cerr << "Unsupported ConstExp structure." << std::endl;
    return static_cast<llvm::Value*>(llvm::ConstantInt::get(llvm::Type::getInt32Ty(irGen.getContext()), 0));
}


std::any ASTtoIRVisitor::visitBlock(HelloParser::BlockContext *ctx) {
    BlockInfo* outerSymbolScope = currentSymbolScope;
    auto it = scopeMap.find(ctx);
    if (it != scopeMap.end()) {
        currentSymbolScope = it->second;
    } else {
        // This block might not introduce a new named scope in the symbol table
        // if it's just a compound statement not at function/file level.
        // Or, if it does, and it's not in the map, it's a problem for finding its BlockInfo.
        // std::cerr << "Warning: Scope for a BlockContext not found in map." << std::endl;
    }

    for (auto item : ctx->blockItem()) {
        visitBlockItem(item);
    }

    currentSymbolScope = outerSymbolScope; // Restore outer scope
    return nullptr;
}

std::any ASTtoIRVisitor::visitBlockItem(HelloParser::BlockItemContext *ctx) {
    if (ctx->decl()) return visitDecl(ctx->decl());
    else if (ctx->stmt()) return visitStmt(ctx->stmt());
    return nullptr;
}


std::any ASTtoIRVisitor::visitStmt(HelloParser::StmtContext *ctx) {
    // Example for return statement:
    if (ctx->Return()) {
        if (ctx->exp().size() > 0 && ctx->exp(0)) { // Check if exp() is not empty and exp(0) is not null
            llvm::Value *retVal = std::any_cast<llvm::Value*>(visitExp(ctx->exp(0)));
            if (retVal) {
                // Type cast if necessary (e.g. int to float if function returns float)
                // This should ideally be handled by semantic checks or explicit casts in source.
                // For now, assume type compatibility or direct use.
                llvm::Type* funcRetType = builder.getCurrentFunctionReturnType();
                if (retVal->getType() != funcRetType) {
                    // Basic implicit cast for demonstration (e.g. i1 to i32, or int to float)
                    // This is a simplification. Proper casting rules are complex.
                    if (funcRetType->isIntegerTy() && retVal->getType()->isIntegerTy()) {
                         retVal = builder.CreateIntCast(retVal, funcRetType, true, "retcast"); // true for signed
                    } else if (funcRetType->isFloatingPointTy() && retVal->getType()->isFloatingPointTy()) {
                         retVal = builder.CreateFPCast(retVal, funcRetType, "retcast");
                    } else if (funcRetType->isFloatingPointTy() && retVal->getType()->isIntegerTy()) {
                         retVal = builder.CreateSIToFP(retVal, funcRetType, "retcast_sitofp");
                    } else if (funcRetType->isIntegerTy() && retVal->getType()->isFloatingPointTy()) {
                         retVal = builder.CreateFPToSI(retVal, funcRetType, "retcast_fptosi");
                    }
                    // else: types are incompatible for simple implicit cast
                }
                builder.CreateRet(retVal);
            }
        } else {
            builder.CreateRetVoid();
        }
        return nullptr;
    }
    // Example for assignment: LVal '=' Exp ';'
    if (ctx->Assign() && ctx->lVal() && ctx->exp().size() > 0 && ctx->exp(0)) {
        llvm::Value *lvalAddr = std::any_cast<llvm::Value*>(visitLVal(ctx->lVal())); // Should return address
        llvm::Value *valToStore = std::any_cast<llvm::Value*>(visitExp(ctx->exp(0))); // Should return value

        if (!lvalAddr || !valToStore) {
            std::cerr << "Error in assignment: null lval address or value." << std::endl;
            return nullptr;
        }
        
        // Type check / cast if necessary (valToStore to type of lvalAddr points to)
        llvm::Type* lvalPointsToType = nullptr;
        if (auto ptrType = llvm::dyn_cast<llvm::PointerType>(lvalAddr->getType())) {
            lvalPointsToType = ptrType->getElementType();
        } else { // GEP can return non-pointer if all indices are 0 for a scalar global. Unlikely for typical LVal.
            std::cerr << "LVal address is not a pointer type." << std::endl;
            return nullptr;
        }


        if (valToStore->getType() != lvalPointsToType) {
            std::cerr << "Type mismatch in assignment. LHS: "/* << lvalPointsToType->getDescription()*/
                      << " RHS: " /*<< valToStore->getType()->getDescription() */<< ". Attempting cast." << std::endl;
            // Add casting logic similar to return statement if needed.
            // For now, assume types are compatible or semantic analysis ensured this.
            // valToStore = builder.CreateBitCast(valToStore, lvalPointsToType); // Risky without type checks
        }

        builder.CreateStore(valToStore, lvalAddr);
        return nullptr;
    }

    // If it's an expression statement: Exp ';'
    if (ctx->exp().size() > 0 && ctx->exp(0) && !ctx->Assign() && !ctx->Return() /* and other keywords */) {
        visitExp(ctx->exp(0)); // Evaluate for side effects
        return nullptr;
    }
    
    if (ctx->block()) {
        return visitBlock(ctx->block());
    }

    // TODO: Implement other statement types (if, while, etc.)
    // For example, if ( Cond ) Stmt ( else Stmt )?
    // visitCond(ctx->cond()) -> llvm::Value* (i1 type)
    // CreateBasicBlock("then"), CreateBasicBlock("else"), CreateBasicBlock("merge")
    // builder.CreateCondBr(condVal, thenBB, elseBB_or_mergeBB)

    return nullptr;
}

std::any ASTtoIRVisitor::visitLVal(HelloParser::LValContext *ctx) {
    std::string varName = ctx->Ident()->getText();
    SymbolInfo* symInfo = currentSymbolScope->lookUpSymbol(varName);

    if (!symInfo) {
        std::cerr << "Error: LValue " << varName << " not found in symbol table." << std::endl;
        return static_cast<llvm::Value*>(nullptr);
    }

    llvm::Value *varAddr = irGen.getNamedValue(varName); // Get base address (AllocaInst or GlobalVar)
    if (!varAddr) {
         std::cerr << "Error: LLVM Value for LValue " << varName << " not found (should be an address)." << std::endl;
        return static_cast<llvm::Value*>(nullptr);
    }

    // Handle array indexing: LVal -> Ident ('[' Exp ']')*
    if (!ctx->exp().empty()) {
        llvm::Type* currentType = varAddr->getType(); // This is PointerType(ArrayType) or PointerType(PointerType(ElementType)) for params
         if (auto ptrTy = llvm::dyn_cast<llvm::PointerType>(currentType)) {
            currentType = ptrTy->getElementType(); // Get the type pointed to (ArrayType or ElementType for decayed array param)
        } else {
            std::cerr << "LVal base address is not a pointer." << std::endl;
            return nullptr;
        }


        std::vector<llvm::Value *> indices;
        // LLVM GEP needs a first index for the pointer itself, usually 0.
        indices.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(irGen.getContext()), 0));

        for (auto expCtx : ctx->exp()) {
            llvm::Value* idxVal = std::any_cast<llvm::Value*>(visitExp(expCtx));
            if (!idxVal) return static_cast<llvm::Value*>(nullptr);
            // Ensure index is integer, cast if necessary (e.g. i1 to i32)
            if (idxVal->getType() != llvm::Type::getInt32Ty(irGen.getContext())) {
                 if (idxVal->getType()->isIntegerTy()) { // e.g. i1, i8, i64
                    idxVal = builder.CreateIntCast(idxVal, llvm::Type::getInt32Ty(irGen.getContext()), true, "idxcast");
                 } else {
                    std::cerr << "Array index is not an integer type." << std::endl; return nullptr;
                 }
            }
            indices.push_back(idxVal);
        }
        // If varAddr is Ptr(ArrayTy), GEP with [0, idx1, idx2] is fine.
        // If varAddr is Ptr(Ptr(ElementTy)) (array param decayed to pointer), GEP needs careful handling.
        // The type of varAddr (from AllocaInst for param) should be Ptr(ElementTy) if it's a simple array param.
        // Or Ptr(ArrayTy[N-1]) if it's PtrToArray.
        // The getLLVMTypeFromDataType for array parameters needs to be consistent with this.
        // If symInfo->isArray() and it's a parameter, it might be a pointer.
        // If it's a pointer to an array (e.g. int (*p)[10]), GEP is different.
        // Assuming simple array or pointer-to-element for params.
        varAddr = builder.CreateInBoundsGEP(
            //varAddr->getType()->getPointerElementType(), // Type of the allocated thing
            varAddr, // Pointer to the array/first element
            indices,
            varName + ".gep"
        );
    }
    // visitLVal returns the ADDRESS of the l-value (scalar or array element).
    return varAddr;
}

std::any ASTtoIRVisitor::visitExp(HelloParser::ExpContext *ctx) {
    // Exp -> AddExp
    return visitAddExp(ctx->addExp());
}

std::any ASTtoIRVisitor::visitAddExp(HelloParser::AddExpContext *ctx) {
    // AddExp -> MulExp ( ( '+' | '-' ) MulExp )*
    // Determine type from semantic analysis if possible, e.g. by looking at first MulExp's type
    // For simplicity, assume all operands will be compatible or cast appropriately.

    llvm::Value *lhs = std::any_cast<llvm::Value*>(visitMulExp(ctx->mulExp(0)));
    if (!lhs) return static_cast<llvm::Value*>(nullptr);

    for (size_t i = 0; i < ctx->op.size(); ++i) { // op is a list of tokens (+ or -)
        llvm::Value *rhs = std::any_cast<llvm::Value*>(visitMulExp(ctx->mulExp(i + 1)));
        if (!rhs) return static_cast<llvm::Value*>(nullptr);

        // Type promotion/checking (e.g. int + float -> float)
        // For now, assume types are compatible or use type of LHS.
        // A real compiler would implement numeric promotion rules.
        // Example: if lhs is float, rhs int -> cast rhs to float.
        // if (lhs->getType()->isFloatTy() && rhs->getType()->isIntegerTy()) {
        //    rhs = builder.CreateSIToFP(rhs, lhs->getType(), "sitofp_tmp");
        // } else if (lhs->getType()->isIntegerTy() && rhs->getType()->isFloatTy()) {
        //    lhs = builder.CreateSIToFP(lhs, rhs->getType(), "sitofp_tmp");
        // } // etc.

        if (ctx->op[i]->getType() == HelloLexer::ADD) {
            if (lhs->getType()->isFloatingPointTy())
                lhs = builder.CreateFAdd(lhs, rhs, "addtmp");
            else // Assuming integer otherwise
                lhs = builder.CreateAdd(lhs, rhs, "addtmp");
        } else if (ctx->op[i]->getType() == HelloLexer::SUB) {
             if (lhs->getType()->isFloatingPointTy())
                lhs = builder.CreateFSub(lhs, rhs, "subtmp");
            else
                lhs = builder.CreateSub(lhs, rhs, "subtmp");
        }
    }
    return lhs;
}

std::any ASTtoIRVisitor::visitMulExp(HelloParser::MulExpContext *ctx) {
    // MulExp -> UnaryExp ( ( '*' | '/' | '%' ) UnaryExp )*
    llvm::Value *lhs = std::any_cast<llvm::Value*>(visitUnaryExp(ctx->unaryExp(0)));
     if (!lhs) return static_cast<llvm::Value*>(nullptr);

    for (size_t i = 0; i < ctx->op.size(); ++i) {
        llvm::Value *rhs = std::any_cast<llvm::Value*>(visitUnaryExp(ctx->unaryExp(i + 1)));
        if (!rhs) return static_cast<llvm::Value*>(nullptr);
        // Similar type promotion/checking as AddExp

        if (ctx->op[i]->getType() == HelloLexer::MUL) {
            if (lhs->getType()->isFloatingPointTy())
                lhs = builder.CreateFMul(lhs, rhs, "multmp");
            else
                lhs = builder.CreateMul(lhs, rhs, "multmp");
        } else if (ctx->op[i]->getType() == HelloLexer::DIV) {
            if (lhs->getType()->isFloatingPointTy())
                lhs = builder.CreateFDiv(lhs, rhs, "divtmp");
            else // Assuming signed integer division
                lhs = builder.CreateSDiv(lhs, rhs, "divtmp");
        } else if (ctx->op[i]->getType() == HelloLexer::MOD) {
            // Modulo typically for integers. LLVM has SRem (signed) and URem (unsigned).
            if (lhs->getType()->isFloatingPointTy()) {
                 std::cerr << "Modulo operator not standard for floats, using fmod." << std::endl;
                 // lhs = builder.CreateFRem(lhs, rhs, "modtmp"); // Or call fmod intrinsic/library function
            } else
                lhs = builder.CreateSRem(lhs, rhs, "modtmp");
        }
    }
    return lhs;
}

std::any ASTtoIRVisitor::visitUnaryExp(HelloParser::UnaryExpContext *ctx) {
    // UnaryExp -> PrimaryExp | Ident '(' FuncRParams? ')' | UnaryOp UnaryExp
    if (ctx->primaryExp()) {
        return visitPrimaryExp(ctx->primaryExp());
    } else if (ctx->Ident()) { // Function call
        std::string funcName = ctx->Ident()->getText();
        FuncInfo* funcSymInfo = globalSymbolTable->lookUpFunc(funcName);
        if (!funcSymInfo) {
            std::cerr << "Error: Function " << funcName << " not found for call." << std::endl;
            return static_cast<llvm::Value*>(nullptr);
        }
        llvm::Function *calleeFunc = irGen.getModule().getFunction(funcName);
        if (!calleeFunc) {
            std::cerr << "Error: LLVM Function " << funcName << " not found for call." << std::endl;
            return static_cast<llvm::Value*>(nullptr);
        }

        std::vector<llvm::Value *> argsV;
        if (ctx->funcRParams()) {
            for (auto expCtx : ctx->funcRParams()->exp()) {
                argsV.push_back(std::any_cast<llvm::Value*>(visitExp(expCtx)));
            }
        }
        // TODO: Check arg count and types against calleeFunc->getFunctionType() or funcSymInfo
        if (argsV.size() != calleeFunc->arg_size()) {
             std::cerr << "Error: Argument count mismatch for function " << funcName << std::endl;
             // return nullptr;
        }
        // Parameter type casting if needed
        for(unsigned i=0; i < argsV.size() && i < calleeFunc->arg_size(); ++i) {
            llvm::Type* expectedType = calleeFunc->getFunctionType()->getParamType(i);
            if (argsV[i]->getType() != expectedType) {
                // Basic implicit cast logic (similar to return)
                // This should be more robust, guided by language rules & semantic analysis
                if (expectedType->isIntegerTy() && argsV[i]->getType()->isIntegerTy()) {
                     argsV[i] = builder.CreateIntCast(argsV[i], expectedType, true, "argcast");
                } else if (expectedType->isFloatingPointTy() && argsV[i]->getType()->isFloatingPointTy()) {
                     argsV[i] = builder.CreateFPCast(argsV[i], expectedType, "argcast");
                } else if (expectedType->isFloatingPointTy() && argsV[i]->getType()->isIntegerTy()) {
                     argsV[i] = builder.CreateSIToFP(argsV[i], expectedType, "argcast_sitofp");
                } else if (expectedType->isIntegerTy() && argsV[i]->getType()->isFloatingPointTy()) {
                     argsV[i] = builder.CreateFPToSI(argsV[i], expectedType, "argcast_fptosi");
                } else if (expectedType->isPointerTy() && argsV[i]->getType()->isPointerTy()) {
                    if (expectedType != argsV[i]->getType()) // Pointer type mismatch
                        argsV[i] = builder.CreatePointerCast(argsV[i], expectedType, "argptr_cast");
                } else {
                    std::cerr << "Warning: Argument type mismatch for param " << i << " of " << funcName << std::endl;
                }
            }
        }


        if (calleeFunc->getReturnType()->isVoidTy()) {
            return builder.CreateCall(calleeFunc, argsV);
        }
        return builder.CreateCall(calleeFunc, argsV, "calltmp");

    } else if (ctx->unaryOp()) {
        llvm::Value* operand = std::any_cast<llvm::Value*>(visitUnaryExp(ctx->unaryExp(0))); // Recursive call
        if (!operand) return static_cast<llvm::Value*>(nullptr);
        std::string op = ctx->unaryOp()->getText();
        if (op == "+") return operand; // Unary plus is a no-op
        if (op == "-") {
            if (operand->getType()->isFloatingPointTy())
                return builder.CreateFNeg(operand, "negtmp");
            else // Assuming integer
                return builder.CreateNeg(operand, "negtmp");
        }
        if (op == "!") { // Logical NOT
            // Assuming operand is bool (i1) or can be compared to zero for other types
            if (operand->getType()->isIntegerTy(1)) { // Already i1
                 return builder.CreateNot(operand, "nottmp"); // Bitwise NOT on i1 is logical NOT
            } else if (operand->getType()->isIntegerTy()) { // e.g. i32
                 return builder.CreateICmpEQ(operand, llvm::ConstantInt::get(operand->getType(), 0), "nottmp");
            } else if (operand->getType()->isFloatingPointTy()) {
                 return builder.CreateFCmpOEQ(operand, llvm::ConstantFP::get(operand->getType(), 0.0), "nottmp");
            }
        }
    }
    return static_cast<llvm::Value*>(nullptr);
}


std::any ASTtoIRVisitor::visitPrimaryExp(HelloParser::PrimaryExpContext *ctx) {
    if (ctx->exp()) { // '(' Exp ')'
        return visitExp(ctx->exp());
    } else if (ctx->number()) {
        return visitNumber(ctx->number());
    } else if (ctx->lVal()) {
        // LVal used as RValue: visitLVal returns address, then we load.
        llvm::Value* varAddr = std::any_cast<llvm::Value*>(visitLVal(ctx->lVal()));
        if (!varAddr) return static_cast<llvm::Value*>(nullptr);

        // If varAddr is a direct llvm::Constant (e.g. a local const not allocated), return it.
        if (llvm::Constant* C = llvm::dyn_cast<llvm::Constant>(varAddr)) {
            // This case happens if visitLVal for a const identifier returns the constant itself.
            // However, visitLVal is designed to return an address.
            // This path is more for when a const symbol is directly used as r-value.
            // Let's assume visitLVal always returns an address for now.
        }
        
        // Determine the type to load. varAddr is PtrToSomeType. We need SomeType.
        llvm::Type* pointedType = nullptr;
        if(auto ptrT = llvm::dyn_cast<llvm::PointerType>(varAddr->getType())) {
            pointedType = ptrT->getElementType();
        } else {
            std::cerr << "PrimaryExp LVal address is not a pointer type." << std::endl;
            return static_cast<llvm::Value*>(nullptr);
        }

        // If LVal refers to an array or function, loading it directly might not be what's intended
        // (it would decay to a pointer or be an error).
        // Semantic analysis should clarify this. For now, assume it's a loadable scalar/element.
        if (pointedType->isArrayTy() || pointedType->isFunctionTy()) {
            // Decaying array to pointer: GEP with [0,0] to get pointer to first element.
            // This is often implicit. If we return varAddr directly, it's already the pointer to the array.
            // For function pointers, this is also different.
            // For now, if it's an array type, we are likely passing it as a pointer.
            // The GEP in visitLVal should have already produced a PtrToElement if indexed.
            // If it's an un-indexed array LVal, varAddr is PtrToArray.
            // To use it as a pointer (e.g. pass to function), this address is fine.
            // If we are trying to "load" an array, that's not a single operation.
            // Let's assume if we reach here with an array type, we want the pointer to its first element.
            if (pointedType->isArrayTy()){
                 std::vector<llvm::Value *> indices;
                 indices.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(irGen.getContext()), 0));
                 indices.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(irGen.getContext()), 0)); // First element
                 return builder.CreateInBoundsGEP(varAddr, indices, "arraydecay");
            }
            // For function type, it means taking address of function, varAddr should be it.
            return varAddr;
        }
        return builder.CreateLoad(pointedType, varAddr, "loadtmp");
    }
    return static_cast<llvm::Value*>(nullptr);
}

std::any ASTtoIRVisitor::visitNumber(HelloParser::NumberContext *ctx) {
    // SemanticAnalyzer's visitNumber returns ReturnValue(DataType, ...)
    // We need to know the DataType to create the correct LLVM constant.
    // Let's assume the text itself implies type for now, or use a fixed type.
    // A better way: get DataType from SemanticAnalyzer's ReturnValue for this node.
    // For now, infer from text or default to int.
    std::string numText = ctx->getText();
    if (ctx->IntConst()) { // Assuming IntConst means integer
        long long val = 0;
        if (numText.rfind("0x", 0) == 0 || numText.rfind("0X", 0) == 0) {
            val = std::stoll(numText.substr(2), nullptr, 16);
        } else if (numText.length() > 1 && numText[0] == '0' && !(numText[1] == 'x' || numText[1] == 'X')) {
             if (numText.find_first_not_of("01234567", 1) == std::string::npos) // Check if octal
                val = std::stoll(numText.substr(1), nullptr, 8);
             else // Decimal starting with 0 but not octal (e.g. "0", "09")
                val = std::stoll(numText, nullptr, 10);
        }else {
            val = std::stoll(numText, nullptr, 10);
        }
        return static_cast<llvm::Value*>(llvm::ConstantInt::get(irGen.getContext(), llvm::APInt(32, val, true))); // Assuming i32
    } else if (ctx->FloatConst()) { // Assuming FloatConst means floating point
        double val = std::stod(numText);
        // Distinguish float vs double based on 'f' suffix or language default
        // bool isFloat = (numText.back() == 'f' || numText.back() == 'F');
        // For now, default to double, then cast if context needs float. Or use float if 'f'.
        // DataType typeFromSemantic = ... ; // Get this from semantic analysis if possible
        // if (typeFromSemantic == DataType::FLOAT) return llvm::ConstantFP::get(irGen.getContext(), llvm::APFloat((float)val));
        return static_cast<llvm::Value*>(llvm::ConstantFP::get(irGen.getContext(), llvm::APFloat(val))); // Default to double
    }
    return static_cast<llvm::Value*>(nullptr);
}


// Implement other necessary visit methods from HelloVisitor.h as stubs or full implementations
std::any ASTtoIRVisitor::visitBtype(HelloParser::BtypeContext *context) { return nullptr; }
std::any ASTtoIRVisitor::visitFuncType(HelloParser::FuncTypeContext *context) { return nullptr; } // Handled in FuncDef
std::any ASTtoIRVisitor::visitFuncFParams(HelloParser::FuncFParamsContext *context) { return nullptr; } // Handled in FuncDef
std::any ASTtoIRVisitor::visitFuncFParam(HelloParser::FuncFParamContext *context) { return nullptr; } // Handled in FuncDef
// ... many more ...
std::any ASTtoIRVisitor::visitAddExpConst(HelloParser::AddExpConstContext *context) { /* similar to AddExp but ensure const result */ return nullptr; }
std::any ASTtoIRVisitor::visitMulExpConst(HelloParser::MulExpConstContext *context) { /* similar to MulExp but ensure const result */ return nullptr; }
std::any ASTtoIRVisitor::visitUnaryExpConst(HelloParser::UnaryExpConstContext *context) { /* similar to UnaryExp but ensure const result */ return nullptr; }
std::any ASTtoIRVisitor::visitPrimaryExpConst(HelloParser::PrimaryExpConstContext *context) { /* similar to PrimaryExp but ensure const result */ return nullptr; }
std::any ASTtoIRVisitor::visitCond(HelloParser::CondContext *context) {
    // Cond -> LOrExp
    // Should result in an i1 value
    llvm::Value* condVal = std::any_cast<llvm::Value*>(visitLOrExp(context->lOrExp()));
    if (!condVal) return nullptr;

    if (condVal->getType()->isIntegerTy(1)) { // Already i1
        return condVal;
    } else if (condVal->getType()->isIntegerTy()) { // Other integer types, compare with 0
        return builder.CreateICmpNE(condVal, llvm::ConstantInt::get(condVal->getType(), 0), "cond_to_bool");
    } else if (condVal->getType()->isFloatingPointTy()) {
        return builder.CreateFCmpONE(condVal, llvm::ConstantFP::get(condVal->getType(), 0.0), "cond_to_bool");
    }
    std::cerr << "Cannot convert condition to boolean." << std::endl;
    return nullptr;
}
std::any ASTtoIRVisitor::visitFuncRParams(HelloParser::FuncRParamsContext *context) { return nullptr; } // Handled in UnaryExp for call
std::any ASTtoIRVisitor::visitRelExp(HelloParser::RelExpContext *context) {
    // RelExp -> AddExp ( RelOp AddExp )*
    // RelOp: '<' | '>' | LE | GE
    llvm::Value* lhs = std::any_cast<llvm::Value*>(visitAddExp(context->addExp(0)));
    if (context->op.empty()) return lhs; // Not a comparison, just an AddExp

    for (size_t i = 0; i < context->op.size(); ++i) {
        llvm::Value* rhs = std::any_cast<llvm::Value*>(visitAddExp(context->addExp(i + 1)));
        // Type compatibility/promotion
        bool isFloat = lhs->getType()->isFloatingPointTy() || rhs->getType()->isFloatingPointTy();
        // if (isFloat) { /* promote to float if one is float */ }

        llvm::CmpInst::Predicate pred;
        if (context->op[i]->getType() == HelloLexer::LT) pred = isFloat ? llvm::CmpInst::FCMP_OLT : llvm::CmpInst::ICMP_SLT;
        else if (context->op[i]->getType() == HelloLexer::GT) pred = isFloat ? llvm::CmpInst::FCMP_OGT : llvm::CmpInst::ICMP_SGT;
        else if (context->op[i]->getType() == HelloLexer::LE) pred = isFloat ? llvm::CmpInst::FCMP_OLE : llvm::CmpInst::ICMP_SLE;
        else if (context->op[i]->getType() == HelloLexer::GE) pred = isFloat ? llvm::CmpInst::FCMP_OGE : llvm::CmpInst::ICMP_SGE;
        else { std::cerr << "Unknown RelOp" << std::endl; return nullptr; }

        if (isFloat) lhs = builder.CreateFCmp(pred, lhs, rhs, "relcmp");
        else lhs = builder.CreateICmp(pred, lhs, rhs, "relcmp");
    }
    return lhs; // Result is i1 (boolean)
}
std::any ASTtoIRVisitor::visitEqExp(HelloParser::EqExpContext *context) {
    // EqExp -> RelExp ( EqOp RelExp )*
    // EqOp: EQ | NE
    llvm::Value* lhs = std::any_cast<llvm::Value*>(visitRelExp(context->relExp(0)));
    if (context->op.empty()) return lhs;

    for (size_t i = 0; i < context->op.size(); ++i) {
        llvm::Value* rhs = std::any_cast<llvm::Value*>(visitRelExp(context->relExp(i + 1)));
        bool isFloat = lhs->getType()->isFloatingPointTy() || rhs->getType()->isFloatingPointTy();
        // Type promotion
        llvm::CmpInst::Predicate pred;
        if (context->op[i]->getType() == HelloLexer::EQ) pred = isFloat ? llvm::CmpInst::FCMP_OEQ : llvm::CmpInst::ICMP_EQ;
        else if (context->op[i]->getType() == HelloLexer::NE) pred = isFloat ? llvm::CmpInst::FCMP_ONE : llvm::CmpInst::ICMP_NE;
        else { std::cerr << "Unknown EqOp" << std::endl; return nullptr; }

        if (isFloat) lhs = builder.CreateFCmp(pred, lhs, rhs, "eqcmp");
        else lhs = builder.CreateICmp(pred, lhs, rhs, "eqcmp");
    }
    return lhs; // Result is i1
}
std::any ASTtoIRVisitor::visitLAndExp(HelloParser::LAndExpContext *context) {
    // LAndExp -> EqExp ( '&&' EqExp )*
    // Needs short-circuiting:
    // result = true
    // For each EqExp:
    //   val = eval(EqExp)
    //   result = result && val
    //   if !result: break
    // This translates to basic blocks and conditional branches.
    if (context->eqExp().size() == 1) {
        return visitEqExp(context->eqExp(0)); // No '&&', just the EqExp
    }

    llvm::Function *TheFunction = builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *OriginalBB = builder.GetInsertBlock();
    
    // Create an alloca for the result, initialized to true (or 1 for i1)
    llvm::AllocaInst *resAlloca = builder.CreateAlloca(llvm::Type::getInt1Ty(irGen.getContext()), nullptr, "land_res");
    builder.CreateStore(llvm::ConstantInt::getTrue(irGen.getContext()), resAlloca);

    llvm::BasicBlock *ShortCircuitEndBB = nullptr; // Will be created if short-circuiting happens

    for (size_t i = 0; i < context->eqExp().size(); ++i) {
        llvm::Value* eqVal = std::any_cast<llvm::Value*>(visitEqExp(context->eqExp(i)));
        if (!eqVal) return nullptr;
        if (!eqVal->getType()->isIntegerTy(1)) { // Ensure it's boolean (i1)
            eqVal = builder.CreateICmpNE(eqVal, llvm::ConstantInt::get(eqVal->getType(), 0), "tobool");
        }

        // Current result = current result && eqVal
        llvm::Value* currentRes = builder.CreateLoad(llvm::Type::getInt1Ty(irGen.getContext()), resAlloca, "land_cur_res");
        llvm::Value* nextRes = builder.CreateAnd(currentRes, eqVal, "land_and");
        builder.CreateStore(nextRes, resAlloca);

        if (i < context->eqExp().size() - 1) { // If not the last operand
            llvm::BasicBlock *NextTermBB = llvm::BasicBlock::Create(irGen.getContext(), "land_next", TheFunction);
            ShortCircuitEndBB = llvm::BasicBlock::Create(irGen.getContext(), "land_sc_end", TheFunction);
            
            // If nextRes is false, branch to ShortCircuitEndBB, else to NextTermBB
            builder.CreateCondBr(nextRes, NextTermBB, ShortCircuitEndBB);
            builder.SetInsertPoint(NextTermBB);
        }
    }

    if (ShortCircuitEndBB) {
        // If we came from a short-circuit path, the current block is the last NextTermBB.
        // We need to branch from it to the ShortCircuitEndBB.
        if (builder.GetInsertBlock()->getTerminator() == nullptr) { // Ensure current block is not already terminated
            builder.CreateBr(ShortCircuitEndBB);
        }
        builder.SetInsertPoint(ShortCircuitEndBB);
        // Values from different paths need to merge if resAlloca is used after this.
        // The value in resAlloca is the result.
    }
    // else: only one term or no short-circuiting occurred, resAlloca holds the final value.

    return builder.CreateLoad(llvm::Type::getInt1Ty(irGen.getContext()), resAlloca, "land_final_res");
}
std::any ASTtoIRVisitor::visitLOrExp(HelloParser::LOrExpContext *context) {
    // LOrExp -> LAndExp ( '||' LAndExp )*
    // Similar short-circuiting logic as LAndExp
    if (context->lAndExp().size() == 1) {
        return visitLAndExp(context->lAndExp(0));
    }

    llvm::Function *TheFunction = builder.GetInsertBlock()->getParent();
    llvm::AllocaInst *resAlloca = builder.CreateAlloca(llvm::Type::getInt1Ty(irGen.getContext()), nullptr, "lor_res");
    builder.CreateStore(llvm::ConstantInt::getFalse(irGen.getContext()), resAlloca); // Initialize to false

    llvm::BasicBlock *ShortCircuitEndBB = nullptr;

    for (size_t i = 0; i < context->lAndExp().size(); ++i) {
        llvm::Value* landVal = std::any_cast<llvm::Value*>(visitLAndExp(context->lAndExp(i)));
        if (!landVal) return nullptr;
         if (!landVal->getType()->isIntegerTy(1)) {
            landVal = builder.CreateICmpNE(landVal, llvm::ConstantInt::get(landVal->getType(), 0), "tobool");
        }

        llvm::Value* currentRes = builder.CreateLoad(llvm::Type::getInt1Ty(irGen.getContext()), resAlloca, "lor_cur_res");
        llvm::Value* nextRes = builder.CreateOr(currentRes, landVal, "lor_or");
        builder.CreateStore(nextRes, resAlloca);

        if (i < context->lAndExp().size() - 1) {
            llvm::BasicBlock *NextTermBB = llvm::BasicBlock::Create(irGen.getContext(), "lor_next", TheFunction);
            ShortCircuitEndBB = llvm::BasicBlock::Create(irGen.getContext(), "lor_sc_end", TheFunction);
            // If nextRes is true, branch to ShortCircuitEndBB, else to NextTermBB
            builder.CreateCondBr(nextRes, ShortCircuitEndBB, NextTermBB);
            builder.SetInsertPoint(NextTermBB);
        }
    }
     if (ShortCircuitEndBB) {
        if (builder.GetInsertBlock()->getTerminator() == nullptr) {
            builder.CreateBr(ShortCircuitEndBB);
        }
        builder.SetInsertPoint(ShortCircuitEndBB);
    }
    return builder.CreateLoad(llvm::Type::getInt1Ty(irGen.getContext()), resAlloca, "lor_final_res");
}
std::any ASTtoIRVisitor::visitCharacter(HelloParser::CharacterContext *context) {
    std::string charText = context->getText(); // e.g., "'a'" or "'\n'"
    if (charText.length() >= 2 && charText.front() == '\'' && charText.back() == '\'') {
        char c_val;
        if (charText.length() == 3) { // Simple char like 'a'
            c_val = charText[1];
        } else if (charText.length() == 4 && charText[1] == '\\') { // Escaped char like '\n'
            switch (charText[2]) {
                case 'n': c_val = '\n'; break;
                case 't': c_val = '\t'; break;
                case '\\': c_val = '\\'; break;
                case '\'': c_val = '\''; break;
                case '0': c_val = '\0'; break;
                // Add other escapes as needed
                default: std::cerr << "Unknown escape sequence: " << charText << std::endl; return nullptr;
            }
        } else {
             std::cerr << "Invalid char literal: " << charText << std::endl; return nullptr;
        }
        // Characters are often treated as small integers (e.g., i8 or i32)
        return llvm::ConstantInt::get(llvm::Type::getInt8Ty(irGen.getContext()), c_val);
    }
    std::cerr << "Invalid char literal format: " << charText << std::endl;
    return nullptr;
}

// ... (Implement ALL other pure virtual visit methods from HelloVisitor.h)
// Many might just call children or return nullptr if not directly generating IR for that node type.
// For example:
// std::any ASTtoIRVisitor::visitSomeNodeWithoutDirectIR(HelloParser::SomeNodeContext *ctx) {
//     return visitChildren(ctx); // Default ANTLR visitor behavior
// }