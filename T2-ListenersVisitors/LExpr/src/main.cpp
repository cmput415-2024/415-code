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
