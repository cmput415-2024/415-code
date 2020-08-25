/***
 * Excerpted from "Language Implementation Patterns",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/tpdsl for more book information.
 *
 * Disclaimer:
 * This is a derivative work produced exclusively for 
 * the University of Alberta, Canada as a supplement to the 
 * learning material in the course CMPUT 415 - Compiler Design.
 * 
 * Redistribution is forbidden in all circumstances. Use of this
 * code without explicit authorization from CMPUT 415
 * Teaching Staff is prohibited.
 * 
 * If this code is found in any public website or public repository, the
 * person finding it is kindly requested to immediately report, including 
 * the URL or other repository locating information, to the following email
 * address:
 *
 *          cmput415@ualberta.ca
***/

// The ASTBuilder class is a visitor that translates the functionality
// of the AST Construction facilities from the ANTLR3 grammar `Cymbol.g`
// from the slides/textbook to ANTLR4 and C++.

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