#include "SemanticAnalyzer.h"
#include <cstddef>
#include <string>
#include <vector>
#include "symbolTable.h"
#include "utils/Utils.h"
#include "utils/ReturnValue.h"

// 语义分析器构造函数，初始化全局作用域和语法树根节点
SemanticAnalyzer::SemanticAnalyzer(GlobalBlock *globalBlock, tree::ParseTree *root)
        : globalBlock(globalBlock), root(root), currentBlock(globalBlock), currentFunc(nullptr) {}

SemanticAnalyzer::~SemanticAnalyzer() = default;

// 处理编译单元（顶级作用域）
// 检查所有声明和函数定义，并确保存在main函数
std::any SemanticAnalyzer::visitCompUnit(HelloParser::CompUnitContext *context) {
    for (auto declOrFunc : context->declOrFunc()) {
        visit(declOrFunc);
    }
    if (globalBlock->lookUpFunc("main") == nullptr) {
        ErrorHandler::printErrorMessage("Missing main function");
        throw std::runtime_error("Semantic analysis failed");
    }
    return {};
}

// 处理声明或函数定义的联合入口
std::any SemanticAnalyzer::visitDeclOrFunc(HelloParser::DeclOrFuncContext *context) {
    if (context->decl()) return visit(context->decl());
    else return visit(context->funcDef());
}

// 处理声明（常量/变量声明）
std::any SemanticAnalyzer::visitDecl(HelloParser::DeclContext *context) {
    if (context->constDecl()) return visit(context->constDecl());
    else return visit(context->varDecl());
}

// 处理常量声明（const类型）
std::any SemanticAnalyzer::visitConstDecl(HelloParser::ConstDeclContext *context) {
    // 解析基础数据类型（int/float等）
    DataType dataType = Utils::stot(context->btype()->getText());
    for (auto constDef : context->constDef()) {
        constDef->dataType = dataType; // 传递数据类型到子节点
        visit(constDef); // 处理具体常量定义（包括数组）
    }
    return {};
}

// 处理变量声明（var类型）
std::any SemanticAnalyzer::visitVarDecl(HelloParser::VarDeclContext *context) {
    // 解析基础数据类型
    DataType dataType = Utils::stot(context->btype()->getText());
    for (auto varDef : context->varDef()) {
        varDef->dataType = dataType; // 传递数据类型
        visit(varDef); // 处理具体变量定义（包括数组和初始化）
    }
    return {};
}

// 处理常量定义（包括普通常量和数组常量）
std::any SemanticAnalyzer::visitConstDef(HelloParser::ConstDefContext *context) {
    int line = context->Ident()->getSymbol()->getLine(); // 获取声明行号
    std::vector<int> arraySize;
    // 解析数组维度（方括号中的常量）
    for (auto size : context->IntConst()) {
        arraySize.push_back(stoi(size->getText()));
    }
    int dimension = arraySize.size(); // 计算数组维度
    std::string name = context->Ident()->getText(); // 获取标识符名称

    // 创建符号表条目：区分普通常量和数组常量
    if (dimension == 0) {
        // 普通常量：添加到当前作用域
        currentSymbol = currentBlock->addNewConst(name, line, context->dataType);
    } else {
        // 数组常量：添加多维数组符号
        currentSymbol = currentBlock->addNewConstArray(name, line, context->dataType, arraySize, dimension);
    }

    visit(context->constInitVal()); // 处理常量初始化值
    return {};
}

// 处理变量定义（包括普通变量和数组变量）
std::any SemanticAnalyzer::visitVarDef(HelloParser::VarDefContext *context) {
    int line = context->Ident()->getSymbol()->getLine(); // 声明行号
    std::vector<int> arraySize;
    // 解析数组维度
    for (auto size : context->IntConst()) {
        arraySize.push_back(stoi(size->getText()));
    }
    int dimension = arraySize.size(); // 维度计算
    std::string name = context->Ident()->getText(); // 变量名

    // 创建符号表条目：区分普通变量和数组变量
    if (dimension == 0) {
        currentSymbol = currentBlock->addNewVar(name, line, context->dataType); // 普通变量
    } else {
        currentSymbol = currentBlock->addNewVarArray(name, line, context->dataType, arraySize, dimension); // 数组变量
    }

    // 处理初始化：如果有初始化列表则解析，否则填充默认值（0）
    if (context->constInitVal()) {
        visit(context->constInitVal()); // 处理初始化值
    } else {
        // 计算数组元素总数，填充默认0值
        unsigned loop = (arraySize.empty()) ? 1 : std::accumulate(arraySize.begin(), arraySize.end(), 1, std::multiplies<>());
        for (int i = 0; i < loop; i++) {
            currentSymbol->setZero(context->dataType); // 设置默认初始值
        }
    }
    return {};
}

