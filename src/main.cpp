#include <iostream>
#include <fstream>

#include "antlr4-runtime.h"
#include "tree/ErrorNode.h"

#include "HelloLexer.h"
#include "HelloParser.h"
#include "HelloVisitor.h"

#include "SemanticAnalyzer.h"
#include "IRCodeGen.h"
#include "ASTtoIRVisitor.h"

// using namespace antlr4;

int main(int argc, const char* argv[]) {

    if(argc < 2) {
        std::cerr << "[ERROR]source file miss" << std::endl;
        return 1;
    }

    std::ifstream stream;
    stream.open(argv[1]);

    if(!stream.is_open()) {
        std::cerr << "[ERROR]open file failed" << std::endl;
        return 2;
    }

    // 1. ANTLR 解析
    ANTLRInputStream input(stream);
    HelloLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    HelloParser parser(&tokens);
    HelloParser::CompUnitContext *tree = parser.compUnit(); // 假设 compUnit 是你的起始规则

    // 2. 设置 LLVM IR 生成器
    IRCodeGenerator irGenerator("myModule");

    // 3. 创建 Visitor 并访问 AST
    ASTtoIRVisitor visitor(irGenerator);
    visitor.visitCompUnit(tree);

    // 4. 获取生成的 Module 并打印或进一步处理
    llvm::Module &module = irGenerator.getModule();
    module.print(llvm::outs(), nullptr); // 打印 IR 到标准输出

    return 0;
}