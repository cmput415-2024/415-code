/***
 * Excerpted from "Language Implementation Patterns",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/tpdsl for more book information.
 *
 * Disclaimer:
 * This is a derivative work produced exclusively for 
 * the University of Alberta, Canada as a supplement to the 
 * learning material in the course CMPUT 415 - Compiler Design.
 * 
 * Redistribution is forbidden in all circumstances. Use of this
 * code without explicit authorization from CMPUT 415
 * Teaching Staff is prohibited.
 * 
 * If this code is found in any public website or public repository, the
 * person finding it is kindly requested to immediately report, including 
 * the URL or other repository locating information, to the following email
 * address:
 *
 *          cmput415@ualberta.ca
***/

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