// 处理常量初始化值（支持字面量和数组初始化）
std::any SemanticAnalyzer::visitConstInitVal(HelloParser::ConstInitValContext *context) {
    // 处理单个字面量初始化（非数组）
    if (context->constExp()) {
        visit(context->constExp()); // 解析常量表达式
        // 设置常量初始值（符号表中存储初始值）
        currentSymbol->setInitValue(context->constExp()->getText(), context->dataType);
    } else {
        // 处理数组初始化列表
        int expectedSize = std::accumulate(currentSymbol->getArraySize().begin(), currentSymbol->getArraySize().end(), 1, std::multiplies<>()); // 期望的数组元素总数
        int providedSize = context->constInitVal().size(); // 提供的初始化值数量
        
        // 检查初始化列表长度是否超过数组大小
        if (providedSize > expectedSize) {
            ErrorHandler::printErrorContext(context, "Too many initializers for array");
            throw std::runtime_error("Semantic error");
        }
        
        // 递归处理每个子初始化值
        for (auto init : context->constInitVal()) {
            init->dataType = context->dataType; // 传递数据类型
            visit(init); // 处理嵌套的初始化（如多维数组）
        }
        // 填充剩余元素为默认0值
        for (int i = providedSize; i < expectedSize; i++) {
            currentSymbol->setZero(context->dataType);
        }
    }
    return {};
}

// 处理函数定义
std::any SemanticAnalyzer::visitFuncDef(HelloParser::FuncDefContext *context) {
    // 解析返回类型（默认void，否则解析基础类型）
    DataType returnType = (context->funcType()->btype()) ? 
        Utils::stot(context->funcType()->btype()->getText()) : DataType::VOID;
    std::string funcName = context->Ident()->getText(); // 函数名
    int line = context->Ident()->getSymbol()->getLine(); // 声明行号
    
    // 添加函数符号到全局作用域
    currentFunc = globalBlock->addNewFunc(funcName, line, returnType);
    BlockInfo *oldBlock = currentBlock; // 保存当前作用域
    // 创建函数作用域（子作用域）
    currentBlock = globalBlock->addNewBlock(currentFunc);

    visit(context->funcFParams()); // 处理函数参数
    visit(context->block()); // 处理函数体（复合语句）
    
    currentBlock = oldBlock; // 恢复外层作用域
    return {};
}

// 处理函数参数列表
std::any SemanticAnalyzer::visitFuncFParams(HelloParser::FuncFParamsContext *context) {
    // 遍历每个函数参数
    if (context->funcFParam()) {
        for (auto param : context->funcFParam()) {
            visit(param); // 处理单个参数
        }
    }
    return {};
}

// 处理单个函数参数（支持数组参数）
std::any SemanticAnalyzer::visitFuncFParam(HelloParser::FuncFParamContext *context) {
    DataType dataType = Utils::stot(context->btype()->getText()); // 参数数据类型
    std::string name = context->Ident()->getText(); // 参数名
    int dimension = context->LeftBracket().size(); // 数组维度（方括号数量）
    std::vector<int> arraySize; // 数组各维度大小
    
    // 解析参数的数组维度（仅允许第一维省略，用0表示）
    for (auto size : context->IntConst()) {
        arraySize.push_back(stoi(size->getText()));
    }
    
    // 检查数组维度合法性（不允许负数或零维数组作为参数）
    if (dimension > 0 && (arraySize.size() > 0 && arraySize[0] <= 0)) {
        ErrorHandler::printErrorContext(context, "Invalid array dimension in parameter");
        throw std::runtime_error("Semantic error");
    }
    
    // 添加参数到函数符号表：区分普通参数和数组参数
    if (dimension == 0) {
        currentFunc->addParamVar(name, context->Ident()->getSymbol()->getLine(), dataType); // 普通参数
    } else {
        currentFunc->addParamArray(name, context->Ident()->getSymbol()->getLine(), dataType, arraySize, dimension); // 数组参数
    }
    return {};
}

