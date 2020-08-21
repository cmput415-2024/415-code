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

antlrcpp::Any ASTBuilder::visitFormalParameter(CymbolParser::FormalParameterContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::ARG_DECL);
    t->addChild(visit(ctx->type()));
    t->addChild(std::make_shared<AST>(ctx->ID()->getSymbol()));
    return t;
}

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

antlrcpp::Any ASTBuilder::visitBlock(CymbolParser::BlockContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::BLOCK);
    for (auto *stat : ctx->statement()) {
        t->addChild(visit(stat));
    }
    return t;
}

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

antlrcpp::Any ASTBuilder::visitReturn(CymbolParser::ReturnContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::RETURN);
    if ( ctx->expression() ) t->addChild(visit(ctx->expression()));
    return t;
}

antlrcpp::Any ASTBuilder::visitAssignment(CymbolParser::AssignmentContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::ASSIGN);
    t->addChild(std::make_shared<AST>(ctx->ID()->getSymbol()));
    t->addChild(visit(ctx->expression()));
    return t;
}

antlrcpp::Any ASTBuilder::visitExpressionStat(CymbolParser::ExpressionStatContext *ctx) {
    return visit(ctx->expression());
}

antlrcpp::Any ASTBuilder::visitExpressionList(CymbolParser::ExpressionListContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::ELIST);
    for ( auto *expr : ctx->expression() ) {
        t->addChild(visit(expr));
    }
    return t;
}

antlrcpp::Any ASTBuilder::visitExpression(CymbolParser::ExpressionContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::EXPR);
    t->addChild(visit(ctx->expr()));
    return t;
}

antlrcpp::Any ASTBuilder::visitAdd(CymbolParser::AddContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::ADD);
    for ( auto *expr : ctx->expr() ) {
        t->addChild(visit(expr));
    }
    return t;
}

antlrcpp::Any ASTBuilder::visitCall(CymbolParser::CallContext *ctx) {
    std::shared_ptr<AST> t = std::make_shared<AST>(CymbolParser::CALL);
    t->addChild(visit(ctx->expr()));
    if ( ctx->expressionList() ) t->addChild(visit(ctx->expressionList()));
    return t;
}

antlrcpp::Any ASTBuilder::visitParen(CymbolParser::ParenContext *ctx) {
    return visit(ctx->expr());
}

antlrcpp::Any ASTBuilder::visitId(CymbolParser::IdContext *ctx) {
    return std::make_shared<AST>(ctx->ID()->getSymbol());
}

antlrcpp::Any ASTBuilder::visitInteger(CymbolParser::IntegerContext *ctx) {
    return std::make_shared<AST>(ctx->INT()->getSymbol());
}

} // namespace nested