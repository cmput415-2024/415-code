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

#pragma once

#include <map>
#include <string>

#include "Scope.h"

class BaseScope : public Scope {
public:
	std::shared_ptr<Scope> enclosingScope; // nullptr if global (outermost) scope
	std::map<std::string, std::shared_ptr<Symbol>> symbols;

    BaseScope() : enclosingScope(nullptr) {}

    std::shared_ptr<Symbol> resolve(const std::string &name) override;
	virtual void define(std::shared_ptr<Symbol> sym) override;
    virtual std::shared_ptr<Scope> getEnclosingScope() override;
    virtual void setEnclosingScope(std::shared_ptr<Scope> scope) override;

	virtual std::string toString() override;
};

class GlobalScope : public BaseScope {
public:
    GlobalScope() {}
    std::string getScopeName() override { return "global"; }
};

class LocalScope : public BaseScope {
public:
    LocalScope() {}
    std::string getScopeName() override { return "local"; }
};
