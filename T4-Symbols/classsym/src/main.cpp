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

#include "CymbolLexer.h"
#include "CymbolParser.h"

#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "tree/ParseTreeWalker.h"

#include <iostream>
#include <string>
#include <memory>

#include "SymbolTable.h"
#include "ASTBuilder.h"
#include "ASTWalker.h"
#include "VerboseErrorListener.h"

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cout 
			<< "Missing required argument.\n"
			<< "Required arguments: <input file path>\n";
		return 1;
	}

	antlr4::ANTLRFileStream afs; 
	afs.loadFromFile(argv[1]);
	classsym::CymbolLexer lexer(&afs);
	antlr4::CommonTokenStream tokens(&lexer);
	classsym::CymbolParser parser(&tokens);

    parser.removeErrorListeners();
    parser.addErrorListener(new antlr4::VerboseErrorListener());

	antlr4::tree::ParseTree *tree = parser.compilationUnit();

    std::cerr << "Building AST" << std::endl;
	classsym::ASTBuilder builder;
	std::shared_ptr<AST> ast = std::any_cast<std::shared_ptr<AST>>(builder.visit(tree));

    std::cerr << "Building SymbolTable" << std::endl;
    SymbolTable symbolTable;

	DefineSymbols defsyms(&symbolTable);
	defsyms.visit(ast);

    std::cout << symbolTable.toString() << std::endl;

    std::cerr << "Resolving References" << std::endl;
	ResolveSymbols refsyms;
	refsyms.visit(ast);

    bool a = true;
    bool b = true;
    std::cout << "math on bools: " << a + b << std::endl;
    
	return 0;
}
