#ifndef COMPILER_IRDERIVEDTYPES_H
#define COMPILER_IRDERIVEDTYPES_H
#pragma once

#include "IRType.h"
#include <vector>

class IRFunctionType : public IRType {
private:
    std::vector<IRType *> paramTys;

public:
    IRFunctionType(IRType *Result, const std::vector<IRType *> &Params);
    
    IRType *getReturnType() const;
    unsigned getNumParams() const { return paramTys.size(); }
    IRType *getParamType(unsigned i) const { 
        return i < paramTys.size() ? paramTys[i] : nullptr; 
    }
    
    void print(std::ostream &OS) const override;
    
    static inline bool classof(const IRFunctionType *) { return true; }
    static inline bool classof(const IRType *T) {
        return T->getPrimitiveID() == FunctionTyID;
    }
};

class IRArrayType : public IRType {
private:
    IRType *elementType;
    unsigned numElements;

public:
    IRArrayType(IRType *ElementType, unsigned NumElements);
    
    IRType *getElementType() const { return elementType; }
    unsigned getNumElements() const { return numElements; }
    
    void print(std::ostream &OS) const override;
    
    static inline bool classof(const IRArrayType *) { return true; }
    static inline bool classof(const IRType *T) {
        return T->getPrimitiveID() == ArrayTyID;
    }
};

class IRPointerType : public IRType {
private:
    IRType *pointeeType;

public:
    IRPointerType(IRType *ElementType);
    
    IRType *getElementType() const { return pointeeType; }
    
    void print(std::ostream &OS) const override;
    
    static inline bool classof(const IRPointerType *) { return true; }
    static inline bool classof(const IRType *T) {
        return T->getPrimitiveID() == PointerTyID;
    }
};

#endif//COMPILER_IRDERIVEDTYPES_H