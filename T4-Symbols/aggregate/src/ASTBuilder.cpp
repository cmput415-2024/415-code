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

namespace aggregate {

std::any ASTBuilder::visitCompilationUnit(CymbolParser::CompilationUnitContext *ctx) {
    std::cerr << "visitCompilationUnit enter" << std::endl;
    std::shared_ptr<AST> t = std::make_shared<AST>();
    for ( auto *child : ctx->children ) {
        t->addChild(visit(child));
    }
    std::cerr << "visitCompilationUnit exit" << std::endl;
    return t;
}

/* ^(METHOD_DECL type ID formalParameters? block) */
std::any ASTBuilder::visitMethodDeclaration(CymbolParser::MethodDeclarationContext *ctx) {
    std::cerr << "visitMethodDeclaration enter line " << ctx->getStart()->getLine() << std::endl;
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::METHOD_DECL);
    t->addChild(visit(ctx->type()));
    t->addChild(std::make_shared<AST>(ctx->ID()->getSymbol()));
    if ( ctx->formalParameterList() ) {
        t->addChild(visit(ctx->formalParameterList()));
    } else {
        t->addChild(std::make_shared<AST>()); // add empty nil node
    }
    t->addChild(visit(ctx->block()));

    std::cerr << "visitMethodDeclaration exit line " << ctx->getStart()->getLine() << std::endl;
    return t;
}

/* ^(ARG_DECL type ID) */
std::any ASTBuilder::visitFormalParameter(CymbolParser::FormalParameterContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::ARG_DECL);
    t->addChild(visit(ctx->type()));
    t->addChild(std::make_shared<AST>(ctx->ID()->getSymbol()));
    return t;
}

/* ^(ARG_DECL type ID)+ */
std::any ASTBuilder::visitFormalParameterList(CymbolParser::FormalParameterListContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>();
    for ( auto *param : ctx->formalParameter() ) {
        t->addChild(visit(param));
    }
    return t;
}

std::any ASTBuilder::visitType(CymbolParser::TypeContext *ctx) {
    std::shared_ptr<AST> t;
    if (ctx->ID())
        t = std::make_shared<AST>(ctx->ID()->getSymbol());
    else 
        t = std::make_shared<AST>(ctx->getStart()); // make AST node from the first token in this context
    return t;
}

/* ^(BLOCK statement*) */
std::any ASTBuilder::visitBlock(CymbolParser::BlockContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::BLOCK, ctx->start->getLine());
    for (auto *stat : ctx->statement()) {
        t->addChild(visit(stat));
    }
    return t;
}

/* ^(DECL_BLOCK declaration*) */
std::any ASTBuilder::visitDeclBlock(CymbolParser::DeclBlockContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::DECL_BLOCK);
    for (auto *decl : ctx->declaration()) {
        t->addChild(visit(decl));
    }
    return t;
}

/* ^(VAR_DECL type ID expression?) */
std::any ASTBuilder::visitVarDeclaration(CymbolParser::VarDeclarationContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::VAR_DECL);
    t->addChild(visit(ctx->type()));
    t->addChild(std::make_shared<AST>(ctx->ID()->getSymbol()));
    if ( ctx->expression() ) t->addChild(visit(ctx->expression()));
    return t;
}

/* ^(struct ID DECL_BLOCK) */
std::any ASTBuilder::visitStructDeclaration(CymbolParser::StructDeclarationContext *ctx) {
    std::cerr << "visitStructDeclaration " << ctx->ID()->getText()
              << " line " << ctx->getStart()->getLine() << std::endl;
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::STRUCT_DECL);
    t->addChild(std::make_shared<AST>(ctx->ID()->getSymbol()));
    t->addChild(visit(ctx->declBlock()));
    return t;
}

std::any ASTBuilder::visitBlockStat(CymbolParser::BlockStatContext *ctx) {
    return visit(ctx->block());
}

std::any ASTBuilder::visitVarDeclarationStat(CymbolParser::VarDeclarationStatContext *ctx) {
    return visit(ctx->varDeclaration());
}

std::any ASTBuilder::visitStructDeclarationStat(CymbolParser::StructDeclarationStatContext *ctx) {
    return visit(ctx->structDeclaration());
}

/* ^(RETURN expression?) */
std::any ASTBuilder::visitReturn(CymbolParser::ReturnContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::RETURN);
    if ( ctx->expression() ) t->addChild(visit(ctx->expression()));
    return t;
}

/* ^(ASSIGN postfixExpression expression) */
std::any ASTBuilder::visitAssignment(CymbolParser::AssignmentContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::ASSIGN, ctx->start->getLine());
    t->addChild(std::make_shared<AST>(ctx->ID()->getSymbol()));
    t->addChild(visit(ctx->expression()));
    return t;
}

/* ^(ASSIGN MEMBER expression) */
std::any ASTBuilder::visitMemberAssignment(CymbolParser::MemberAssignmentContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::ASSIGN, ctx->start->getLine());
    t->addChild(visit(ctx->member()));
    t->addChild(visit(ctx->expression()));
    return t;
}

std::any ASTBuilder::visitExpressionStat(CymbolParser::ExpressionStatContext *ctx) {
    return visit(ctx->expression());
}

/* ^(ELIST expression+) */
std::any ASTBuilder::visitExpressionList(CymbolParser::ExpressionListContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::ELIST);
    for ( auto *expr : ctx->expression() ) {
        t->addChild(visit(expr));
    }
    return t;
}

/* ^(EXPR expr) */
std::any ASTBuilder::visitExpression(CymbolParser::ExpressionContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::EXPR);
    t->addChild(visit(ctx->expr()));
    return t;
}

/* ^(ADD expr expr) */
std::any ASTBuilder::visitAdd(CymbolParser::AddContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::ADD);
    t->addChild(visit(ctx->expr(0)));
    t->addChild(visit(ctx->expr(1)));
    return t;
}

/* ^(CALL expr expressionList) */
std::any ASTBuilder::visitCall(CymbolParser::CallContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::CALL);
    t->addChild(visit(ctx->expr()));
    if ( ctx->expressionList() ) t->addChild(visit(ctx->expressionList()));
    return t;
}

std::any ASTBuilder::visitParen(CymbolParser::ParenContext *ctx) {
    return visit(ctx->expr());
}

std::any ASTBuilder::visitMemberExpr(CymbolParser::MemberExprContext *ctx) {
    return visit(ctx->member());
}

/* ^(MEMBER ID+) */
std::any ASTBuilder::visitMember(CymbolParser::MemberContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::MEMBER, ctx->start->getLine());

    for (auto *m : ctx->ID()) {
        t->addChild(std::make_shared<AST>(m->getSymbol()));
    }
    return t;
}

/* ID */
std::any ASTBuilder::visitId(CymbolParser::IdContext *ctx) {
    return std::make_shared<AST>(ctx->ID()->getSymbol());
}

/* INT */
std::any ASTBuilder::visitInteger(CymbolParser::IntegerContext *ctx) {
    return std::make_shared<AST>(ctx->INT()->getSymbol());
}

} // namespace aggregate
