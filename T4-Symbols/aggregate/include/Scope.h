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

#include <string>
#include <memory>

#include "Symbol.h"

class Symbol; // forward declaration of Symbol to resolve circular dependency

class Scope : public std::enable_shared_from_this<Scope> {
public:
    virtual std::string getScopeName() = 0;

    /** Where to look next for symbols */
    virtual std::shared_ptr<Scope> getEnclosingScope() = 0;

    /** Define a symbol in the current scope */
    virtual void define(std::shared_ptr<Symbol> sym) = 0;

    /** Look up name in this scope or in enclosing scope if not here */
    virtual std::shared_ptr<Symbol> resolve(const std::string &name) = 0;

	virtual std::string toString() = 0;
    virtual ~Scope() {};
};
