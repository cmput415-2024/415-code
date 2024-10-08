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

#include "DefRef.h"

#include <iostream>

#include "CymbolParser.h"
#include "LocalScope.h"
#include "Symbol.h"
#include "MethodSymbol.h"
#include "VariableSymbol.h"

DefRef::DefRef() : currentScope(symtab.globals), numExprAncestors(0) { }

void DefRef::visit(std::shared_ptr<AST> t) {
    if ( t->isNil() ) {
        visitChildren(t);
    } else {
        switch ( t->getNodeType() ) {
            case nested::CymbolParser::BLOCK:
                visitBLOCK(t);
                break;
            case nested::CymbolParser::METHOD_DECL:
                visitMETHOD_DECL(t);
                break;
            case nested::CymbolParser::VAR_DECL:
            case nested::CymbolParser::ARG_DECL:
                visitDECL(t);
                break;
            case nested::CymbolParser::ASSIGN:
                visitASSIGN(t);
                break;
            case nested::CymbolParser::ID:
                visitID(t);
                break;
            case nested::CymbolParser::EXPR:
                // Keep track of number of expression ancestors for id references
                numExprAncestors++;
                visitChildren(t);
                numExprAncestors--;
                break;
            default: // The other nodes we don't care about just have their children visited
                visitChildren(t);
        }
    }
}

void DefRef::visitChildren(std::shared_ptr<AST> t) {
    for ( auto child : t->children ) visit(child);
}

std::shared_ptr<Type> DefRef::resolveType(std::shared_ptr<AST> t) {
    std::shared_ptr<Type> tsym;
    tsym = std::dynamic_pointer_cast<Type>(currentScope->resolve(t->token->getText()));
    return tsym;
}

void DefRef::visitBLOCK(std::shared_ptr<AST> t) {
    currentScope = std::make_shared<LocalScope>(currentScope); // push scope
    visitChildren(t);
    std::cout << "locals: " << currentScope->toString() << "\n";
    currentScope = currentScope->getEnclosingScope(); // pop scope
}

//  ^(METHOD_DECL type ID .*)
void DefRef::visitMETHOD_DECL(std::shared_ptr<AST> t) {
    std::shared_ptr<AST> ty = t->children[0];
    std::shared_ptr<AST> id = t->children[1];

    std::cout << "line " << id->token->getLine() << ": def method " << id->token->getText() << "\n";

    std::shared_ptr<Type> retType = resolveType(ty);
    std::shared_ptr<MethodSymbol> ms = std::make_shared<MethodSymbol>(id->token->getText(), retType, currentScope);
    currentScope->define(ms); // def method in globals
    currentScope = ms;        // set current scope to method scope

    visitChildren(t);

    currentScope = currentScope->getEnclosingScope(); // pop method scope
}

/* ^((ARG_DECL|VAR_DECL) type ID .?) */
void DefRef::visitDECL(std::shared_ptr<AST> t) {
    std::shared_ptr<AST> ty = t->children[0];
    std::shared_ptr<AST> id = t->children[1];

    std::cout << "line " << id->token->getLine() << ": def " << id->token->getText() << "\n";

    std::shared_ptr<Type> type = resolveType(ty);
    std::shared_ptr<VariableSymbol> vs = std::make_shared<VariableSymbol>(id->token->getText(), type);
    currentScope->define(vs);

    visitChildren(t);
}

/* ^(ASSIGN ID .) */
void DefRef::visitASSIGN(std::shared_ptr<AST> t) {
    visitChildren(t);

    std::shared_ptr<AST> id = t->children[0];
    std::shared_ptr<VariableSymbol> vs = std::dynamic_pointer_cast<VariableSymbol>(currentScope->resolve(id->token->getText()));
    std::cout << "line " << id->token->getLine() << ": assign to " << vs->toString() << "\n";
}

/* {$start.hasAncestor(EXPR)}? ID */
void DefRef::visitID(std::shared_ptr<AST> t) {
    if ( numExprAncestors > 0 ) { // If an ID occurs within an expression, we have an ID reference
        std::shared_ptr<Symbol> s = currentScope->resolve(t->token->getText());
        if ( s ) {
            std::cout << "line " << t->token->getLine() << ": ref " << s->toString() << "\n";
        } else {
            std::cout << "line " << t->token->getLine() << ": ref null\n"; // variable not defined
        }
    }
}
