#pragma once

#include <memory>

#include "Symbol.h"
#include "Type.h"

class VariableSymbol : public Symbol {
public:
    VariableSymbol(std::string name, std::shared_ptr<Type> type);
};