// 处理复合语句（函数体或块作用域）
std::any SemanticAnalyzer::visitBlock(HelloParser::BlockContext *context) {
    BlockInfo *oldBlock = currentBlock; // 保存当前作用域
    // 创建新的块作用域（子作用域）
    currentBlock = currentBlock->addNewBlock();
    
    // 处理块内的声明和语句
    for (auto blockItem : context->blockItem()) {
        visit(blockItem); // 处理声明或语句
    }
    
    currentBlock = oldBlock; // 恢复外层作用域
    return {};
}

// 处理块内元素（声明或语句）
std::any SemanticAnalyzer::visitBlockItem(HelloParser::BlockItemContext *context) {
    // 区分声明和语句
    if (context->decl()) return visit(context->decl()); // 处理声明
    else return visit(context->stmt()); // 处理语句
}

// 处理各种语句类型
std::any SemanticAnalyzer::visitStmt(HelloParser::StmtContext *context) {
    if (context->assignStmt()) return visit(context->assignStmt()); // 赋值语句
    else if (context->exprStmt()) return visit(context->exprStmt()); // 表达式语句
    else if (context->blockStmt()) return visit(context->blockStmt()); // 块语句
    else if (context->returnStmt()) return visit(context->returnStmt()); // 返回语句
    else if (context->ifStmt()) return visit(context->ifStmt()); // if语句
    else if (context->whileStmt()) return visit(context->whileStmt()); // while语句
    else if (context->breakStmt() || context->continueStmt()) return visit(context->breakStmt()); // break/continue语句
    return {};
}

// 处理赋值语句（核心类型检查点）
std::any SemanticAnalyzer::visitAssignStmt(HelloParser::AssignStmtContext *context) {
    // 获取左值和右值的语义信息
    auto lval = visit(context->lVal());
    auto expr = visit(context->exp());
    
    ReturnValue lvalInfo = std::any_cast<ReturnValue>(lval); // 左值信息（符号类型、数据类型等）
    ReturnValue exprInfo = std::any_cast<ReturnValue>(expr); // 右值信息
    
    // 类型匹配检查：左值和右值数据类型必须一致
    if (lvalInfo.getDataType() != exprInfo.getDataType()) {
        ErrorHandler::printErrorContext(context, "Type mismatch in assignment");
        throw std::runtime_error("Semantic error");
    }
    // 常量不可赋值检查：防止修改const变量或数组
    if (lvalInfo.getSymbolType() == SymbolType::CONST || lvalInfo.getSymbolType() == SymbolType::CONST_ARRAY) {
        ErrorHandler::printErrorContext(context, "Assign to constant is not allowed");
        throw std::runtime_error("Semantic error");
    }
    return {};
}

// 处理表达式语句（忽略纯表达式语句）
std::any SemanticAnalyzer::visitExprStmt(HelloParser::ExprStmtContext *context) {
    if (context->exp()) visit(context->exp()); // 仅解析表达式，不产生副作用
    return {};
}

// 处理返回语句（函数返回值检查）
std::any SemanticAnalyzer::visitReturnStmt(HelloParser::ReturnStmtContext *context) {
    // 处理void函数返回：不允许有返回值
    if (currentFunc->getDataType() == DataType::VOID && context->exp()) {
        ErrorHandler::printErrorContext(context, "Return statement with value in void function");
        throw std::runtime_error("Semantic error");
    }
    // 处理非void函数返回：必须有返回值且类型匹配
    else if (currentFunc->getDataType() != DataType::VOID && !context->exp()) {
        ErrorHandler::printErrorContext(context, "Missing return value in non-void function");
        throw std::runtime_error("Semantic error");
    } else if (context->exp()) {
        auto expr = visit(context->exp());
        ReturnValue exprInfo = std::any_cast<ReturnValue>(expr);
        // 返回值类型必须与函数声明一致
        if (exprInfo.getDataType() != currentFunc->getDataType()) {
            ErrorHandler::printErrorContext(context, "Return type mismatch");
            throw std::runtime_error("Semantic error");
        }
    }
    return {};
}

