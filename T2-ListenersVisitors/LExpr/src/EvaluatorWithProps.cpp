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