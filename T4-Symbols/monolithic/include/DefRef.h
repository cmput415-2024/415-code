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

// The DefRef class is a visitor that translates the functionality
// of the tree grammar `DefRef.g` from the slides/textbook to ANTLR4
// and C++.

#pragma once

#include "CymbolBaseVisitor.h"

#include "SymbolTable.h"

namespace mono {

class DefRef : public CymbolBaseVisitor {
public:
    SymbolTable symtab;
    DefRef();
    virtual antlrcpp::Any visitType(CymbolParser::TypeContext *ctx) override;
    virtual antlrcpp::Any visitVarDeclaration(CymbolParser::VarDeclarationContext *ctx) override;
    virtual antlrcpp::Any visitPrimaryID(CymbolParser::PrimaryIDContext *ctx) override;
};

}
