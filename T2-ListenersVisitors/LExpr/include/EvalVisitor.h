#pragma once

#include "LExprBaseVisitor.h"

namespace lexpr {

class EvalVisitor : public LExprBaseVisitor {
public:
    std::any visitMult(LExprParser::MultContext *ctx) override;
    std::any visitAdd(LExprParser::AddContext *ctx) override;
    std::any visitInt(LExprParser::IntContext *ctx) override;
};

}