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

#include "BaseScope.h"

#include <sstream>
#include <string>

BaseScope::BaseScope(std::shared_ptr<Scope> enclosingScope) : enclosingScope(enclosingScope) {}

std::shared_ptr<Symbol> BaseScope::resolve(const std::string &name) {
    auto find_s = symbols.find(name);
    if ( find_s != symbols.end() ) return find_s->second;
    // if not here, check any enclosing scope
    if ( enclosingScope != nullptr ) return enclosingScope->resolve(name);
    return nullptr; // not found
}

void BaseScope::define(std::shared_ptr<Symbol> sym) {
    symbols.emplace(sym->name, sym);
    sym->scope = shared_from_this(); // track the scope in each symbol
}

std::shared_ptr<Scope> BaseScope::getEnclosingScope() {
    return enclosingScope;
}

std::string BaseScope::toString() {
    std::stringstream str;
    str << "{";
    for (auto iter = symbols.begin(); iter != symbols.end(); iter++) {
        std::shared_ptr<Symbol> sym = iter->second;
        if ( iter != symbols.begin() ) str << ", ";
        str << sym->toString();
    }
    str << "}";
    return str.str();
}
