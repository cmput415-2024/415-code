#pragma once

#include "LExprBaseListener.h"

#include <stack>

namespace lexpr {

class Evaluator : public LExprBaseListener {
public:
    std::stack<int> stack;
    void exitMult(LExprParser::MultContext *ctx) override;
    void exitAdd(LExprParser::AddContext *ctx) override;
    void exitInt(LExprParser::IntContext *ctx) override;
};

}