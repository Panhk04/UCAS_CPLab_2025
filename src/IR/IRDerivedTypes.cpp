#include "IRDerivedTypes.h"
#include <iostream>

// IRFunctionType 实现
IRFunctionType::IRFunctionType(IRType *Result, const std::vector<IRType *> &Params)
    : IRType("", IRType::FunctionTyID), paramTys(Params) {
    // 函数类型的结果类型存储在另一个地方，这里简化处理
}

IRType *IRFunctionType::getReturnType() const {
    // 简化实现，实际应该存储返回类型
    return const_cast<IRType*>(IRType::getPrimitiveType(IRType::VoidTyID));
}

void IRFunctionType::print(std::ostream &OS) const {
    OS << "function(";
    for (size_t i = 0; i < paramTys.size(); ++i) {
        if (i > 0) OS << ", ";
        paramTys[i]->print(OS);
    }
    OS << ")";
}

// IRArrayType 实现
IRArrayType::IRArrayType(IRType *ElementType, unsigned NumElements)
    : IRType("", IRType::ArrayTyID), elementType(ElementType), numElements(NumElements) {
}

void IRArrayType::print(std::ostream &OS) const {
    OS << "[" << numElements << " x ";
    elementType->print(OS);
    OS << "]";
}

// IRPointerType 实现
IRPointerType::IRPointerType(IRType *ElementType)
    : IRType("", IRType::PointerTyID), pointeeType(ElementType) {
}

void IRPointerType::print(std::ostream &OS) const {
    pointeeType->print(OS);
    OS << "*";
}