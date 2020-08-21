#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Symbol.h"
#include "Type.h"

class MethodSymbol : public Symbol, public Scope {
private:
    std::vector<std::shared_ptr<Symbol>> orderedArgs;
    std::shared_ptr<Scope> enclosingScope;
public:
    MethodSymbol(std::string name, std::shared_ptr<Type> retType, std::shared_ptr<Scope> enclosingScope);
    std::shared_ptr<Symbol> resolve(const std::string &name);
    void define(std::shared_ptr<Symbol> sym);
    std::shared_ptr<Scope> getEnclosingScope();
    std::string getScopeName();
    std::string toString();
};


