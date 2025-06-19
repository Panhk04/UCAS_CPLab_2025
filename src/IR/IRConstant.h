#ifndef COMPILER_IRCONSTANT_H
#define COMPILER_IRCONSTANT_H
#pragma once

#include "IRValue.h"
#include "IRType.h"
#include <string>
#include <vector>

class IRType;

class IRConstant : public IRValue {
public:
    IRConstant(IRType *Ty, const std::string &Name = "");
    virtual ~IRConstant() = default;

    void print(std::ostream &OS) const override;

    static inline bool classof(const IRConstant *) { return true; }
    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::ConstantVal;
    }
};

class IRConstantInt : public IRConstant {
private:
    int value;

public:
    IRConstantInt(int val);
    
    static IRConstantInt* get(int val);
    int getValue() const { return value; }
    
    void print(std::ostream &OS) const override;
    
    static inline bool classof(const IRConstantInt *) { return true; }
    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::ConstantVal;
    }
};

class IRConstantFloat : public IRConstant {
private:
    float value;

public:
    IRConstantFloat(float val);
    
    static IRConstantFloat* get(float val);
    float getValue() const { return value; }
    
    void print(std::ostream &OS) const override;
    
    static inline bool classof(const IRConstantFloat *) { return true; }
    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::ConstantVal;
    }
};

class IRConstantDouble : public IRConstant {
private:
    double value;

public:
    IRConstantDouble(double val);
    
    static IRConstantDouble* get(double val);
    double getValue() const { return value; }
    
    void print(std::ostream &OS) const override;
    
    static inline bool classof(const IRConstantDouble *) { return true; }
    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::ConstantVal;
    }
};

class IRConstantBool : public IRConstant {
private:
    bool value;

public:
    IRConstantBool(bool val);
    
    static IRConstantBool* get(bool val);
    bool getValue() const { return value; }
    
    void print(std::ostream &OS) const override;
    
    static inline bool classof(const IRConstantBool *) { return true; }
    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::ConstantVal;
    }
};

class IRConstantArray : public IRConstant {
private:
    std::vector<IRConstant*> elements;

public:
    IRConstantArray(IRType *arrayType, const std::vector<IRConstant*> &elements);
    
    static IRConstantArray* get(IRType *arrayType, const std::vector<IRConstant*> &elements);
    const std::vector<IRConstant*>& getElements() const { return elements; }
    
    void print(std::ostream &OS) const override;
    
    static inline bool classof(const IRConstantArray *) { return true; }
    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::ConstantVal;
    }
};

#endif//COMPILER_IRCONSTANT_H