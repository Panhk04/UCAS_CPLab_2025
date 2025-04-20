

# 编译原理研讨课实验一实验报告

[toc]

## 实验内容

1. 熟悉ANTLR的安装和使用
2. 完成词法分析器和语法分析器的设计

## 组员

- 潘泓锟
- 朱辰
- 郑舜泽

## 实验设计

### 1.编译器的目录结构

- src/
  - main.cpp: 编译器的主框架
- grammar/
  - hello.g4: ANTLR语法文件
  - HelloLexer.h
  - HelloLexer.cpp: 词法分析器
  - HelloParser.h
  - HelloParser.cpp: 语法分析器
  - HelloBaseVisitor.h
  - HelloBaseVisitor.cpp: 
  - HelloVisitor.h
  - HelloVisitor.cpp: 

### 2.表达式优先级的体现

在antlr中，优先级通过语法规则的前后顺序来体现，在语法描述文件中，先定义优先级高的规则，再定义优先级低的规则

以优先级1的PrimaryExp和优先级2的UnaryExp为例

```g4
primaryExp
    : '(' exp ')'
    | lVal
    | number
    ;

unaryExp
    : primaryExp
    | ('+'|'-'|'!') unaryExp
    | Ident '(' (funcRParams)? ')'
    ;
```

在上面的例子中，primaryExp的优先级高于unaryExp，因此在语法分析时，首先会匹配primaryExp，然后再匹配unaryExp


### 3.设计数值常量的词法规则

数值常量的词法规则如下，实现了整型和单精度浮点型两种数值常量

```bash

IntConst
    : DecimalConstant
    | OctalConstant
    | HexadecConstant
    ;

fragment DecimalConstant
    : '0'                          // 单独的数字0
    | NonzeroDigit Digit*          // 非零开头的多位数
    ;

fragment OctalConstant
    : '0' Octaldigit*
    ;

fragment HexadecConstant
    : Hexadecimalprefix Hexadecimaldigit+
    ;

CharConst
    : '"character"'
    ;

FloatConst
    : FracConst ExpPart? FloatSuf?
    | DigitSeq ExpPart FloatSuf?
    ;

Digit
    : '0'
    | NonzeroDigit
    ;

fragment NonzeroDigit
    : [1-9]
    ;

fragment Octaldigit
    : [0-7]
    ;    

fragment Hexadecimalprefix
    : '0' [xX]
    ;

fragment Hexadecimaldigit
    : [0-9a-fA-F]
    ;

fragment FracConst
    : DigitSeq? '.' DigitSeq
    | DigitSeq '.'
    ;

fragment ExpPart
    : [eE] Sign? DigitSeq
    ;

fragment Sign
    : [+-]
    ;

fragment DigitSeq
    : Digit+
    ;

fragment FloatSuf
    : [fF]
    ;

```

### 4.替换ANTLR的默认异常处理方法

## 实验过程

### 1.熟悉ANTLR的安装和使用

根据实验说明文档，解压并安装ANTLR

然后生成visitor代码

```bash
java -jar ../deps/antlr-4.13.1-complete.jar -Dlanguage=Cpp Hello.g4 -visitor -no-listener
```

### 编写语法描述文件(`Hello.g4`)

根据cact-spec中的语法描述文件，编写`Hello.g4`文件

声明&定义

```g4
/****** parser ******/
compUnit
    : ( decl | funcDef )+ EOF
    ;

decl
    : constDecl
    | varDecl
    ;

btype
    : 'int'
    | 'float'
    | 'char'
    ;

constDecl
    : 'const' btype constDef ( ',' constDef )* ';'
    ;

...
```

语句&表达式

```g4
block
    : '{' blockItem* '}'
    ;

blockItem
    : decl
    | stmt
    ;

stmt
    : lVal '=' exp ';'                        // assignStmt
    | (exp)? ';'                              // exprStmt
    | block                                   // blockStmt
    | 'return' exp? ';'                       // returnStmt
    | 'if' '(' cond ')' stmt ('else' stmt)?   // ifStmt
    | 'while' '(' cond ')' stmt               // whileStmt
    | 'break' ';'                             // breakStmt
    | 'continue' ';'                          // continueStmt
    ;

...
```

终结符

```g4
/****** lexer  ******/
Ident
    : [a-zA-Z_] [a-zA-Z0-9_]*
    ;

Newline
    : '\r' ('\n')?
    | '\n'
    ;

Whitespace
    : (' ' | '\t')+
    ;

LineComment
    : '//' ~[\r\n]*  
    ;
...
```

### 编写主框架`main.cpp`

依据提供的示例和官方的模板，在main.cpp中编写主框架，并添加一些错误处理

