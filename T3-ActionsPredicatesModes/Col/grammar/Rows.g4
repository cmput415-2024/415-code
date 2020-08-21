grammar Rows;

@header {
#include <iostream>
}

@parser::members {
int col;
RowsParser(antlr4::TokenStream *input, int col) : RowsParser(input) {
    this->col = col;
}
}

file: (row NL)+ ;

row
locals [int i=0]
    : (   STUFF
          {
          $i++;
          if ( $i == col ) std::cout << $STUFF.text << '\n';
          }
      )+
    ;

TAB  :  '\t' -> skip ;   // match but don't pass to the parser
NL   :  '\r'? '\n' ;     // match and pass to the parser
STUFF:  ~[\t\r\n]+ ;     // match any chars except tab, newline
