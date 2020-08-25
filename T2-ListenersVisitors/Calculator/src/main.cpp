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

#include "LabeledExprLexer.h" 
#include "LabeledExprParser.h"

#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"

#include "EvalVisitor.h" // This file is from `include/EvalVisitor.h`.
// `include/` is configured to be in the include path of this project via CMake
// which is why we can simply refer to EvalVisitor.h by name instead of a full path.

int main(int argc, char **argv) {

	if (argc < 2) {
		std::cout 
			<< "Missing required argument.\n"
			<< "Required arguments: <input file path>\n";
		return 1;
	}

	// Open the file then parse and lex it.
	antlr4::ANTLRFileStream afs(argv[1]); 
	calc::LabeledExprLexer lexer(&afs);
	antlr4::CommonTokenStream tokens(&lexer);
	calc::LabeledExprParser parser(&tokens);

	// Get the root of the parse tree. Use your base rule name.
	antlr4::tree::ParseTree *tree = parser.prog();

	calc::EvalVisitor eval;
	eval.visit(tree);

	return 0;
}
