#pragma once

#include "LExprBaseVisitor.h"

namespace lexpr {

class EvalVisitor : public LExprBaseVisitor {
public:
    antlrcpp::Any visitMult(LExprParser::MultContext *ctx) override;
    antlrcpp::Any visitAdd(LExprParser::AddContext *ctx) override;
    antlrcpp::Any visitInt(LExprParser::IntContext *ctx) override;
};

}