```cpp

int main(int argc, const char* argv[]) {

    if(argc < 2) {
        std::cerr << "[ERROR]source file miss" << std::endl;
        return 1;
    }

    std::ifstream stream;
    stream.open(argv[1]);

    if(!stream.is_open()) {
        std::cerr << "[ERROR]open file failed" << std::endl;
        return 1;
    }

    ANTLRInputStream input(stream);
    HelloLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    HelloParser parser(&tokens);

    tokens.fill();
    //for(auto token : tokens.getTokens()) {
    //    std::cout << "token: " << token->toString() << std::endl;
    //}
    //打印Laxer得到的token

    // tree::ParseTree *tree = parser.compUnit();
    // std::cout << "tree: " << tree->toStringTree(&parser) << std::endl;
    //打印parser得到的AST

    std::cerr << lexer.getNumberOfSyntaxErrors() << std::endl;
    std::cerr << parser.getNumberOfSyntaxErrors() << std::endl;

    if (lexer.getNumberOfSyntaxErrors() > 0 || parser.getNumberOfSyntaxErrors() > 0) {
        std::cerr << "[ERROR] total number"<<lexer.getNumberOfSyntaxErrors() + parser.getNumberOfSyntaxErrors() << std::endl;
        return 1;
    }

    return 0;
}
```

为了方便调试，添加了打印token和AST的代码，同时区分了cout流和cerr流来处理正常输出和错误输出



### 错误处理

为了识别是否存在语法错误，使用了antlr提供的`lexer.getNumberOfSyntaxErrors()`函数和`parser.getNumberOfSyntaxErrors()`来获取语法错误的数量，如果这些数量大于0，则表示存在语法错误。

### 在样例上进行测试

为了方便进行测试，编写了一个脚本文件来自动化进行所有样例的测试并输出错误结果。

```bash
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
``` 

## debug过程

### Ident优先级问题

在尝试用cact识别测试代码时，发现返回的语法树均为关键字本身，没有沿语法树向下遍历。

检查代码后发现是ident的优先级过高，导致关键字无法被识别，进而无法沿语法树向下匹配，因此调整了ident的优先级，后续就能得到正确的语法树返回。

### 左递归问题

在对代码进行编译时出现报错，显示代码中含有左递归内容，查找资料得知antlr文法中是不允许左递归出现的，因此按照理论课中的内容进行修改，修改后该部分能够成功编译。

### 关键字未定义问题

一开始我们只是遵照手册中给出的语法生成规则编写g4文件，忽略了cact自带的关键字，发现后也及时进行了补充：

```bash

Float
    : 'float'
    ;

If
    : 'if'
    ;

Int
    : 'int'
    ;

//......

```

### 初始化规则不完整

在最初将代码在测试点上运行时发现对所有测试点的输出结果均为错误，即返回值均为非零值，无法生成正确的语法输。在对照讲义对代码进行细致的检查之后，
发现其中一条初始化规则在定义时漏掉了一部分内容，错误代码如下：

```bash

constInitVal
    : constExp
    | '{' ( (',' constInitVal)*)? '}'
    ;

```

将代码补全后，可以通过大部分测试点。

### 初始化语句规则不正确

在解决了大部分问题后，发现最后剩下未能通过的测试点均是初始化变量时规则出现问题。

原本的规则如下：

```bash

constInitVal
    : constExp
    | '{' (constInitVal (',' constInitVal)*)? '}'
    ;

constExp
    : addExp
    ;

```

但是发现这会导致cact可以识别初始化中的非常量赋值，如"int a = b;"，"int a = 2 * 3;"等情况。

于是进行简单修改，将constExp修改如下：

```bash

constExp
    : number
    | '(' constExp ')'
    ;

```

这样就实现了仅常量初始化的效果，而正常的赋值则通过exp进行识别，并不受到影响。



## 实验结果

### 样例上运行结果

![alt text](tess_pass.png)

如图，当前的CACT可以正确通过所有给出的样例。

## 总结与反思

一开始接触CACT是非常手足无措的，因为我们从未接触过CACT语言，更没有使用过antlr工具，需要从头学习。

后续，我们小组成员同心协力按照给出的CACT语法文档完成了g4文件的初步编写。但是发现不知道如何检查错误、调试代码。后续也是通过编写cmake脚本实现了测试的简化。

同时，在这次实验中还遇到了一些问题，例如，尽管CACT语言是C语言的子集，但是在语法分析时，仍然需要注意一些细节问题，例如初值表达式必须是常数，这个问题我们在语法分析时没有考虑到，导致在测试时出现了一些错误。

## 参考文献

