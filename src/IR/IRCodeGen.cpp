#include "IRCodeGen.h"

llvm::Function* IRCodeGenerator::createFunction(const std::string &name, 
                                                llvm::Type *returnType,
                                                const std::vector<llvm::Type*> &paramTypes) {
    llvm::FunctionType *funcType = llvm::FunctionType::get(returnType, paramTypes, false);
    llvm::Function *func = llvm::Function::Create(funcType, 
                                                  llvm::Function::ExternalLinkage, 
                                                  name, &module);
    return func;
}

llvm::BasicBlock* IRCodeGenerator::createBasicBlock(const std::string &name, 
                                                    llvm::Function *func) {
    if (!func) func = currentFunction;
    return llvm::BasicBlock::Create(context, name, func);
}

void IRCodeGenerator::setNamedValue(const std::string &name, llvm::Value *value) {
    namedValues[name] = value;
}

llvm::Value* IRCodeGenerator::getNamedValue(const std::string &name) {
    auto it = namedValues.find(name);
    return (it != namedValues.end()) ? it->second : nullptr;
}