#pragma once

#include <map>
#include <string>
#include <memory>

#include "Scope.h"

class SymbolTable : public Scope { // single-scope symtab
protected:
    void initTypeSystem();
public:	
    std::map<std::string, std::shared_ptr<Symbol>> symbols;
    SymbolTable();

    // Satisfy Scope interface
    std::string getScopeName();
    std::shared_ptr<Scope> getEnclosingScope();
    void define(std::shared_ptr<Symbol> sym);
    std::shared_ptr<Symbol> resolve(const std::string &name);
    std::string toString();
};
