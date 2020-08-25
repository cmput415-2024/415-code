/***
 * Excerpt from "The Definitive ANTLR 4 Reference",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/tpantlr2 for more book information.
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

// It is important to note that this file, `src/Evaluator.cpp`, 
// has been added to `src/CMakeLists.txt`. This is necessary to tell
// CMake that this code needs to be compiled and linked with the rest
// of the project.

#include "Evaluator.h"

#include <string>

namespace lexpr {

void Evaluator::exitMult(LExprParser::MultContext *ctx) {
    int left = stack.top(); stack.pop();
    int right = stack.top(); stack.pop();
    stack.push( left * right );
}

void Evaluator::exitAdd(LExprParser::AddContext *ctx) {
    int left = stack.top(); stack.pop();
    int right = stack.top(); stack.pop();
    stack.push( left + right );
}

void Evaluator::exitInt(LExprParser::IntContext *ctx) {
    stack.push( std::stoi(ctx->INT()->getText()) );
}

}