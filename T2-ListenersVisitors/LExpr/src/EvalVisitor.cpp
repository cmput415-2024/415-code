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

#include <string>

namespace lexpr {

antlrcpp::Any EvalVisitor::visitMult(LExprParser::MultContext *ctx) {
    return visit(ctx->e(0)).as<int>() * visit(ctx->e(1)).as<int>();
    // Alternatively, you may use casting instead of the .as<>() method.
}

antlrcpp::Any EvalVisitor::visitAdd(LExprParser::AddContext *ctx) {
    return visit(ctx->e(0)).as<int>() + visit(ctx->e(1)).as<int>();
}

antlrcpp::Any EvalVisitor::visitInt(LExprParser::IntContext *ctx) {
    return std::stoi(ctx->INT()->getText());
}

}