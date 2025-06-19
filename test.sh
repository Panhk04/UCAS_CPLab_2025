#!/bin/bash

prj_dir="/home/compiler06/cc"

compiler="$prj_dir/build/compiler"

cact_dir="$prj_dir/test/samples_lex_and_syntax"

errorNum=0  # 正确赋值，无空格

for file in "$cact_dir"/*.cact; do
    if [[ -f "$file" ]]; then
        filename=$(basename "$file")  # 修正引号闭合
        ans=$(echo "$filename" | grep -E "[0-9][0-9]_(true|false)" -o | grep -E "(true|false)" -o | tail -n 1)
        $compiler "$file" 1>"${file}.out" 2>/dev/null
        return_value=$?
        if [[ $return_value -ne 0 ]]; then
            out="false"
        elif [[ $return_value -eq 0 ]]; then
            out="true"
        else
            out="unknown return value"
        fi
        if [[ "$out" != "$ans" ]]; then
            echo "syntax test failed at $filename"  # 添加双引号避免空格问题
            echo "return value is $return_value"
            $compiler "$file" 1>/dev/null  2>&1
            errorNum=$((errorNum + 1))  # 正确递增变量
        fi
    fi
done

if [[ $errorNum -ne 0 ]]; then
    echo "syntax test failed!"
    exit 1
else
    echo "syntax test pass!"
fi

exit 0