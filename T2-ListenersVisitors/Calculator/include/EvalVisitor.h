#pragma once

#include "LabeledExprBaseVisitor.h"

#include <map>

namespace calc {

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