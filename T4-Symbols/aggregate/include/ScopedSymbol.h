#pragma once

#include "Symbol.h"
#include "Scope.h"

class ScopedSymbol : public Symbol, public Scope {
 public:
	std::shared_ptr<Scope> enclosingScope; // nullptr if global (outermost) scope
    ScopedSymbol(std::string name, std::shared_ptr<Scope> enClosingScope);
    ScopedSymbol(std::string name, std::shared_ptr<Type> type,
                 std::shared_ptr<Scope> enClosingScope);

    /** Look up name in this scope or in enclosing scope if not here */
    virtual std::shared_ptr<Symbol> resolve(const std::string &name) = 0;

    virtual std::shared_ptr<Scope> getEnclosingScope();

    virtual ~ScopedSymbol();
};
