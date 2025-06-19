#include "IRUse.h"
#include "IRValue.h"
#include "IRUser.h"

IRUse::IRUse(IRValue *v, IRUser *user) : val(v), user(user) {
    if (val)
        val->addUse(*this);
}

IRUse::IRUse(const IRUse &u) : val(u.val), user(u.user) {
    if (val)
        val->addUse(*this);
}

IRUse::~IRUse() {
    if (val)
        val->killUse(*this);
}

void IRUse::set(IRValue *Val) {
    if (val)
        val->killUse(*this);
    val = Val;
    if (Val)
        Val->addUse(*this);
}