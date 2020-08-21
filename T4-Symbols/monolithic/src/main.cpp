#include "CymbolLexer.h"
#include "CymbolParser.h"

#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "tree/ParseTreeWalker.h"

#include <iostream>
#include <string>

#include "MyVisitor.h"

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

	mono::MyVisitor visitor;
	visitor.visit(tree);

	return 0;
}
