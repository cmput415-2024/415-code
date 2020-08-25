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
