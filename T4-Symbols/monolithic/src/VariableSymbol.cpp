#include "VariableSymbol.h"

#include <memory>

#include "Symbol.h"
#include "Type.h"

VariableSymbol::VariableSymbol(std::string name, std::shared_ptr<Type> type) : Symbol(name, type) {}
