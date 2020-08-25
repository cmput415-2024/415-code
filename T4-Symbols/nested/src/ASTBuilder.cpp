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

#include "ASTBuilder.h"

#include "AST.h"

namespace nested {

antlrcpp::Any ASTBuilder::visitCompilationUnit(CymbolParser::CompilationUnitContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>();
    for ( auto *child : ctx->children ) {
        t->addChild(visit(child));
    }
    return t;
}

/* ^(METHOD_DECL type ID formalParameters? block) */
antlrcpp::Any ASTBuilder::visitMethodDeclaration(CymbolParser::MethodDeclarationContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::METHOD_DECL);
    t->addChild(visit(ctx->type()));
    t->addChild(std::make_shared<AST>(ctx->ID()->getSymbol()));
    if ( ctx->formalParameterList() ) {
        t->addChild(visit(ctx->formalParameterList()));
    } else {
        t->addChild(std::make_shared<AST>()); // add empty nil node
    }
    t->addChild(visit(ctx->block()));
    return t;
}

/* ^(ARG_DECL type ID) */
antlrcpp::Any ASTBuilder::visitFormalParameter(CymbolParser::FormalParameterContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::ARG_DECL);
    t->addChild(visit(ctx->type()));
    t->addChild(std::make_shared<AST>(ctx->ID()->getSymbol()));
    return t;
}

/* ^(ARG_DECL type ID)+ */
antlrcpp::Any ASTBuilder::visitFormalParameterList(CymbolParser::FormalParameterListContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>();
    for ( auto *param : ctx->formalParameter() ) {
        t->addChild(visit(param));
    }
    return t;
}

antlrcpp::Any ASTBuilder::visitType(CymbolParser::TypeContext *ctx) {
    return std::make_shared<AST>(ctx->getStart()); // make AST node from the first token in this context
}

/* ^(BLOCK statement*) */
antlrcpp::Any ASTBuilder::visitBlock(CymbolParser::BlockContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::BLOCK);
    for (auto *stat : ctx->statement()) {
        t->addChild(visit(stat));
    }
    return t;
}

/* ^(VAR_DECL type ID expression?) */
antlrcpp::Any ASTBuilder::visitVarDeclaration(CymbolParser::VarDeclarationContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::VAR_DECL);
    t->addChild(visit(ctx->type()));
    t->addChild(std::make_shared<AST>(ctx->ID()->getSymbol()));
    if ( ctx->expression() ) t->addChild(visit(ctx->expression()));
    return t;
}

antlrcpp::Any ASTBuilder::visitBlockStat(CymbolParser::BlockStatContext *ctx) {
    return visit(ctx->block());
}

antlrcpp::Any ASTBuilder::visitVarDeclarationStat(CymbolParser::VarDeclarationStatContext *ctx) {
    return visit(ctx->varDeclaration());
}

/* ^(RETURN expression?) */
antlrcpp::Any ASTBuilder::visitReturn(CymbolParser::ReturnContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::RETURN);
    if ( ctx->expression() ) t->addChild(visit(ctx->expression()));
    return t;
}

/* ^(ASSIGN postfixExpression expression) */
antlrcpp::Any ASTBuilder::visitAssignment(CymbolParser::AssignmentContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::ASSIGN);
    t->addChild(std::make_shared<AST>(ctx->ID()->getSymbol()));
    t->addChild(visit(ctx->expression()));
    return t;
}

antlrcpp::Any ASTBuilder::visitExpressionStat(CymbolParser::ExpressionStatContext *ctx) {
    return visit(ctx->expression());
}

/* ^(ELIST expression+) */
antlrcpp::Any ASTBuilder::visitExpressionList(CymbolParser::ExpressionListContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::ELIST);
    for ( auto *expr : ctx->expression() ) {
        t->addChild(visit(expr));
    }
    return t;
}

/* ^(EXPR expr) */
antlrcpp::Any ASTBuilder::visitExpression(CymbolParser::ExpressionContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::EXPR);
    t->addChild(visit(ctx->expr()));
    return t;
}

/* ^(ADD expr expr) */
antlrcpp::Any ASTBuilder::visitAdd(CymbolParser::AddContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::ADD);
    t->addChild(visit(ctx->expr(0)));
    t->addChild(visit(ctx->expr(1)));
    return t;
}

/* ^(CALL expr expressionList) */
antlrcpp::Any ASTBuilder::visitCall(CymbolParser::CallContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::CALL);
    t->addChild(visit(ctx->expr()));
    if ( ctx->expressionList() ) t->addChild(visit(ctx->expressionList()));
    return t;
}

antlrcpp::Any ASTBuilder::visitParen(CymbolParser::ParenContext *ctx) {
    return visit(ctx->expr());
}

/* ID */
antlrcpp::Any ASTBuilder::visitId(CymbolParser::IdContext *ctx) {
    return std::make_shared<AST>(ctx->ID()->getSymbol());
}

/* INT */
antlrcpp::Any ASTBuilder::visitInteger(CymbolParser::IntegerContext *ctx) {
    return std::make_shared<AST>(ctx->INT()->getSymbol());
}

} // namespace nested