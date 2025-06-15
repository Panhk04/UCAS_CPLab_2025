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
    /*
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
    */
    /*遍历语法树，生成无优化IR代码*/
    IRModule ir(file);
    FrontEnd frontEnd(&stream, &ir);

    try {
        frontEnd.analyze();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    /*对IR代码进行优化；opt建立，划定优先级，根据优先级跑优化pass*/
    Optimizer opt(&ir);
    opt.build();
    opt.setLevel(parser.getLevel());
    opt.run();

    /*打印优化之后的IR代码*/
    if (parser.get("emit-IR"))
        frontEnd.print();

    /*解释执行或者直接生成RISCV代码*/
    Interpreter ip(&ir);
    Interpreter::debugOpt = parser.get("verbose");
    if (parser.get("simulate") || parser.get("verbose")) {
        int ret = ip.interpret();
        if (parser.get("c"))
            printf("inst_cnt = %d\n", Interpreter::getInstCnt());
        return ret;
    } else {
        BackEnd backEnd(&ir);
        backEnd.print();
    }
    return 0;
}