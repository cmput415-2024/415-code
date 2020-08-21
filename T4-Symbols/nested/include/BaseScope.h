#pragma once

#include <map>
#include <string>

#include "Scope.h"

class BaseScope : public Scope {
public:
	std::shared_ptr<Scope> enclosingScope; // nullptr if global (outermost) scope
	std::map<std::string, std::shared_ptr<Symbol>> symbols;

    BaseScope(std::shared_ptr<Scope> enclosingScope);
    std::shared_ptr<Symbol> resolve(const std::string &name);
	void define(std::shared_ptr<Symbol> sym);
    std::shared_ptr<Scope> getEnclosingScope();

	virtual std::string toString() override;
};
