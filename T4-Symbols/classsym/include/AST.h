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

#pragma once

#include "antlr4-runtime.h"

#include <vector>
#include <string>
#include <memory>

#include "Scope.h"
#include "Type.h"
#include "Symbol.h"

class AST { // Homogeneous AST node type
public:
    std::shared_ptr<antlr4::Token> token;       // From which token did we create node?
    std::vector<std::shared_ptr<AST>> children; // normalized list of children
    std::shared_ptr<Scope> scope;               // containing scope

    AST(); // for making nil-rooted nodes
    AST(antlr4::Token* token);
    /** Create node from token type; used mainly for imaginary tokens */
    AST(size_t tokenType);

    /** External visitors execute the same action for all nodes
     *  with same node type while walking. */
    size_t getNodeType();
    
    void addChild(std::any t);
    void addChild(std::shared_ptr<AST> t);
    bool isNil();

    /** Compute string for single node */
    virtual std::string toString();
    /** Compute string for a whole tree not just a node */
    std::string toStringTree();

    virtual ~AST();
};

class ExprAST : public AST {
public:
    std::shared_ptr<Type> type;  // For type checking

    ExprAST(antlr4::Token* token) : AST(token), type(nullptr) {}
    ExprAST(size_t tokenType) : AST(tokenType), type(nullptr) {}
};

class SymAST : public AST {
public:
    std::shared_ptr<Symbol> sym; // pointer to symbol definition

    SymAST(antlr4::Token* token) : AST(token), sym(nullptr) {}
    SymAST(size_t tokenType) : AST(tokenType), sym(nullptr) {}
};
