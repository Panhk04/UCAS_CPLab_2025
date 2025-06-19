#ifndef COMPILER_IRARGUMENT_H
#define COMPILER_IRARGUMENT_H
#pragma once

#include "IRValue.h"
#include <string>

class IRFunction;

class IRArgument : public IRValue {
private:
    IRFunction *parent;

public:
    IRArgument(IRType *Ty, const std::string &Name = "", IRFunction *Par = nullptr);
    virtual ~IRArgument() = default;

    void setParent(IRFunction *parent) { this->parent = parent; }
    IRFunction *getParent() const { return parent; }

    void print(std::ostream &OS) const override;

    static inline bool classof(const IRArgument *) { return true; }
    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::ArgumentVal;
    }
};

#endif//COMPILER_IRARGUMENT_H