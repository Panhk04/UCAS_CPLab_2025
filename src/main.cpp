#include <iostream>

// #include "antlr4-runtime.h"
#include "tree/ErrorNode.h"

#include "HelloLexer.h"
#include "HelloParser.h"
#include "HelloVisitor.h"

using namespace antlr4;
/*
 class Analysis : public HelloVisitor {
 public:
     std::any visitR(HelloParser::RContext *context) {
         visitChildren( context );
        
         std::cout << "enter rule [r]!" << std::endl;
         std::cout << "the ID is: " << context->ID()->getText().c_str() << std::endl;
         return nullptr;
     }


     std::any visitErrorNode(tree::ErrorNode * node) override {
         std::cout << "visit error node!" << std::endl;
         return nullptr;
     }
 };
*/
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



    ANTLRInputStream input(stream);
    HelloLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    HelloParser parser(&tokens);

    tokens.fill();
    for(auto token : tokens.getTokens()) {
        std::cout << "token: " << token->toString() << std::endl;
    }
    //打印Laxer得到的token

    tree::ParseTree *tree = parser.compUnit();
    std::cout << "tree: " << tree->toStringTree(&parser) << std::endl;
    //打印parser得到的AST

    std::cerr << lexer.getNumberOfSyntaxErrors() << std::endl;
    std::cerr << parser.getNumberOfSyntaxErrors() << std::endl;

    if (lexer.getNumberOfSyntaxErrors() > 0 || parser.getNumberOfSyntaxErrors() > 0) {
        std::cerr << "[ERROR] total number"<<lexer.getNumberOfSyntaxErrors() + parser.getNumberOfSyntaxErrors() << std::endl;
        return 3;
    }

    return 0;
}