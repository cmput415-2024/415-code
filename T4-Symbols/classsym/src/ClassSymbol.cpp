#include "ScopedSymbol.h"

#include <sstream>
#include <iostream>

std::shared_ptr<Symbol> ClassSymbol::resolveMember(const std::string &name) {
    std::cerr << "class " << getName() << " resolveMember: " << name << std::endl;
    if (fields.count(name) == 1) {
        return fields.at(name);
    }

    if (superClass) {
        std::cerr << "trying superclass " << superClass->getName() << std::endl;
        return superClass->resolveMember(name);
    }
    return nullptr;
}

std::string ClassSymbol::toString() {
    std::stringstream str;
    str << "class " << Symbol::toString() << " {" << std::endl;
    for (auto const& f : fields) {
        std::shared_ptr<Symbol> sym = f.second;
        str << "\t" << sym->toString() << std::endl;
    }
    str << "}";
    return str.str();
}

