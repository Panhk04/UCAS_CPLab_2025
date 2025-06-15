#ifndef COMPILER_IRVALUE_H
#define COMPILER_IRVALUE_H

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "IRUse.h"

class IRType;

class IRConstant;

class IRArgument;

class IRInstruction;

class IRBasicBlock;

class IRGlobalValue;

class IRFunction;

class IRGlobalVariable;

class TemporaryVariable;

class Register;

class IRValue {
public:
    enum ValueTy {
        TypeVal,
        ConstantVal,
        ArgumentVal,
        InstructionVal,
        BasicBlockVal,
        FunctionVal,
        GlobalVariableVal,
    };

private:
    std::vector<IRUse *> Uses;
    std::string name;
    IRType *ty;
    ValueTy vTy;
    TemporaryVariable *tempVar;

public:
    //void operator=(const IRValue &) = delete;
    //IRValue(const IRValue &) = delete;
    IRValue(IRType *Ty, ValueTy vty, std::string name = "");

    virtual ~IRValue() = default;

    virtual void printPrefixName(std::ostream &OS) const {};

    virtual void print(std::ostream &OS) const = 0;

    IRType *getType() const { return ty; }

    inline bool hasName() const { return name != ""; }

    inline const std::string &getName() const { return name; }

    void setName(std::string Name) { name = std::move(Name); }

    inline ValueTy getValueType() const { return vTy; }

    void replaceAllUsesWith(IRValue *V);

    /**
     * add Use in Uses. It should only be used by the Use class
     * @param U
     */
    void addUse(IRUse &U) {
        Uses.push_back(&U);
    }

    /**
     * delete all Use* in Uses which equals &U. It should only be used by ths Use class
     * @param U
     */
    void killUse(IRUse &U) {
        auto ptr = std::find(Uses.begin(), Uses.end(), &U);
        Uses.erase(ptr);
    }

    std::vector<IRUse *> getUses() const {
        return Uses;
    }

    void setTempVar(TemporaryVariable *tempVar);

    TemporaryVariable *getTempVar();

    virtual Register* getReg() { return nullptr; }
};

#endif//COMPILER_IRVALUE_H
