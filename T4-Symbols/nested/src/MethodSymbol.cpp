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

#include "MethodSymbol.h"

#include <sstream>

MethodSymbol::MethodSymbol( std::string name, std::shared_ptr<Type> retType,
                            std::shared_ptr<Scope> enclosingScope) 
                        : Symbol(name, retType), enclosingScope(enclosingScope) {}

std::shared_ptr<Symbol> MethodSymbol::resolve(const std::string &name) {
    for ( auto sym : orderedArgs ) {
        if ( sym->getName() == name ) {
            return sym;
        }
    }
    // if not here, check any enclosing scope
    if ( getEnclosingScope() != nullptr ) {
        return getEnclosingScope()->resolve(name);
    }
    return nullptr; // not found
}

void MethodSymbol::define(std::shared_ptr<Symbol> sym) {
    orderedArgs.push_back(sym);
    sym->scope = shared_from_this();
}

std::shared_ptr<Scope> MethodSymbol::getEnclosingScope() { return enclosingScope; }

std::string MethodSymbol::getScopeName() { return name; }

std::string MethodSymbol::toString() {
    std::stringstream str;
    str << "method" << Symbol::toString() << ":{";
    for (auto iter = orderedArgs.begin(); iter != orderedArgs.end(); iter++) {
        std::shared_ptr<Symbol> sym = *iter;
        if ( iter != orderedArgs.begin() ) str << ", ";
        str << sym->toString();
    }
    str << "}";
    return str.str();
}