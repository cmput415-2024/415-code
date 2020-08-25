/***
 * Excerpt from "The Definitive ANTLR 4 Reference",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/tpantlr2 for more book information.
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

#include "ExtractInterfaceListener.h"

namespace trans {

ExtractInterfaceListener::ExtractInterfaceListener(JavaParser *parser) : parser(parser) {}

void ExtractInterfaceListener::enterClassDeclaration(JavaParser::ClassDeclarationContext *ctx) {
    std::cout << "interface I" << ctx->Identifier()->getText() << " {\n";
}

void ExtractInterfaceListener::exitClassDeclaration(JavaParser::ClassDeclarationContext *ctx) {
    std::cout << "}\n";
}

void ExtractInterfaceListener::enterMethodDeclaration(JavaParser::MethodDeclarationContext *ctx) {
    // need parser to get tokens
    antlr4::TokenStream *tokens = parser->getTokenStream();
    std::string type = "void";
    if (ctx->type() != nullptr) {
        type = tokens->getText(ctx->type());
    }
    std::string args = tokens->getText(ctx->formalParameters());
    std::cout << "\t" << type << " " << ctx->Identifier()->getText() << args << ";\n";
}

}