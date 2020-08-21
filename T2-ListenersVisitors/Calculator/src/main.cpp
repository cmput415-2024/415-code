#include "LabeledExprLexer.h"
#include "LabeledExprParser.h"

#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"

#include "EvalVisitor.h"

int main(int argc, char **argv) {

	if (argc < 2) {
		std::cout 
			<< "Missing required argument.\n"
			<< "Required arguments: <input file path>\n";
		return 1;
	}

	antlr4::ANTLRFileStream afs(argv[1]); 
	calc::LabeledExprLexer lexer(&afs);
	antlr4::CommonTokenStream tokens(&lexer);
	calc::LabeledExprParser parser(&tokens);

	antlr4::tree::ParseTree *tree = parser.prog();

	calc::EvalVisitor eval;
	eval.visit(tree);

	return 0;
}
