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
#include "Symbol.h"
#include "MethodSymbol.h"
#include "BuiltInTypeSymbol.h"
#include "StructSymbol.h"
#include "VariableSymbol.h"

DefRef::DefRef() {
    std::string globals = "globals";
    currentScope = symtab.enterScope(globals, nullptr);

    currentScope->define(std::make_shared<BuiltInTypeSymbol>("int"));
    currentScope->define(std::make_shared<BuiltInTypeSymbol>("float"));
    currentScope->define(std::make_shared<BuiltInTypeSymbol>("void")); // pseudo-type
}

void DefRef::visit(std::shared_ptr<AST> t) {
    if ( t->isNil() ) {
        visitChildren(t);
    } else {
        switch ( t->getNodeType() ) {
            case aggregate::CymbolParser::BLOCK:
                visitBLOCK(t);
                break;
            case aggregate::CymbolParser::DECL_BLOCK:
                visitDECL_BLOCK(t);
                break;
            case aggregate::CymbolParser::METHOD_DECL:
                visitMETHOD_DECL(t);
                break;
            case aggregate::CymbolParser::STRUCT_DECL:
                visitSTRUCT_DECL(t);
                break;
            case aggregate::CymbolParser::VAR_DECL:
            case aggregate::CymbolParser::ARG_DECL:
                visitDECL(t);
                break;
            case aggregate::CymbolParser::ASSIGN:
                visitASSIGN(t);
                break;
            case aggregate::CymbolParser::ID:
                visitID(t);
                break;
            case aggregate::CymbolParser::MEMBER:
                visitMEMBER(t);
                break;
            case aggregate::CymbolParser::EXPR:
                visitChildren(t);
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
    auto res = currentScope->resolve(t->token->getText());
    std::shared_ptr<Type> tsym = std::dynamic_pointer_cast<Type>(res);

    if (!tsym) {
        std::cerr << "Error: " << t->token->getText() << " is not a type" << std::endl;
        std::cerr << "tsym type " << typeid(res).name() << std::endl;
    }
    return tsym;
}

void DefRef::visitBLOCK(std::shared_ptr<AST> t) {
    std::string sname = "local-" + std::to_string(t->token->getLine());
    currentScope = symtab.enterScope(sname, currentScope);
    visitChildren(t);
    //std::cout << "locals: " << currentScope->toString() << std::endl;
    currentScope = symtab.exitScope(currentScope);
}

void DefRef::visitDECL_BLOCK(std::shared_ptr<AST> t) {    
    visitChildren(t);
}

//  ^(METHOD_DECL type ID .*)
void DefRef::visitMETHOD_DECL(std::shared_ptr<AST> t) {
    std::shared_ptr<AST> ty = t->children[0];
    std::shared_ptr<AST> id = t->children[1];

    std::cout << "line " << id->token->getLine() << ": def method " << id->token->getText() << std::endl;

    std::shared_ptr<Type> retType = resolveType(ty);
    std::shared_ptr<MethodSymbol> ms = std::make_shared<MethodSymbol>(id->token->getText(), retType, currentScope);
    currentScope->define(ms); // def method in globals
    currentScope = symtab.enterScope(ms);

    visitChildren(t);

    currentScope = symtab.exitScope(currentScope);
}

void DefRef::visitSTRUCT_DECL(std::shared_ptr<AST> t) {
    std::shared_ptr<AST> id = t->children[0];

    std::cout << "line " << id->token->getLine() << ": def struct " << id->token->getText() << std::endl;

    std::shared_ptr<StructSymbol> ss = std::make_shared<StructSymbol>(id->token->getText(), currentScope);
    currentScope->define(ss); // def struct in local scope
    currentScope = ss;        // set current scope to struct scope

    visitChildren(t);

    currentScope = currentScope->getEnclosingScope(); // pop method scope

    std::cout << ss->toString() << std::endl;
}

/* ^((ARG_DECL|VAR_DECL) type ID .?) */
void DefRef::visitDECL(std::shared_ptr<AST> t) {
    std::shared_ptr<AST> ty = t->children[0];
    std::shared_ptr<AST> id = t->children[1];

    std::cout << "line " << id->token->getLine() << ": def " << id->token->getText() << std::endl;

    std::shared_ptr<Type> type = resolveType(ty);
            
    std::shared_ptr<VariableSymbol> vs = std::make_shared<VariableSymbol>(id->token->getText(), type);
    currentScope->define(vs);

    visitChildren(t);
}

/* ^(ASSIGN ID .) */
void DefRef::visitASSIGN(std::shared_ptr<AST> t) {
    visitChildren(t);

    std::shared_ptr<AST> id = t->children[0];

    std::cout << "line " << id->token->getLine() << ": assignment to ";
    if (id->getNodeType() == aggregate::CymbolParser::MEMBER) {
        std::cout << "member" << std::endl;
        visit(id);
    }
    else {
        std::shared_ptr<VariableSymbol> vs = std::dynamic_pointer_cast<VariableSymbol>(currentScope->resolve(id->token->getText()));
        std::cout << vs->getName() << std::endl;
    }

    visit(t->children[1]);
}


/* {$start.hasAncestor(EXPR)}? ID */
void DefRef::visitID(std::shared_ptr<AST> t) {
    std::shared_ptr<Symbol> s = currentScope->resolve(t->token->getText());
    if ( s ) {
        std::cout << "line " << t->token->getLine() << ": ref " << s->toString() << std::endl;
    } else {
        std::cout << "line " << t->token->getLine() << ": ref null\n"; // variable not defined
    }
}

/* member: ID ('.' ID)+ */
void DefRef::visitMEMBER(std::shared_ptr<AST> t) {
    std::shared_ptr<AST> structId = t->children[0];

    // The first ID is the outermost struct variable. Use the lexical scope rules to resolve it.
    std::shared_ptr<Symbol> sym = currentScope->resolve(structId->token->getText());
    std::shared_ptr<StructSymbol> structSym = std::dynamic_pointer_cast<StructSymbol>(sym->type);
    if (!structSym) {
        std::cerr << "line " << structId->token->getLine() << ": error "
                  << structId->token->getText() << " is not a struct" << std::endl;
        return;
    }
                                                                               
    std::cout << "visit instance " << sym->getName() << " of type " << structSym->getName() << std::endl;
    
    for (int i=1; i<t->children.size(); i++) {
        std::shared_ptr<AST> m = t->children[i];

        // Use resolveMember to resolve this field within structSym
        sym = structSym->resolveMember(m->token->getText());
        if (!sym) {
            std::cerr << "line " << m->token->getLine() << ": error "
                      << m->token->getText() << " is not a member of " << structSym->getName() << std::endl;
            return;
        }

        std::cout << "resolved child[" << i << "]: " << sym->toString() << std::endl;
        if (i < (t->children.size() - 1)) {
            // The type of this field becomes the enclosing struct of the next field
            structSym = std::dynamic_pointer_cast<StructSymbol>(sym->type);
            if (!structSym) {
                std::cerr << "line " << m->token->getLine() << ": Error "
                          << sym->getName() << " is not a struct" << std::endl;
                return;
            }
        }
    }
}
