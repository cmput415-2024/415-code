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