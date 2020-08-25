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

#include "Type.h"
#include "Scope.h"

class Scope; // forward declaration of Scope to resolve circular dependency

class Symbol { // A generic programming language symbol
public:
    std::string name;               // All symbols at least have a name
    std::shared_ptr<Type> type;
    std::shared_ptr<Scope> scope;   // All symbols know what scope contains them.

    Symbol(std::string name);
    Symbol(std::string name, std::shared_ptr<Type> type);
    virtual std::string getName();

    virtual std::string toString();
    virtual ~Symbol();
};
