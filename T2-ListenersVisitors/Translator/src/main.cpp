#include "JavaLexer.h"
#include "JavaParser.h"

#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"

#include "ExtractInterfaceListener.h"

int main(int argc, char **argv) {

	if (argc < 2) {
		std::cout 
			<< "Missing required argument.\n"
			<< "Required arguments: <input file path>\n";
		return 1;
	}

	antlr4::ANTLRFileStream afs(argv[1]); 
	trans::JavaLexer lexer(&afs);
	antlr4::CommonTokenStream tokens(&lexer);
	trans::JavaParser parser(&tokens);

	antlr4::tree::ParseTree *tree = parser.compilationUnit();

	trans::ExtractInterfaceListener extractor(&parser);
	antlr4::tree::ParseTreeWalker::DEFAULT.walk(&extractor, tree);

	return 0;
}
