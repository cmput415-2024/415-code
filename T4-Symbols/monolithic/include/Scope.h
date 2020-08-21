#pragma once

#include <string>

#include "Symbol.h"

class Scope {
public:
    virtual std::string getScopeName() = 0;

    /** Where to look next for symbols */
    virtual std::shared_ptr<Scope> getEnclosingScope() = 0;

    /** Define a symbol in the current scope */
    virtual void define(std::shared_ptr<Symbol> sym) = 0;

    /** Look up name in this scope or in enclosing scope if not here */
    virtual std::shared_ptr<Symbol> resolve(const std::string &name) = 0;

    virtual ~Scope();
};
