#include "DataLexer.h"
#include "DataParser.h"

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

	antlr4::ANTLRFileStream afs(argv[1]);
	data::DataLexer lexer(&afs);
	antlr4::CommonTokenStream tokens(&lexer);
	data::DataParser parser(&tokens);

	antlr4::tree::ParseTree *tree = parser.file();
	std::cout << antlr4::tree::Trees::toStringTree(tree, &parser) << '\n';

	return 0;
}
