#pragma once

#include "JavaBaseListener.h"

#include "antlr4-runtime.h"

#include <string>

namespace trans {

class ExtractInterfaceListener : public JavaBaseListener {
public:
    JavaParser *parser;
    ExtractInterfaceListener(JavaParser *parser);
    /** Listen to matches of classDeclaration */
    void enterClassDeclaration(JavaParser::ClassDeclarationContext *ctx) override;
    void exitClassDeclaration(JavaParser::ClassDeclarationContext *ctx) override;
    /** Listen to matches of methodDeclaration */
    void enterMethodDeclaration(JavaParser::MethodDeclarationContext *ctx) override;
};

}