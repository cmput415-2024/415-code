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

#include "EvaluatorWithProps.h"

#include <string>

namespace lexpr {

void EvaluatorWithProps::exitS(LExprParser::SContext *ctx) {
    setValue(ctx, getValue(ctx->e())); // like: int s() { return e(); }
}

void EvaluatorWithProps::exitMult(LExprParser::MultContext *ctx) {
    int left = getValue(ctx->e(0));  // e '*' e   # Mult
    int right = getValue(ctx->e(1));
    setValue(ctx, left * right);
}

void EvaluatorWithProps::exitAdd(LExprParser::AddContext *ctx) {
    int left = getValue(ctx->e(0)); // e '+' e   # Add
    int right = getValue(ctx->e(1));
    setValue(ctx, left + right);
}

void EvaluatorWithProps::exitInt(LExprParser::IntContext *ctx) {
    std::string intText = ctx->INT()->getText(); // INT   # Int
    setValue(ctx, std::stoi(intText));
}

void EvaluatorWithProps::setValue(antlr4::tree::ParseTree *node, int value) {
    values.put(node, value);
}

int EvaluatorWithProps::getValue(antlr4::tree::ParseTree *node) {
    return values.get(node);
}

}