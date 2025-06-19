#ifndef COMPILER_IRUSER_H
#define COMPILER_IRUSER_H
#pragma once

#include "IRValue.h"
#include "IRUse.h"
#include <vector>

class IRUse;

class IRUser : public IRValue {
protected:
    std::vector<IRUse> Operands;

public:
    IRUser(IRType *Ty, ValueTy vty, const std::string &Name = "");
    virtual ~IRUser() = default;

    // Operand access methods
    unsigned getNumOperands() const { return Operands.size(); }
    
    IRValue *getOperand(unsigned i) const {
        if (i >= Operands.size()) return nullptr;
        return Operands[i].get();
    }
    
    void setOperand(unsigned i, IRValue *V) {
        if (i < Operands.size()) {
            Operands[i].set(V);
        }
    }
    
    void addOperand(IRValue *V) {
        Operands.emplace_back(V, this);
    }
    
    void removeLastOperand() {
        if (!Operands.empty()) {
            Operands.pop_back();
        }
    }

    void print(std::ostream &OS) const override;

    static inline bool classof(const IRUser *) { return true; }
    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::InstructionVal ||
               V->getValueType() == IRValue::FunctionVal ||
               V->getValueType() == IRValue::GlobalVariableVal;
    }
};

#endif//COMPILER_IRUSER_H