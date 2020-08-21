#pragma once

#include <map>
#include <string>
#include <memory>

#include "Scope.h"
#include "Symbol.h"
#include "GlobalScope.h"

class SymbolTable { // single-scope symtab
protected:
    void initTypeSystem();
public:	
    std::shared_ptr<GlobalScope> globals;
    SymbolTable();

    std::string toString();
};
