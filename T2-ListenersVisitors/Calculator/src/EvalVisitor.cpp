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

}