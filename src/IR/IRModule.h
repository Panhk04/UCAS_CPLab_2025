#ifndef COMPILER_IRMODULE_H
#define COMPILER_IRMODULE_H
#pragma once

#include <string>
#include <vector>

#include "IRFunction.h"
#include "IRGlobalVariable.h"

class IRGlobalVariable;
class FunctionType;

class IRModule {
private:
    std::string name;
    std::vector<IRFunction *> funcList;
    std::vector<IRGlobalVariable *> varList;

public:
    explicit IRModule(std::string name);

    void setName(std::string &Name){ name = Name; };
    std::string &getName(){ return name; };

    void addGlobalVariable(IRGlobalVariable *var);
    void addFunction(IRFunction *func);

    IRFunction *getFunction(const std::string &name);

    IRFunction *getMainFunction();

    const std::vector<IRFunction *> &getFuncList() const;

    const std::vector<IRGlobalVariable *> &getVarList() const;

    void print(std::ostream &OS);
};


#endif//COMPILER_IRMODULE_H