// 处理if语句（条件表达式必须为布尔类型）
std::any SemanticAnalyzer::visitIfStmt(HelloParser::IfStmtContext *context) {
    auto cond = visit(context->cond());
    ReturnValue condInfo = std::any_cast<ReturnValue>(cond);
    // 条件表达式必须为布尔类型
    if (condInfo.getDataType() != DataType::BOOL) {
        ErrorHandler::printErrorContext(context, "Condition must be boolean");
        throw std::runtime_error("Semantic error");
    }
    visit(context->stmt(0)); // 处理then分支
    if (context->stmt().size() > 1) visit(context->stmt(1)); // 处理else分支
    return {};
}

// 处理while语句（循环条件必须为布尔类型）
std::any SemanticAnalyzer::visitWhileStmt(HelloParser::WhileStmtContext *context) {
    auto cond = visit(context->cond());
    ReturnValue condInfo = std::any_cast<ReturnValue>(cond);
    // 循环条件必须为布尔类型
    if (condInfo.getDataType() != DataType::BOOL) {
        ErrorHandler::printErrorContext(context, "Loop condition must be boolean");
        throw std::runtime_error("Semantic error");
    }
    visit(context->stmt()); // 处理循环体
    return {};
}

// 处理左值（变量或数组元素）
std::any SemanticAnalyzer::visitLVal(HelloParser::LValContext *context) {
    std::string name = context->Ident()->getText(); // 标识符名称
    // 在作用域链中查找符号（当前块 -> 父块 -> 全局块）
    SymbolInfo *symbol = currentBlock->lookUpSymbol(name);
    
    // 未声明标识符检查
    if (!symbol) {
        ErrorHandler::printErrorContext(context, "Undeclared identifier");
        throw std::runtime_error("Semantic error");
    }
    
    int dimension = symbol->getArraySize().size(); // 符号的数组维度
    int indexCount = context->exp().size(); // 使用的下标数量
    
    // 下标数量不能超过数组维度
    if (indexCount > dimension) {
        ErrorHandler::printErrorContext(context, "Too many array indices");
        throw std::runtime_error("Semantic error");
    }
    
    // 检查每个下标表达式是否为整数
    for (auto exp : context->exp()) {
        auto idx = visit(exp);
        ReturnValue idxInfo = std::any_cast<ReturnValue>(idx);
        if (idxInfo.getDataType() != DataType::INT || idxInfo.getDimension() != 0) {
            ErrorHandler::printErrorContext(exp, "Array index must be integer");
            throw std::runtime_error("Semantic error");
        }
    }
    
    // 计算剩余维度（用于多维数组访问）
    std::vector<int> remainingSize;
    for (int i = indexCount; i < dimension; i++) {
        remainingSize.push_back(symbol->getArraySize()[i]);
    }
    
    // 返回左值信息（数据类型、剩余维度、符号类型）
    return ReturnValue(
        symbol->getDataType(),
        dimension - indexCount,
        remainingSize,
        symbol->getSymbolType()
    );
}

// 处理表达式（入口点）
std::any SemanticAnalyzer::visitExp(HelloParser::ExpContext *context) {
    return visit(context->addExp()); // 表达式解析从加法表达式开始
}

// 处理加法表达式（类型一致性检查）
std::any SemanticAnalyzer::visitAddExp(HelloParser::AddExpContext *context) {
    std::vector<ReturnValue> operands;
    // 解析所有乘法表达式作为操作数
    for (auto mulExp : context->mulExp()) {
        operands.push_back(std::any_cast<ReturnValue>(visit(mulExp)));
    }
    
    // 检查所有操作数类型一致且非数组
    for (int i = 1; i < operands.size(); i++) {
        if (operands[i].getDataType() != operands[0].getDataType()) {
            ErrorHandler::printErrorContext(context, "Type mismatch in expression");
            throw std::runtime_error("Semantic error");
        }
        if (operands[i].getDimension() != 0) {
            ErrorHandler::printErrorContext(context, "Array cannot be used in arithmetic expression");
            throw std::runtime_error("Semantic error");
        }
    }
    
    return operands[0]; // 返回第一个操作数（类型已统一）
}

