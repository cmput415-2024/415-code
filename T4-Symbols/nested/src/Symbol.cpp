#include "Symbol.h"

Symbol::Symbol(std::string name) : Symbol(name, nullptr) {}
Symbol::Symbol(std::string name, std::shared_ptr<Type> type) : name(name), type(type) {}

std::string Symbol::getName() { return name; }

std::string Symbol::toString() {
    if (type != nullptr) return '<' + getName() + ":" + type->getName() + '>';
    return getName();
}

Symbol::~Symbol() {}
