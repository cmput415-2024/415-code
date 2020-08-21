#pragma once

#include "AST.h"
#include "SymbolTable.h"

class DefRef {
private:
    SymbolTable symtab;
    std::shared_ptr<Scope> currentScope;
    std::shared_ptr<Type> resolveType(std::shared_ptr<AST> t);
    size_t numExprAncestors;
public:
    DefRef();
    void visit(std::shared_ptr<AST> t);
    void visitChildren(std::shared_ptr<AST> t);
    void visitBLOCK(std::shared_ptr<AST> t);
    void visitMETHOD_DECL(std::shared_ptr<AST> t);
    void visitDECL(std::shared_ptr<AST> t);
    void visitASSIGN(std::shared_ptr<AST> t);
    void visitID(std::shared_ptr<AST> t);
};