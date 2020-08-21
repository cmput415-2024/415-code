#include "CymbolLexer.h"
#include "CymbolParser.h"

#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "tree/ParseTreeWalker.h"

#include <iostream>
#include <string>
#include <memory>

#include "AST.h"
#include "ASTBuilder.h"
#include "DefRef.h"

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cout 
			<< "Missing required argument.\n"
			<< "Required arguments: <input file path>\n";
		return 1;
	}

	antlr4::ANTLRFileStream afs(argv[1]);
	nested::CymbolLexer lexer(&afs);
	antlr4::CommonTokenStream tokens(&lexer);
	nested::CymbolParser parser(&tokens);

	antlr4::tree::ParseTree *tree = parser.compilationUnit();

	nested::ASTBuilder builder;
	std::shared_ptr<AST> ast = builder.visit(tree);

	DefRef defref;
	defref.visit(ast);

	return 0;
}
