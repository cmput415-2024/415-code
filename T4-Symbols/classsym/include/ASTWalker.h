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

#include "AST.h"
#include "SymbolTable.h"

class ASTWalker {
public:
    ASTWalker() {}

    virtual void visit(std::shared_ptr<AST> t);
    virtual void visitChildren(std::shared_ptr<AST> t);
};

class DefineSymbols : public ASTWalker {
private:
    SymbolTable *symtab;

    std::shared_ptr<Type> resolveType(std::shared_ptr<AST> t);
public:
    DefineSymbols(SymbolTable *symtab) : symtab(symtab) {}

    virtual void visit(std::shared_ptr<AST> t);
    virtual void visitChildren(std::shared_ptr<AST> t);

    void visitBLOCK(std::shared_ptr<AST> t);
    void visitDECL_BLOCK(std::shared_ptr<AST> t);
    void visitMETHOD_DECL(std::shared_ptr<AST> t);
    void visitSTRUCT_DECL(std::shared_ptr<AST> t);
    void visitCLASS_DECL(std::shared_ptr<AST> t);
    void visitDECL(std::shared_ptr<AST> t);
    void visitID(std::shared_ptr<AST> t);
};

class ResolveSymbols : public ASTWalker {
public:
    ResolveSymbols() {}

    virtual void visit(std::shared_ptr<AST> t);

    void visitCLASS_DECL(std::shared_ptr<AST> t);
    void visitASSIGN(std::shared_ptr<AST> t);
    void visitEXPR(std::shared_ptr<AST> t);
    void visitID(std::shared_ptr<AST> t);
    void visitMEMBER(std::shared_ptr<AST> t);
};
