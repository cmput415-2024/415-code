grammar LabeledExpr;
prog: stat+ ;
stat: expr NEWLINE              # printExpr
    | ID '=' expr NEWLINE       # assign
    | NEWLINE                   # blank
    ;
expr: expr op=('*'|'/') expr    # MulDiv
    | expr op=('+'|'-') expr    # AddSub
    | INT                       # int
    | ID                        # id
    | '(' expr ')'              # parens
    ;
MUL: '*' ;              // define token name for operator literals
DIV: '/' ;              // to refer to token names as constants
ADD: '+' ;              // in visitor
SUB: '-' ;
ID: [a-zA-Z]+ ;
INT: [0-9]+ ;
NEWLINE: '\r'?'\n' ;    // return newlines to parser
WS: [ \t]+ -> skip ;