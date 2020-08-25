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

// `pragma once` is an alterative to the traditional ifndef include guards.
// It is a non-standard but widely supported preprocessor directive.
#pragma once

#include "LabeledExprBaseVisitor.h"

#include <map>

namespace calc {

// Note the special return types of the visit functions: antlrcpp::Any
// As the name implies, it means that the function can return "Any[thing]".
// Just make sure to cast the result to the correct type before using it.

class EvalVisitor : public LabeledExprBaseVisitor {
public:
	/** "memory" for our calculator; variable/value pairs go here */
	std::map<std::string, int> memory;

	/** ID '=' expr NEWLINE */
	antlrcpp::Any visitAssign(LabeledExprParser::AssignContext *ctx) override;

	/** expr NEWLINE */
	antlrcpp::Any visitPrintExpr(LabeledExprParser::PrintExprContext *ctx) override;

    /** INT */
    antlrcpp::Any visitInt(LabeledExprParser::IntContext *ctx) override;

    /** ID */
    antlrcpp::Any visitId(LabeledExprParser::IdContext *ctx) override;

    /** expr op=('*'|'/') expr */
    antlrcpp::Any visitMulDiv(LabeledExprParser::MulDivContext *ctx) override;

    /** expr op=('+'|'-') expr */
    antlrcpp::Any visitAddSub(LabeledExprParser::AddSubContext *ctx) override;

    /** '(' expr ')' */
    antlrcpp::Any visitParens(LabeledExprParser::ParensContext *ctx) override;
};

}