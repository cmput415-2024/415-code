#include "ASTWalker.h"

void ASTWalker::visit(std::shared_ptr<AST> t) {
    visitChildren(t);
}

void ASTWalker::visitChildren(std::shared_ptr<AST> t) {
    for ( auto child : t->children ) visit(child);
}

