#include "IRGlobalVariable.h"
#include "IR/IRDerivedTypes.h"
#include "IRConstant.h"
#include <iostream>
void IRGlobalVariable::setParent(IRModule *parent) {
    Parent = parent;
}

void IRGlobalVariable::printPrefixName(std::ostream &OS) const{
    OS << "@" << this->getName();
}

void IRGlobalVariable::print(std::ostream &OS) const {
    /******打印module_name******/
    this->printPrefixName(OS);
    OS << " = global ";
    if(this->Linkage == AppendingLinkage)
        OS << "privateFuncVarArray ";
    else if(this->Linkage == ExternalLinkage)
        OS << "externalFuncConstArray ";
    this->getInitializer()->print(OS); //获得初始化use的value值，并进行打印

    this->getType()->IRpointerPrintAlign(OS);
    OS << std::endl;
}

IRGlobalVariable::IRGlobalVariable(IRType *Ty, bool isConstant, IRGlobalValue::LinkageTypes Linkage, IRConstant *Initializer, const std::string &Name, IRModule *Parent, bool isinitial)
    : IRGlobalValue(new IRPointerType(Ty), IRValue::GlobalVariableVal, Linkage, Name), isConstantGlobal(isConstant), isinitial(isinitial) {
    if (Initializer) {
        Operands.emplace_back(dynamic_cast<IRValue *>(Initializer), this);
    }
    if (Parent) {
        Parent->addGlobalVariable(this);
    }
}

bool IRGlobalVariable::isIsinitial() const {
    return isinitial;
}
