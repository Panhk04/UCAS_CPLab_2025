#include "IRGlobalValue.h"
#include <iostream>

IRGlobalValue::IRGlobalValue(IRType *Ty, ValueTy vty, LinkageTypes linkage, 
                             const std::string &Name, IRModule *parent)
    : IRUser(Ty, vty, Name), linkage(linkage), parent(parent) {
}

void IRGlobalValue::print(std::ostream &OS) const {
    OS << "global ";
    getType()->print(OS);
    OS << " " << getName();
}