// 处理乘法表达式（类型一致性检查）
std::any SemanticAnalyzer::visitMulExp(HelloParser::MulExpContext *context) {
    std::vector<ReturnValue> operands;
    // 解析所有一元表达式作为操作数
    for (auto unaryExp : context->unaryExp()) {
        operands.push_back(std::any_cast<ReturnValue>(visit(unaryExp)));
    }
    
    // 检查所有操作数类型一致且非数组
    for (int i = 1; i < operands.size(); i++) {
        if (operands[i].getDataType() != operands[0].getDataType()) {
            ErrorHandler::printErrorContext(context, "Type mismatch in expression");
            throw std::runtime_error("Semantic error");
        }
        if (operands[i].getDimension() != 0) {
            ErrorHandler::printErrorContext(context, "Array cannot be used in multiplicative expression");
            throw std::runtime_error("Semantic error");
        }
    }
    
    return operands[0]; // 返回第一个操作数（类型已统一）
}

// 处理一元表达式（支持函数调用、取反、逻辑非）
std::any SemanticAnalyzer::visitUnaryExp(HelloParser::UnaryExpContext *context) {
    if (context->primaryExp()) {
        return visit(context->primaryExp()); // 处理基本表达式（变量、数组、字面量）
    } else if (context->unaryOp()) {
        // 处理一元运算符（取反、逻辑非）
        auto operand = visit(context->unaryExp());
        ReturnValue opInfo = std::any_cast<ReturnValue>(operand);
        
        // 数组不能参与一元运算检查
        if (opInfo.getDimension() != 0) {
            ErrorHandler::printErrorContext(context, "Array cannot be used in unary expression");
            throw std::runtime_error("Semantic error");
        }
        
        std::string op = context->unaryOp()->getText();
        // 逻辑非只能用于布尔类型
        if (op == "!" && opInfo.getDataType() != DataType::BOOL) {
            ErrorHandler::printErrorContext(context, "Logical not applied to non-boolean");
            throw std::runtime_error("Semantic error");
        }
        // 取反只能用于数值类型
        else if (op == "-" && (opInfo.getDataType() != DataType::INT && opInfo.getDataType() != DataType::FLOAT && opInfo.getDataType() != DataType::DOUBLE)) {
            ErrorHandler::printErrorContext(context, "Unary minus applied to non-numeric type");
            throw std::runtime_error("Semantic error");
        }
        
        return opInfo; // 返回操作数（类型已检查）
    } else { 
        // 处理函数调用
        std::string funcName = context->Ident()->getText();
        auto func = globalBlock->lookUpFunc(funcName);
        // 未声明函数检查
        if (!func) {
            ErrorHandler::printErrorContext(context, "Undeclared function");
            throw std::runtime_error("Semantic error");
        }
        // 参数数量匹配检查
        int argCount = context->funcRParams() ? context->funcRParams()->exp().size() : 0;
        if (argCount != func->getparamNum()) {
            ErrorHandler::printErrorContext(context, "Argument count mismatch");
            throw std::runtime_error("Semantic error");
        }
        return ReturnValue(func->getDataType(), 0, {}, SymbolType::FUNC); // 返回函数返回类型
    }
}

// 处理基本表达式（变量、数组元素、字面量、括号表达式）
std::any SemanticAnalyzer::visitPrimaryExp(HelloParser::PrimaryExpContext *context) {
    if (context->lVal()) return visit(context->lVal()); // 处理左值（变量/数组元素）
    else if (context->number()) return visit(context->number()); // 处理数值字面量
    else if (context->exp()) return visit(context->exp()); // 处理括号表达式
    return {};
}

// 处理数值字面量（整数、浮点数）
std::any SemanticAnalyzer::visitNumber(HelloParser::NumberContext *context) {
    if (context->IntConst()) return ReturnValue(DataType::INT, 0, {}, SymbolType::NUM); // 整数类型
    else if (context->FloatConst()) {
        // 区分float和double类型
        std::string val = context->FloatConst()->getText();
        return (val.find('f') != std::string::npos) ? 
            ReturnValue(DataType::FLOAT, 0, {}, SymbolType::NUM) : 
            ReturnValue(DataType::DOUBLE, 0, {}, SymbolType::NUM);
    }
    return {};
}

// 开始语义分析的入口函数
void SemanticAnalyzer::analyze() {
    visit(root); // 从语法树根节点开始遍历
}