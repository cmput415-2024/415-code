// START: header
grammar Cymbol; // my grammar is called Cymbol

// define a SymbolTable field in generated parser
compilationUnit // pass symbol table to start rule
    :   varDeclaration+ // recognize at least one variable declaration
    ;
// END: header

// START: type   
type
    :   'float'
    |   'int'
    ;
// END: type   

// START: decl
varDeclaration
    :   type ID ('=' expression)? ';' // E.g., "int i = 2;", "int i;"
    ;
// END: decl

expression
    :   primary ('+' primary)*
    ;

// START: primary
primary
    :   ID                  # primaryID // reference variable in an expression
    |   INT                 # primaryOther
    |   '(' expression ')'  # primaryOther
    ;
// END: primary

// LEXER RULES

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
