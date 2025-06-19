#include "FrontEnd.h"
#include <filesystem>
#include "utils/ControlFlowGraph.h"

FrontEnd::FrontEnd(std::ifstream *stream, IRModule *ir)
        : input(*stream), lexer(&input), tokens(&lexer), parser(&tokens), ir(ir), root(parser.compilationUnit()),
          analyzer(&globalBlock, ir, root), generator(&globalBlock, ir, root) {
    globalBlock.initIOFunction(ir);
}

void FrontEnd::analyze() {
    if (this->parser.getNumberOfSyntaxErrors() > 0 ||
        this->lexer.getNumberOfSyntaxErrors() > 0) {
        std::cerr << "lexer error: " << lexer.getNumberOfSyntaxErrors()
                  << std::endl;
        std::cerr << "parser error: " << parser.getNumberOfSyntaxErrors()
                  << std::endl;
        throw std::runtime_error("Syntax analysis failed at " +
                                 std::string(__FILE__) + ":" +
                                 std::to_string(__LINE__));
    }

    analyzer.analyze();

    generator.generate();

    for (auto func: ir->getFuncList()) {
        if (func->getFuntTy() == IRFunction::Declared)
            ControlFlowGraph cfg(func);
    }
}

void FrontEnd::print() {
    std::string strsrc = ir->getName();

    /**替换cact**/
    std::string strCact = ".cact";
    std::string strIr = ".ir";
    size_t pos2 = strsrc.find(strCact);
    if (pos2 != std::string::npos) {
        strsrc.replace(pos2, strCact.length(), strIr);  // 替换子串
    }

    std::filesystem::path path(strsrc);
    std::string dirPath = path.parent_path().string();
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
    }
    std::ofstream outputFile(strsrc);

    ir->print(outputFile);

    outputFile.close();

}
