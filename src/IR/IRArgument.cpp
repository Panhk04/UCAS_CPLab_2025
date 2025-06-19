#include "IRArgument.h"
#include <iostream>

IRArgument::IRArgument(IRType *Ty, const std::string &Name, IRFunction *Par)
    : IRValue(Ty, IRValue::ArgumentVal, Name), parent(Par) {
}

void IRArgument::print(std::ostream &OS) const {
    getType()->print(OS);
    OS << " " << getName();
}