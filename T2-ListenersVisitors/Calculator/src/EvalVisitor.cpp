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

// It is important to note that this file, `src/EvalVisitor.cpp`, 
// has been added to `src/CMakeLists.txt`. This is necessary to tell
// CMake that this code needs to be compiled and linked with the rest
// of the project.

#include "EvalVisitor.h"

#include <iostream>
#include <string>

namespace calc {

/** ID '=' expr NEWLINE */
antlrcpp::Any EvalVisitor::visitAssign(LabeledExprParser::AssignContext *ctx) {
    std::string id = ctx->ID()->getText();	// id is left-hand side of '='
    int value = visit(ctx->expr());			// compute value of expression
    memory[id] = value;				        // store it in our memory
    return value;
}

/** expr NEWLINE */
antlrcpp::Any EvalVisitor::visitPrintExpr(LabeledExprParser::PrintExprContext *ctx) {
    int value = visit(ctx->expr());         // evaluate the expr child
    std::cout << value << '\n';             // print the result
    return 0;                               // return dummy value
}

/** INT */
antlrcpp::Any EvalVisitor::visitInt(LabeledExprParser::IntContext *ctx) {
    return std::stoi(ctx->INT()->getText());
}

/** ID */
antlrcpp::Any EvalVisitor::visitId(LabeledExprParser::IdContext *ctx) {
    std::string id = ctx->ID()->getText();
    auto it = memory.find(id);
    if (it != memory.end()) return it->second;
    return 0;
}

/** expr op=('*'|'/') expr */
antlrcpp::Any EvalVisitor::visitMulDiv(LabeledExprParser::MulDivContext *ctx) {
    int left = visit(ctx->expr(0));         // value of left expression
    int right = visit(ctx->expr(1));        // value of right expression
    if ( ctx->op->getType() == LabeledExprParser::MUL )
        return left * right;
    return left / right; // must be DIV
}

/** expr op=('+'|'-') expr */
antlrcpp::Any EvalVisitor::visitAddSub(LabeledExprParser::AddSubContext *ctx) {
    int left = visit(ctx->expr(0));         // value of left expression
    int right = visit(ctx->expr(1));        // value of right expression
    if ( ctx->op->getType() == LabeledExprParser::ADD )
        return left + right;
    return left - right; // must be SUB
}

/** '(' expr ')' */
antlrcpp::Any EvalVisitor::visitParens(LabeledExprParser::ParensContext *ctx) {
    return visit(ctx->expr());              // return child expr's value
}

} // namespace calc