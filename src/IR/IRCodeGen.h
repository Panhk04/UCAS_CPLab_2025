# pragma once

#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include <memory>
#include <unordered_map>
#include <string>

class IRCodeGenerator{
    private:
        llvm::LLVMContext &context;
        llvm::Module &module;
        llvm::IRBuilder<> builder;
        // 符号表，存储变量名到LLVM Value的映射
        std::unordered_map<std::string, llvm::Value*> namedValues;
        
        // 当前函数
        llvm::Function *currentFunction;
    public:
        // 声明构造函数
        IRCodeGenerator(llvm::LLVMContext &ctx, llvm::Module &mod); 

        // 基本类型获取
        llvm::Type* getInt32Type() { return llvm::Type::getInt32Ty(context); }
        llvm::Type* getFloatType() { return llvm::Type::getFloatTy(context); }
        llvm::Type* getVoidType() { return llvm::Type::getVoidTy(context); }
        llvm::Type* getInt8Type() { return llvm::Type::getInt8Ty(context); }
        
        // 创建函数
        llvm::Function* createFunction(const std::string &name, 
                                    llvm::Type *returnType,
                                    const std::vector<llvm::Type*> &paramTypes);
        
        // 创建基本块
        llvm::BasicBlock* createBasicBlock(const std::string &name, 
                                        llvm::Function *func = nullptr);
        
        // 变量管理
        void setNamedValue(const std::string &name, llvm::Value *value);
        llvm::Value* getNamedValue(const std::string &name);
        
        // 设置当前函数
        void setCurrentFunction(llvm::Function *func) { currentFunction = func; }
        llvm::Function* getCurrentFunction() { return currentFunction; }
        
        // 获取builder引用用于代码生成
        llvm::IRBuilder<>& getBuilder() { return builder; }
        llvm::Module& getModule() { return module; }
        llvm::LLVMContext& getContext() { return context; }

};