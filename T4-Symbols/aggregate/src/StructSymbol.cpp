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

#include "StructSymbol.h"

#include <sstream>

StructSymbol::StructSymbol( std::string name, std::shared_ptr<Scope> enclosingScope) 
    : ScopedSymbol(name, enclosingScope) {}

std::shared_ptr<Symbol> StructSymbol::resolve(const std::string &name) {
    if (fields.count(name) == 1) {
        return fields.at(name);
    }

    // if not here, check any enclosing scope
    if ( getEnclosingScope() != nullptr ) {
        return getEnclosingScope()->resolve(name);
    }

    return nullptr; // not found
}

std::shared_ptr<Symbol> StructSymbol::resolveMember(const std::string &name) {
    if (fields.count(name) == 1) {
        return fields.at(name);
    }
    // No enclosing scope for a struct
    return nullptr;
}

void StructSymbol::define(std::shared_ptr<Symbol> sym) {
    fields.emplace(sym->name, sym);
    sym->scope = shared_from_this();
}

std::string StructSymbol::getScopeName() {
    return name;
}

std::string StructSymbol::getName() {
    return name;
}

std::string StructSymbol::toString() {
    std::stringstream str;
    str << "struct " << Symbol::toString() << " {" << std::endl;
    for (auto const& f : fields) {
        std::shared_ptr<Symbol> sym = f.second;
        str << "\t" << sym->toString() << std::endl;
    }
    str << "}";
    return str.str();
}
