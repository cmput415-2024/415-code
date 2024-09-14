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

#include "AST.h"

#include <sstream>

AST::AST() {}
AST::AST(antlr4::Token* token) : token(std::make_shared<antlr4::CommonToken>(token)) {}
AST::AST(size_t tokenType, size_t line) {
    std::shared_ptr<antlr4::CommonToken> t = std::make_shared<antlr4::CommonToken>(tokenType);
    t->setLine(line);
    token = t;
}

size_t AST::getNodeType() { return token->getType(); }

void AST::addChild(std::any t) {
    this->addChild(std::any_cast<std::shared_ptr<AST>>(t)); // There is only one valid type for t. Pass it to AST::addChild(std::shared_ptr<AST> t)
}
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
