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
#include "MethodSymbol.h"
#include "ScopedSymbol.h"

void ResolveSymbols::visit(std::shared_ptr<AST> t) {
    if ( t->isNil() ) {
        visitChildren(t);
    } else {
        switch ( t->getNodeType() ) {
            case classsym::CymbolParser::CLASS_DECL:
                visitCLASS_DECL(t);
                break;
            case classsym::CymbolParser::ASSIGN:
                visitASSIGN(t);
                break;
            case classsym::CymbolParser::ID:
                visitID(t);
                break;
            case classsym::CymbolParser::MEMBER:
                visitMEMBER(t);
                break;
            case classsym::CymbolParser::EXPR:
                visitEXPR(t);
                break;
            default: // The other nodes we don't care about just have their children visited
                visitChildren(t);
        }
    }
}

void ResolveSymbols::visitCLASS_DECL(std::shared_ptr<AST> t) {
    if (t->children[1]->isNil())
        return; // No superClass defined
    
    // The superclass symbol is already defined, but needs to be resolved.
    std::shared_ptr<SymAST> superClass = std::dynamic_pointer_cast<SymAST>(t->children[1]);
    assert(superClass);

    std::shared_ptr<SymAST> id = std::dynamic_pointer_cast<SymAST>(t->children[0]);
    assert(id);
    assert(id->sym);

    std::shared_ptr<Symbol> super = t->scope->resolve(superClass->token->getText());
    if (!super) {
        std::cerr << "line " << id->token->getLine() << " error: super class "
                  << superClass->token->getText() << " of class "
                  << id->sym->getName() << " not found" << std::endl;
        return;
    }
    std::shared_ptr<ClassSymbol> supersym = std::dynamic_pointer_cast<ClassSymbol>(super);
    std::shared_ptr<ClassSymbol> csym = std::dynamic_pointer_cast<ClassSymbol>(id->sym);
    csym->superClass = supersym;
}

/* ^(ASSIGN ID .) */
void ResolveSymbols::visitASSIGN(std::shared_ptr<AST> t) {
    visitChildren(t);

    std::shared_ptr<SymAST> id = std::dynamic_pointer_cast<SymAST>(t->children[0]);
    std::shared_ptr<SymAST> assign = std::dynamic_pointer_cast<SymAST>(t);

    assert(id);
    assert(assign);

    std::cerr << "line " << id->token->getLine() << ": assignment";

    if (id->getNodeType() == classsym::CymbolParser::MEMBER) {
        visitMEMBER(id);
        assign->sym = id->sym;
    }
    else {
        std::shared_ptr<VariableSymbol> vsym = std::dynamic_pointer_cast<VariableSymbol>(t->scope->resolve(id->token->getText()));
        std::cout << vsym->toString() << std::endl;
        assign->sym = vsym;
    }
}

/* ^(EXPR .) */
void ResolveSymbols::visitEXPR(std::shared_ptr<AST> t) {
    visitChildren(t);
}


/* {$start.hasAncestor(EXPR)}? ID */
void ResolveSymbols::visitID(std::shared_ptr<AST> t) {
    std::shared_ptr<SymAST> id = std::dynamic_pointer_cast<SymAST>(t);

    assert(id);
    assert(t->scope);
        
    id->sym = t->scope->resolve(t->token->getText());
    if ( id->sym ) {
        std::cout << "line " << t->token->getLine() << ": ref " << id->sym->toString() << std::endl;
    } else {
        std::cout << "line " << t->token->getLine() << ": ref null\n"; // variable not defined
    }
}

/* member: ID ('.' ID)+ */
void ResolveSymbols::visitMEMBER(std::shared_ptr<AST> t) {
    std::shared_ptr<SymAST> structId = std::dynamic_pointer_cast<SymAST>(t->children[0]);
    assert(structId);
    assert(t->scope);

    // The first ID is the outermost struct variable. Use the lexical scope rules to resolve it.
    std::shared_ptr<Symbol> sym = t->scope->resolve(structId->token->getText());
    structId->sym = sym;
    if (!sym) {
        std::cerr << "line " << structId->token->getLine() << ": error "
                      << structId->token->getText() << " could not be resolved"
                      << std::endl;
        return;
    }
    std::shared_ptr<ClassSymbol> classSym = std::dynamic_pointer_cast<ClassSymbol>(sym->type);
    std::shared_ptr<StructSymbol> structSym = nullptr;
    if (!classSym) {
        structSym = std::dynamic_pointer_cast<StructSymbol>(sym->type);
        if (!structSym) {
            std::cerr << "line " << structId->token->getLine() << ": error "
                      << structId->token->getText() << " is not a struct or class"
                      << std::endl;
            return;
        }
    }
                                                                               
    for (int i=1; i<t->children.size(); i++) {
        std::shared_ptr<SymAST> m = std::dynamic_pointer_cast<SymAST>(t->children[i]);
        assert(m);

        // Use resolveMember to resolve this field within the struct/class
        if (classSym) {
            sym = classSym->resolveMember(m->token->getText());
        }
        else {
            sym = structSym->resolveMember(m->token->getText());
        }
        m->sym = sym;
        if (!sym) {
            std::cerr << "line " << m->token->getLine() << ": error "
                      << m->token->getText() << " is not a member of ";
            std::cerr << (classSym)? classSym->getName() : structSym->getName();
            std::cerr << std::endl;
            return;
        }
        if (i < (t->children.size() - 1)) {
            classSym = std::dynamic_pointer_cast<ClassSymbol>(sym->type);
            if (!classSym) {
                structSym = std::dynamic_pointer_cast<StructSymbol>(sym->type);
                if (!structSym) {
                    std::cerr << "line " << m->token->getLine() << ": Error "
                              << sym->getName() << " is not a struct/class"
                              << std::endl;
                    return;
                }
            }
            else {
                structSym = nullptr;
            }
        }
        else { // this is the last reference
            std::cout << "line " << m->token->getLine() << ":";
            m = std::dynamic_pointer_cast<SymAST>(t);
            m->sym = sym;
            std::cout << " member ref: " << sym->toString() << std::endl;
        }
    }
}
