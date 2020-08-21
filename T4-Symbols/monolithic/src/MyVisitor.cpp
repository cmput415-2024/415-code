#include "MyVisitor.h"

#include "VariableSymbol.h"
#include "Type.h"

namespace mono {

MyVisitor::MyVisitor() : symtab() {}

antlrcpp::Any MyVisitor::visitType(CymbolParser::TypeContext *ctx) {
    std::shared_ptr<Type> tsym;
    tsym = std::dynamic_pointer_cast<Type>(symtab.resolve(ctx->getText()));
    return tsym;
}

antlrcpp::Any MyVisitor::visitVarDeclaration(CymbolParser::VarDeclarationContext *ctx) {
    size_t line = ctx->getStart()->getLine();
    std::string idstr = ctx->ID()->getText();
    std::shared_ptr<Type> type = visit(ctx->type());

    std::cout << "line " << line << ": def " << idstr << '\n';
    std::shared_ptr<VariableSymbol> vs = std::make_shared<VariableSymbol>(idstr, type);
    symtab.define(vs);

    if (ctx->expression()) visit(ctx->expression());

    return 0; // we must return some value
}

antlrcpp::Any MyVisitor::visitPrimaryID(CymbolParser::PrimaryIDContext *ctx) {
    size_t line = ctx->getStart()->getLine();
    std::string idstr = ctx->ID()->getText();

    std::shared_ptr<Symbol> sym = symtab.resolve(idstr);
    std::cout << "line " << line << ": ref to " << sym->toString() << '\n';

    return 0; // must return some value
}

}
