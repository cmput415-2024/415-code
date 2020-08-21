#include "BuiltInTypeSymbol.h"

BuiltInTypeSymbol::BuiltInTypeSymbol(std::string name) : Symbol(name) {}

std::string BuiltInTypeSymbol::getName() {
    return Symbol::getName();
}
