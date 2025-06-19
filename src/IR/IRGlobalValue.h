#ifndef COMPILER_IRGLOBALVALUE_H
#define COMPILER_IRGLOBALVALUE_H
#pragma once

#include "IRConstant.h"
#include "IRUser.h"
#include <string>

class IRModule;

class IRGlobalValue : public IRUser {
public:
    enum LinkageTypes {
        ExternalLinkage = 0,
        AvailableExternallyLinkage,
        LinkOnceAnyLinkage,
        LinkOnceODRLinkage,
        WeakAnyLinkage,
        WeakODRLinkage,
        AppendingLinkage,
        InternalLinkage,
        PrivateLinkage,
        ExternalWeakLinkage,
        CommonLinkage
    };

private:
    LinkageTypes linkage;
    IRModule *parent;

public:
    IRGlobalValue(IRType *Ty, ValueTy vty, LinkageTypes linkage, 
                  const std::string &Name = "", IRModule *parent = nullptr);
    
    virtual ~IRGlobalValue() = default;

    LinkageTypes getLinkage() const { return linkage; }
    void setLinkage(LinkageTypes LT) { linkage = LT; }

    IRModule *getParent() const { return parent; }
    void setParent(IRModule *parent) { this->parent = parent; }

    bool hasExternalLinkage() const {
        return linkage == ExternalLinkage;
    }

    bool hasInternalLinkage() const {
        return linkage == InternalLinkage;
    }

    bool hasPrivateLinkage() const {
        return linkage == PrivateLinkage;
    }

    void print(std::ostream &OS) const override;

    static inline bool classof(const IRGlobalValue *) { return true; }
    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::FunctionVal ||
               V->getValueType() == IRValue::GlobalVariableVal;
    }
};

#endif//COMPILER_IRGLOBALVALUE_H