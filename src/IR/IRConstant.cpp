#include "IRConstant.h"
#include "IRType.h"
#include <iostream>

// IRConstant 基类实现
IRConstant::IRConstant(IRType *Ty, const std::string &Name)
    : IRValue(Ty, IRValue::ConstantVal, Name) {
}

void IRConstant::print(std::ostream &OS) const {
    OS << "constant ";
    getType()->print(OS);
}

// IRConstantInt 实现
IRConstantInt::IRConstantInt(int val)
    : IRConstant(const_cast<IRType*>(IRType::getPrimitiveType(IRType::IntTyID))), value(val) {
}

IRConstantInt* IRConstantInt::get(int val) {
    return new IRConstantInt(val);
}

void IRConstantInt::print(std::ostream &OS) const {
    OS << value;
}

// IRConstantFloat 实现
IRConstantFloat::IRConstantFloat(float val)
    : IRConstant(const_cast<IRType*>(IRType::getPrimitiveType(IRType::FloatTyID))), value(val) {
}

IRConstantFloat* IRConstantFloat::get(float val) {
    return new IRConstantFloat(val);
}

void IRConstantFloat::print(std::ostream &OS) const {
    OS << value;
}

// IRConstantDouble 实现
IRConstantDouble::IRConstantDouble(double val)
    : IRConstant(const_cast<IRType*>(IRType::getPrimitiveType(IRType::DoubleTyID))), value(val) {
}

IRConstantDouble* IRConstantDouble::get(double val) {
    return new IRConstantDouble(val);
}

void IRConstantDouble::print(std::ostream &OS) const {
    OS << value;
}

// IRConstantBool 实现
IRConstantBool::IRConstantBool(bool val)
    : IRConstant(const_cast<IRType*>(IRType::getPrimitiveType(IRType::BoolTyID))), value(val) {
}

IRConstantBool* IRConstantBool::get(bool val) {
    return new IRConstantBool(val);
}

void IRConstantBool::print(std::ostream &OS) const {
    OS << (value ? "true" : "false");
}

// IRConstantArray 实现
IRConstantArray::IRConstantArray(IRType *arrayType, const std::vector<IRConstant*> &elements)
    : IRConstant(arrayType), elements(elements) {
}

IRConstantArray* IRConstantArray::get(IRType *arrayType, const std::vector<IRConstant*> &elements) {
    return new IRConstantArray(arrayType, elements);
}

void IRConstantArray::print(std::ostream &OS) const {
    OS << "[";
    for (size_t i = 0; i < elements.size(); ++i) {
        if (i > 0) OS << ", ";
        elements[i]->print(OS);
    }
    OS << "]";
}