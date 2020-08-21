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