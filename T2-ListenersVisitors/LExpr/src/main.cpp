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

#include "LExprLexer.h"
#include "LExprParser.h"

#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"

#include "EvalVisitor.h"
#include "Evaluator.h"
#include "EvaluatorWithProps.h"

int main(int argc, char **argv) {

	if (argc < 2) {
		std::cout 
			<< "Missing required argument.\n"
			<< "Required arguments: <input file path>\n";
		return 1;
	}

	antlr4::ANTLRFileStream afs(argv[1]); 
	lexpr::LExprLexer lexer(&afs);
	antlr4::CommonTokenStream tokens(&lexer);
	lexpr::LExprParser parser(&tokens);

	antlr4::tree::ParseTree *tree = parser.s();

	lexpr::EvalVisitor visitor;
	int visitor_result = visitor.visit(tree);
	std::cout << "visitor result = " << visitor_result << '\n';

	lexpr::Evaluator eval;
	antlr4::tree::ParseTreeWalker::DEFAULT.walk(&eval, tree);
	std::cout << "stack result = " << eval.stack.top() << '\n';

	lexpr::EvaluatorWithProps evalProps;
	antlr4::tree::ParseTreeWalker::DEFAULT.walk(&evalProps, tree);
	std::cout << "properties result = " << evalProps.getValue(tree) << '\n';

	return 0;
}
