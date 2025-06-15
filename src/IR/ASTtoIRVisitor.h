#pragma once

#include <string.h>
#include "../../grammar/HelloVisitor.h"
#include "IRCodeGen.h"
#include "symbolTable.h" // For GlobalBlock, BlockInfo, FuncInfo, SymbolInfo, DataType
#include "utils/Utils.h"// For DataType, if it's defined there, or its own header
#include "llvm/IR/Value.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h" // For ArrayType, PointerType
#include <any>
#include <string>
#include <vector>
#include <map>

// Forward declaration
namespace antlr4 {
namespace tree {
class ParseTree;
}
}
class GlobalBlock;
class BlockInfo;
class FuncInfo;
class SymbolInfo;
// enum class DataType; // Ensure DataType is known

class ASTtoIRVisitor : public HelloVisitor {
public:
    // Constructor now takes the global symbol table and a map from AST context to BlockInfo
    ASTtoIRVisitor(IRCodeGenerator& generator, GlobalBlock* globalSymTable,
                   std::map<antlr4::tree::ParseTree*, BlockInfo*>& contextToScopeMap);

    std::any visitCompUnit(HelloParser::CompUnitContext *ctx) override;
    std::any visitDecl(HelloParser::DeclContext *ctx) override;
    std::any visitBtype(HelloParser::BtypeContext *ctx) override; // Might not be needed if types come from SymbolInfo
    std::any visitConstDecl(HelloParser::ConstDeclContext *ctx) override;
    std::any visitVarDecl(HelloParser::VarDeclContext *ctx) override;
    std::any visitConstDef(HelloParser::ConstDefContext *ctx) override;
    std::any visitConstInitVal(HelloParser::ConstInitValContext *ctx) override;
    std::any visitVarDef(HelloParser::VarDefContext *ctx) override;
    std::any visitFuncDef(HelloParser::FuncDefContext *ctx) override;
    std::any visitFuncType(HelloParser::FuncTypeContext *ctx) override; // Might use FuncInfo's return type
    std::any visitFuncFParams(HelloParser::FuncFParamsContext *ctx) override;
    std::any visitFuncFParam(HelloParser::FuncFParamContext *ctx) override;
    std::any visitBlock(HelloParser::BlockContext *ctx) override;
    std::any visitBlockItem(HelloParser::BlockItemContext *ctx) override;
    std::any visitStmt(HelloParser::StmtContext *ctx) override;
    std::any visitLVal(HelloParser::LValContext *ctx) override;
    std::any visitExp(HelloParser::ExpContext *ctx) override;
    std::any visitConstExp(HelloParser::ConstExpContext *ctx) override;
    std::any visitAddExpConst(HelloParser::AddExpConstContext *ctx) override;
    std::any visitMulExpConst(HelloParser::MulExpConstContext *ctx) override;
    std::any visitUnaryExpConst(HelloParser::UnaryExpConstContext *ctx) override;
    std::any visitPrimaryExpConst(HelloParser::PrimaryExpConstContext *ctx) override;
    std::any visitCond(HelloParser::CondContext *ctx) override;
    std::any visitNumber(HelloParser::NumberContext *ctx) override;
    std::any visitFuncRParams(HelloParser::FuncRParamsContext *ctx) override;
    std::any visitPrimaryExp(HelloParser::PrimaryExpContext *ctx) override;
    std::any visitUnaryExp(HelloParser::UnaryExpContext *ctx) override;
    std::any visitMulExp(HelloParser::MulExpContext *ctx) override;
    std::any visitAddExp(HelloParser::AddExpContext *ctx) override;
    std::any visitRelExp(HelloParser::RelExpContext *ctx) override;
    std::any visitEqExp(HelloParser::EqExpContext *ctx) override;
    std::any visitLAndExp(HelloParser::LAndExpContext *ctx) override;
    std::any visitLOrExp(HelloParser::LOrExpContext *ctx) override;
    std::any visitCharacter(HelloParser::CharacterContext *ctx) override;
    // Add any missing visit methods from HelloVisitor.h

private:
    IRCodeGenerator& irGen;
    llvm::IRBuilder<> builder;
    GlobalBlock* globalSymbolTable;
    BlockInfo* currentSymbolScope; // Current symbol table scope
    FuncInfo* currentFunctionSymInfo; // Symbol info for the current LLVM function being generated
    std::map<antlr4::tree::ParseTree*, BlockInfo*>& scopeMap; // Maps AST context to its BlockInfo

    llvm::Type* getLLVMTypeFromDataType(DataType dt, const std::vector<int>& arrayDimensions = {}, bool isFuncParam = false);
    llvm::Value* getSymbolAddress(const std::string& name);
    llvm::Constant* getConstSymbolValue(const std::string& name);
    llvm::Value* castToType(llvm::Value* value, llvm::Type* targetType, bool isSigned);


    // Helper to get LLVM type for an expression context, using semantic info
    DataType getExpDataType(HelloParser::ExpContext* ctx);
    // You might need to pass DataType around or attach it to ExpContext nodes via SemanticAnalyzer
    // For simplicity, many visitExp methods might need to determine type or get it from children.
};