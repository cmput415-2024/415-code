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
#include <sstream>

#include "LocalScope.h"
#include "SymbolTable.h"

SymbolTable::~SymbolTable() {
    scopes.clear();
}

std::shared_ptr<Scope> SymbolTable::enterScope(std::string& name, std::shared_ptr<Scope> enclosingScope) {
    std::shared_ptr<Scope> newScope = std::make_shared<LocalScope>(name, enclosingScope);
    scopes.push_back(newScope);
    return newScope;
}

std::shared_ptr<Scope> SymbolTable::enterScope(std::shared_ptr<Scope> newScope) {
    scopes.push_back(newScope);
    return newScope;
}

std::shared_ptr<Scope> SymbolTable::exitScope(std::shared_ptr<Scope> currentScope) {
    return currentScope->getEnclosingScope();
}

std::string SymbolTable::toString() {
    std::stringstream str;
    str << "Symbol Table {" << std::endl;
    for (auto s : scopes) {
        str << s->getScopeName() << ": " << s->toString() << std::endl;
    }
    str << "}" << std::endl;
    return str.str();
}
