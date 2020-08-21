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
