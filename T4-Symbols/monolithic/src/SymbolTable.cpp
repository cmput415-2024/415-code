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

#include "SymbolTable.h"

#include <string>
#include <sstream>

#include "BuiltInTypeSymbol.h"

void SymbolTable::initTypeSystem() {
    define(std::make_shared<BuiltInTypeSymbol>("int"));
    define(std::make_shared<BuiltInTypeSymbol>("float"));
}

SymbolTable::SymbolTable() { 
    initTypeSystem(); 
}

// Satisfy Scope interface
std::string SymbolTable::getScopeName() {
    return "global";
}

std::shared_ptr<Scope> SymbolTable::getEnclosingScope() {
    return nullptr;
}

void SymbolTable::define(std::shared_ptr<Symbol> sym) {
    symbols.emplace(sym->name, sym);
}

std::shared_ptr<Symbol> SymbolTable::resolve(const std::string &name) {
    return symbols.at(name);
}

std::string SymbolTable::toString() {
    std::stringstream str;
    str << getScopeName() << ":{";
    for (auto iter = symbols.begin(); iter != symbols.end(); iter++) {
        if ( iter != symbols.begin() ) str << ", ";
        str << iter->first;
    }
    str << "}\n";
    return str.str();
}
