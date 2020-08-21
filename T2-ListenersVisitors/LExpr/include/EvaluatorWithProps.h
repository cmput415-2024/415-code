#pragma once

#include "LExprBaseListener.h"

namespace lexpr {

/** Sample "calculator" using property of nodes */
class EvaluatorWithProps : public LExprBaseListener {
public:
    /** maps nodes to integers with Map<ParseTree,Integer> */
    antlr4::tree::ParseTreeProperty<int> values;

    /** Need to pass e's value out of rule s : e ; */
    void exitS(LExprParser::SContext *ctx) override;
    void exitMult(LExprParser::MultContext *ctx) override;
    void exitAdd(LExprParser::AddContext *ctx) override;
    void exitInt(LExprParser::IntContext *ctx) override;

    void setValue(antlr4::tree::ParseTree *node, int value);
    int getValue(antlr4::tree::ParseTree *node);
};

}