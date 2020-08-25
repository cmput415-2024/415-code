#pragma once

#include "CymbolBaseVisitor.h"

namespace nested {

class ASTBuilder : public CymbolBaseVisitor {
public:
    antlrcpp::Any visitCompilationUnit(CymbolParser::CompilationUnitContext *ctx) override;
    antlrcpp::Any visitMethodDeclaration(CymbolParser::MethodDeclarationContext *ctx) override;
    antlrcpp::Any visitFormalParameter(CymbolParser::FormalParameterContext *ctx) override;
    antlrcpp::Any visitFormalParameterList(CymbolParser::FormalParameterListContext *ctx) override;
    antlrcpp::Any visitType(CymbolParser::TypeContext *ctx) override;
    antlrcpp::Any visitBlock(CymbolParser::BlockContext *ctx) override;
    antlrcpp::Any visitVarDeclaration(CymbolParser::VarDeclarationContext *ctx) override;
    antlrcpp::Any visitBlockStat(CymbolParser::BlockStatContext *ctx) override;
    antlrcpp::Any visitVarDeclarationStat(CymbolParser::VarDeclarationStatContext *ctx) override;
    antlrcpp::Any visitReturn(CymbolParser::ReturnContext *ctx) override;
    antlrcpp::Any visitAssignment(CymbolParser::AssignmentContext *ctx) override;
    antlrcpp::Any visitExpressionStat(CymbolParser::ExpressionStatContext *ctx) override;
    antlrcpp::Any visitExpressionList(CymbolParser::ExpressionListContext *ctx) override;
    antlrcpp::Any visitExpression(CymbolParser::ExpressionContext *ctx) override;
    antlrcpp::Any visitAdd(CymbolParser::AddContext *ctx) override;
    antlrcpp::Any visitCall(CymbolParser::CallContext *ctx) override;
    antlrcpp::Any visitParen(CymbolParser::ParenContext *ctx) override;
    antlrcpp::Any visitId(CymbolParser::IdContext *ctx) override;
    antlrcpp::Any visitInteger(CymbolParser::IntegerContext *ctx) override;
};

} // namespace nested