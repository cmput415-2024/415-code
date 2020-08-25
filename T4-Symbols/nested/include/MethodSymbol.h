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
#include <vector>

#include "Symbol.h"
#include "Type.h"

class MethodSymbol : public Symbol, public Scope {
private:
    std::vector<std::shared_ptr<Symbol>> orderedArgs; // Note: The original Java implementation used a data structure 
                                                      // called a LinkedHashMap which as no direct equivalent in C++
                                                      // Essentially it is a Hash Map implementation that retains the original
                                                      // insertion ordering of its elements.
                                                      // For simplicity, this C++ implementation uses a vector and performs
                                                      // a linear scan to resolve symbols. However, for larger projects this
                                                      // simple alternative may not be ideal for performance.
    std::shared_ptr<Scope> enclosingScope;
public:
    MethodSymbol(std::string name, std::shared_ptr<Type> retType, std::shared_ptr<Scope> enclosingScope);
    std::shared_ptr<Symbol> resolve(const std::string &name);
    void define(std::shared_ptr<Symbol> sym);
    std::shared_ptr<Scope> getEnclosingScope();
    std::string getScopeName();
    std::string toString();
};


