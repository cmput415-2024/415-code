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

// Note: this code makes heavy use of C++ Smart Pointers.
// Smart Pointers are a way of providing pointers while automatically
// managing memory (such as remembering to `delete` every `new` object).
// Recommended resource: https://docs.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp

// You do not need to use smart pointers in your assignments, but knowing
// how to use them can greatly simplify memory management.

#include "CymbolLexer.h"
#include "CymbolParser.h"

#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "tree/ParseTreeWalker.h"

#include <iostream>
#include <string>

#include "DefRef.h"

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cout 
			<< "Missing required argument.\n"
			<< "Required arguments: <input file path>\n";
		return 1;
	}

	antlr4::ANTLRFileStream afs(argv[1]);
	mono::CymbolLexer lexer(&afs);
	antlr4::CommonTokenStream tokens(&lexer);
	mono::CymbolParser parser(&tokens);

	antlr4::tree::ParseTree *tree = parser.compilationUnit();

	mono::DefRef visitor;
	visitor.visit(tree);

	return 0;
}
