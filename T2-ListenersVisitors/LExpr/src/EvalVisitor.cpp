#include "EvalVisitor.h"

#include <string>

namespace lexpr {

antlrcpp::Any EvalVisitor::visitMult(LExprParser::MultContext *ctx) {
    return visit(ctx->e(0)).as<int>() * visit(ctx->e(1)).as<int>();
}

antlrcpp::Any EvalVisitor::visitAdd(LExprParser::AddContext *ctx) {
    return visit(ctx->e(0)).as<int>() + visit(ctx->e(1)).as<int>();
}

antlrcpp::Any EvalVisitor::visitInt(LExprParser::IntContext *ctx) {
    return std::stoi(ctx->INT()->getText());
}

}