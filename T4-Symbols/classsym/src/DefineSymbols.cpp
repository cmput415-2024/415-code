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

#include "ASTWalker.h"

#include <assert.h>
#include <iostream>

#include "CymbolParser.h"
#include "BaseScope.h"
#include "Symbol.h"
#include "MethodSymbol.h"
#include "ScopedSymbol.h"

void DefineSymbols::visit(std::shared_ptr<AST> t) {
    if ( t->isNil() ) {
        visitChildren(t);
    } else {
        switch ( t->getNodeType() ) {
            case classsym::CymbolParser::BLOCK:
                visitBLOCK(t);
                break;
            case classsym::CymbolParser::DECL_BLOCK:
                visitDECL_BLOCK(t);
                break;
            case classsym::CymbolParser::METHOD_DECL:
                visitMETHOD_DECL(t);
                break;
            case classsym::CymbolParser::STRUCT_DECL:
                visitSTRUCT_DECL(t);
                break;
            case classsym::CymbolParser::CLASS_DECL:
                visitCLASS_DECL(t);
                break;
            case classsym::CymbolParser::VAR_DECL:
            case classsym::CymbolParser::ARG_DECL:
                visitDECL(t);
                break;
            default: // The other nodes we don't care about just have their children visited
                visitChildren(t);
        }
    }
}

void DefineSymbols::visitChildren(std::shared_ptr<AST> t) {
    for ( auto child : t->children ) {
        if (!child->scope) child->scope = symtab->currentScope;
        visit(child);
    }
}

std::shared_ptr<Type> DefineSymbols::resolveType(std::shared_ptr<AST> t) {
    if (!t->scope) t->scope = symtab->currentScope;

    auto res = t->scope->resolve(t->token->getText());
    std::shared_ptr<Type> tsym = std::dynamic_pointer_cast<Type>(res);

    if (!tsym) {
        std::cerr << "Error: " << t->token->getText() << " is not a type" << std::endl;
        std::cerr << "tsym type " << typeid(res).name() << std::endl;
    }
    return tsym;
}

void DefineSymbols::visitBLOCK(std::shared_ptr<AST> t) {
    symtab->push_scope(std::make_shared<LocalScope>());
    visitChildren(t);
    symtab->pop_scope();
}

void DefineSymbols::visitDECL_BLOCK(std::shared_ptr<AST> t) {    
    visitChildren(t);
}

//  ^(METHOD_DECL type ID .*)
void DefineSymbols::visitMETHOD_DECL(std::shared_ptr<AST> t) {
    std::shared_ptr<AST> ty = t->children[0];
    std::shared_ptr<SymAST> id = std::dynamic_pointer_cast<SymAST>(t->children[1]);
    assert(id);

    std::shared_ptr<Type> retType = resolveType(ty);
    std::shared_ptr<MethodSymbol> ms = std::make_shared<MethodSymbol>(id->token->getText(), retType, symtab->currentScope);
    symtab->currentScope->define(ms);
    id->sym = ms;

    symtab->push_scope(ms);

    visitChildren(t);

    symtab->pop_scope();
}

void DefineSymbols::visitSTRUCT_DECL(std::shared_ptr<AST> t) {
    std::shared_ptr<SymAST> id = std::dynamic_pointer_cast<SymAST>(t->children[0]);
    assert(id);
    id->scope = symtab->currentScope;

    assert(symtab->currentScope);
    
    std::shared_ptr<StructSymbol> ss = std::make_shared<StructSymbol>(id->token->getText(), symtab->currentScope);
    symtab->currentScope->define(ss); // def struct in local scope
    id->sym = ss;

    symtab->push_scope(ss);

    visitChildren(t->children[1]);

    symtab->pop_scope();
}

void DefineSymbols::visitCLASS_DECL(std::shared_ptr<AST> t) {
    std::shared_ptr<SymAST> id = std::dynamic_pointer_cast<SymAST>(t->children[0]);
    assert(id);

    std::shared_ptr<ClassSymbol> csym = std::make_shared<ClassSymbol>(id->token->getText(), symtab->currentScope);
    symtab->currentScope->define(csym); // def struct in local scope
    id->scope = symtab->currentScope;
    id->sym = csym;

    symtab->push_scope(csym);    
    visitChildren(t);
    symtab->pop_scope();
}

/* ^((ARG_DECL|VAR_DECL) type ID .?) */
void DefineSymbols::visitDECL(std::shared_ptr<AST> t) {
    std::shared_ptr<AST> ty = t->children[0];
    std::shared_ptr<SymAST> id = std::dynamic_pointer_cast<SymAST>(t->children[1]);
    assert(id);

    std::shared_ptr<Type> type = resolveType(ty);

    std::shared_ptr<VariableSymbol> vs = std::make_shared<VariableSymbol>(id->token->getText(), type);
    symtab->currentScope->define(vs);
    id->sym = vs;
        
    visitChildren(t);
}
