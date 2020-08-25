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

// The DefRef class is a visitor that translates the functionality
// of the tree grammar `DefRef.g` from the slides/textbook to ANTLR4
// and C++.

#include "DefRef.h"

#include "VariableSymbol.h"
#include "Type.h"

namespace mono {

DefRef::DefRef() : symtab() {}

antlrcpp::Any DefRef::visitType(CymbolParser::TypeContext *ctx) {
    std::shared_ptr<Type> tsym;
    tsym = std::dynamic_pointer_cast<Type>(symtab.resolve(ctx->getText()));
    // std::dynamic_pointer_cast<Type>(arg) casts arg to a std::shared_ptr<Type>
    // with error checks (i.e. will return nullptr if it is not a Type)
    return tsym;
}

antlrcpp::Any DefRef::visitVarDeclaration(CymbolParser::VarDeclarationContext *ctx) {
    size_t line = ctx->getStart()->getLine();
    std::string idstr = ctx->ID()->getText();
    std::shared_ptr<Type> type = visit(ctx->type());

    std::cout << "line " << line << ": def " << idstr << '\n';
    std::shared_ptr<VariableSymbol> vs = std::make_shared<VariableSymbol>(idstr, type);
    // `std::make_shared<VariableSymbol(idstr, type);` is analagous to `new VariableSymbol(idstr, type);`
    // but returns a shared_ptr instead of a raw pointer (VariableSymbol*).
    symtab.define(vs);

    if (ctx->expression()) visit(ctx->expression());

    return 0; // we must return some value
}

antlrcpp::Any DefRef::visitPrimaryID(CymbolParser::PrimaryIDContext *ctx) {
    size_t line = ctx->getStart()->getLine();
    std::string idstr = ctx->ID()->getText();

    std::shared_ptr<Symbol> sym = symtab.resolve(idstr);
    std::cout << "line " << line << ": ref to " << sym->toString() << '\n';

    return 0; // must return some value
}

}
