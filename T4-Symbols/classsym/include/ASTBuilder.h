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

namespace classsym {

class ASTBuilder : public CymbolBaseVisitor {
public:
    std::any visitCompilationUnit(CymbolParser::CompilationUnitContext *ctx) override;
    std::any visitStructDeclaration(CymbolParser::StructDeclarationContext *ctx) override;
    std::any visitClassDeclaration(CymbolParser::ClassDeclarationContext *ctx) override;
    std::any visitMethodDeclaration(CymbolParser::MethodDeclarationContext *ctx) override;
    std::any visitFormalParameter(CymbolParser::FormalParameterContext *ctx) override;
    std::any visitFormalParameterList(CymbolParser::FormalParameterListContext *ctx) override;
    std::any visitType(CymbolParser::TypeContext *ctx) override;
    std::any visitVisibility(CymbolParser::VisibilityContext *ctx) override;
    std::any visitBlock(CymbolParser::BlockContext *ctx) override;
    std::any visitDeclBlock(CymbolParser::DeclBlockContext *ctx) override;
    std::any visitVarDeclaration(CymbolParser::VarDeclarationContext *ctx) override;
    std::any visitBlockStat(CymbolParser::BlockStatContext *ctx) override;
    std::any visitVarDeclarationStat(CymbolParser::VarDeclarationStatContext *ctx) override;
    std::any visitStructDeclarationStat(CymbolParser::StructDeclarationStatContext *ctx) override;
    std::any visitReturn(CymbolParser::ReturnContext *ctx) override;
    std::any visitAssignment(CymbolParser::AssignmentContext *ctx) override;
    std::any visitMemberAssignment(CymbolParser::MemberAssignmentContext *ctx) override;
    std::any visitExpressionStat(CymbolParser::ExpressionStatContext *ctx) override;
    std::any visitExpressionList(CymbolParser::ExpressionListContext *ctx) override;
    std::any visitExpression(CymbolParser::ExpressionContext *ctx) override;
    std::any visitAdd(CymbolParser::AddContext *ctx) override;
    std::any visitCall(CymbolParser::CallContext *ctx) override;
    std::any visitParen(CymbolParser::ParenContext *ctx) override;
    std::any visitId(CymbolParser::IdContext *ctx) override;
    std::any visitMember(CymbolParser::MemberContext *ctx) override;
    std::any visitMemberExpr(CymbolParser::MemberExprContext *ctx) override;
    std::any visitInteger(CymbolParser::IntegerContext *ctx) override;
};

} // namespace classsym
