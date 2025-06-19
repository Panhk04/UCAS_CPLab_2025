#include "IRUser.h"
#include <iostream>

IRUser::IRUser(IRType *Ty, ValueTy vty, const std::string &Name)
    : IRValue(Ty, vty, Name) {
}

void IRUser::print(std::ostream &OS) const {
    OS << "user ";
    getType()->print(OS);
    OS << " " << getName();
}