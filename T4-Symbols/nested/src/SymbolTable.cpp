#include "SymbolTable.h"

#include "BuiltInTypeSymbol.h"

void SymbolTable::initTypeSystem() {
    globals->define(std::make_shared<BuiltInTypeSymbol>("int"));
    globals->define(std::make_shared<BuiltInTypeSymbol>("float"));
    globals->define(std::make_shared<BuiltInTypeSymbol>("void")); // pseudo-type
}

SymbolTable::SymbolTable() : globals(std::make_shared<GlobalScope>()) { 
    initTypeSystem(); 
}

std::string SymbolTable::toString() {
    return globals->toString();
}
