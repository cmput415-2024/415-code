grammar Cymbol;

tokens {
  METHOD_DECL,  // function definition
  ARG_DECL,     // parameter
  BLOCK,
  VAR_DECL,
  ASSIGN,
  CALL,
  ELIST,        // expression list
  EXPR 	        // root of an expression
}

compilationUnit
    :   (methodDeclaration | varDeclaration)+
    ;

// START: method
methodDeclaration
    :   type ID '(' formalParameterList? ')' block
    ;
// END: method

formalParameter
    :   type ID
    ;

formalParameterList
    :   formalParameter (',' formalParameter)*
    ;

type:   'float'
    |   'int'
    |	'void'
    ;

// START: block
block
    :   '{' statement* '}'
    ;
// END: block

// START: var
varDeclaration
    :   type ID ('=' expression)? ';'
    ;
// END: var

statement
    :   block                       #blockStat
    |	varDeclaration              #varDeclarationStat
    |   'return' expression? ';'    #return
    |   ID '=' expression ';'       #assignment
    |   expression ';'              #expressionStat
    ;

expressionList
    :   expression (',' expression)*
    ;

expression // root of an expression tree
    :   expr
    ;

expr
    :   expr '(' expressionList? ')'    #call
    |   expr '+' expr                   #add
    |   ID                              #id
    |   INT                             #integer
    |   '(' expr ')'                    #paren
    ;

// LEXER RULES

ADD : '+';
RETURN : 'return';

ID  :   LETTER (LETTER | '0'..'9')*
    ;

fragment
LETTER  :   ('a'..'z' | 'A'..'Z')
    ;

INT :   '0'..'9'+
    ;

WS  :   (' '|'\r'|'\t'|'\n') -> skip
    ;

SL_COMMENT
    :   '//' ~('\r'|'\n')* '\r'? '\n' -> skip
    ;
