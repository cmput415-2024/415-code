#pragma once

#include "CymbolBaseVisitor.h"

#include "SymbolTable.h"

namespace mono {

class MyVisitor : public CymbolBaseVisitor {
public:
    SymbolTable symtab;
    MyVisitor();
    virtual antlrcpp::Any visitType(CymbolParser::TypeContext *ctx) override;
    virtual antlrcpp::Any visitVarDeclaration(CymbolParser::VarDeclarationContext *ctx) override;
    virtual antlrcpp::Any visitPrimaryID(CymbolParser::PrimaryIDContext *ctx) override;
};

}
