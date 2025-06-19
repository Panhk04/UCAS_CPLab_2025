#ifndef COMPILER_IRUSE_H
#define COMPILER_IRUSE_H
#pragma once

class IRValue;
class IRUser;

class IRUse {
private:
    IRValue *val;
    IRUser *user;

public:
    IRUse(IRValue *v = nullptr, IRUser *user = nullptr);
    IRUse(const IRUse &u);
    ~IRUse();

    IRValue *get() const { return val; }
    void set(IRValue *Val);

    IRUser *getUser() const { return user; }

    operator IRValue*() const { return val; }
    IRValue *operator->() const { return val; }
    IRValue &operator*() const { return *val; }
};

#endif//COMPILER_IRUSE_H