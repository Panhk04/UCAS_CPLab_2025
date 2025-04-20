grammar Hello;

@header {
    #include <vector>
    #include <string>
}
//test
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

varDecl
    : btype varDef (',' varDef)* ';'
    ;

constDef
    : Ident ('[' IntConst ']')* '=' constInitVal
    ;

constInitVal
    : constExp
    | '{' (constInitVal (',' constInitVal)*)? '}'
    ;

// fix.
varDef
    : Ident ('[' IntConst ']')* ('=' constInitVal)?
    ;

funcDef
    : funcType Ident '(' funcFParams? ')' block
    ;

funcType
    : 'void'
    | btype
    ;

funcFParams
    : funcFParam (',' funcFParam)*
    ;

funcFParam
    : btype Ident ('[' IntConst? ']' ('[' IntConst ']')*)?
    ;

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

lVal
    : Ident ('[' exp ']')*
    ;

exp
    : addExp
    ;
/*
constExp
    : addExpConst
    ;
*/

constExp
    : number             // 仅允许字面值
    | '(' constExp ')'   // 允许括号包裹
    ;

addExpConst
    : mulExpConst ( ('+'|'-') mulExpConst )*
    ;

mulExpConst
    : unaryExpConst ( ('*'|'/'|'%') unaryExpConst )*
    ;

unaryExpConst
    : ('+'|'-'|'!') unaryExpConst
    | primaryExpConst
    ;

primaryExpConst
    : '(' constExp ')'
    | number
    ;

cond
    : lOrExp
    ;

number
    : IntConst
    | CharConst
    | FloatConst
    ;

funcRParams
    : exp (',' exp)*
    ;
    
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

mulExp
    : unaryExp ( ('*'|'/'|'%') unaryExp )*
    ;

addExp
    : mulExp ( ('+'|'-') mulExp )*
    ;

relExp   
    : addExp ( ('<'|'>'|'<='|'>=') addExp )?
    ;

eqExp    
    : relExp ( ('=='|'!=') relExp )?
    ;

lAndExp  
    : eqExp ( '&&' eqExp )*
    ;

lOrExp   
    : lAndExp ( '||' lAndExp )* 
    ;



/****** lexer  ******/
Whitespace
    : (' ' | '\t')+ -> skip
    ;

Newline
    : ('\r' ('\n')? | '\n') -> skip
    ;

LineComment
    : '//' ~[\r\n]* -> skip
    ;

BlockComment
    : '/*' .*? '*/' -> skip
    ;

Bool
    : 'bool'
    ;

Break
    : 'break'
    ;

Const
    : 'const'
    ;

Continue
    : 'continue'
    ;

Double
    : 'double'
    ;

Else
    : 'else'
    ;

False
    : 'false'
    ;

Float
    : 'float'
    ;

If
    : 'if'
    ;

Int
    : 'int'
    ;

Return
    : 'return'
    ;

True
    : 'true'
    ;

Void
    : 'void'
    ;

While
    : 'while'
    ;

LeftParen
    : '('
    ;

RightParen
    : ')'
    ;

LeftBracket
    : '['
    ;

RightBracket
    : ']'
    ;

LeftBrace
    : '{'
    ;

RightBrace
    : '}'
    ;

LessEqual
    : '<='
    ;

GreaterEqual
    : '>='
    ;

Less
    : '<'
    ;

Greater
    : '>'
    ;

Plus
    : '+'
    ;

Minus
    : '-'
    ;

Star
    : '*'
    ;

Div
    : '/'
    ;

Mod
    : '%'
    ;

AndAnd
    : '&&'
    ;

OrOr
    : '||'
    ;

Not
    : '!'
    ;

Semi
    : ';'
    ;

Comma
    : ','
    ;

Assign
    : '='
    ;

Equal
    : '=='
    ;

NotEqual
    : '!='
    ;

Dot
    : '.'
    ;

Ident
    : [a-zA-Z_] [a-zA-Z0-9_]*
    ;

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

character
    :
    ;
/*
character
    : EscapeSeq           // 匹配转义字符（如 \n, \t 等）
    | ~[\r\n'\\]          // 匹配非换行符、非单引号、非反斜杠的任意ASCII字符
    ;

fragment EscapeSeq
    : '\\' [nrt0'"\\]  // 匹配 \n, \r, \t, \0, \', \", \\
    ;
*/

