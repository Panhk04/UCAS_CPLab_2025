#ifndef COMPILER_CACT_H
#define COMPILER_CACT_H
#pragma once

// 数据类型枚举
enum DataType {
    VOID = 0,
    BOOL,
    INT,
    FLOAT,
    DOUBLE
};

// 符号类型枚举
enum SymbolType {
    CONST = 0,
    VAR,
    CONST_ARRAY,
    VAR_ARRAY,
    FUNC
};

#endif//COMPILER_CACT_H