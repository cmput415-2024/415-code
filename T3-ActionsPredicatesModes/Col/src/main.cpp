#include "RowsLexer.h"
#include "RowsParser.h"

#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "tree/ParseTreeWalker.h"

#include <iostream>
#include <string>

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cout 
			<< "Missing required argument.\n"
			<< "Required arguments: <input file path>\n";
		return 1;
	}

	int col = std::stoi(argv[1]);

	antlr4::ANTLRFileStream afs(argv[2]);
	col::RowsLexer lexer(&afs);
	antlr4::CommonTokenStream tokens(&lexer);
	col::RowsParser parser(&tokens, col);
	parser.setBuildParseTree(false); // don't waste time bulding a tree
	parser.file(); // parse


	return 0;
}
