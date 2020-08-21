#include "AST.h"

#include <sstream>

AST::AST() {}
AST::AST(antlr4::Token* token) : token(std::make_shared<antlr4::CommonToken>(token)) {}
AST::AST(size_t tokenType) { token = std::make_shared<antlr4::CommonToken>(tokenType); }

size_t AST::getNodeType() { return token->getType(); }

void AST::addChild(std::shared_ptr<AST> t) {
    children.push_back(t);
}
bool AST::isNil() { return token == nullptr; }

std::string AST::toString() { return token != nullptr ? token->toString() : "nil"; }

std::string AST::toStringTree() {
    if ( children.empty() ) return toString();
    std::stringstream buf;
    if ( !isNil() ) {
        buf << '(' << toString() << ' ';
    }
    for (auto iter = children.begin(); iter != children.end(); iter++) {
        std::shared_ptr<AST> t = *iter; // normalized (unnamed) children
        if ( iter != children.begin() ) buf << ' ';
        buf << t->toStringTree();
    }
    if ( !isNil() ) buf << ')';
    return buf.str();
}

AST::~AST() {}