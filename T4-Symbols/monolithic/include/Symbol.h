#pragma once

#include <string>
#include <memory>

#include "Type.h"

class Symbol { // A generic programming language symbol
public:
    std::string name;      // All symbols at least have a name
    std::shared_ptr<Type> type;
    Symbol(std::string name);
    Symbol(std::string name, std::shared_ptr<Type> type);
    virtual std::string getName();
    virtual std::string toString();
    virtual ~Symbol();
};
