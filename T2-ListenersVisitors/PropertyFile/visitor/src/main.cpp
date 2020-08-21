#include "PropertyFileLexer.h"
#include "PropertyFileParser.h"
#include "PropertyFileBaseVisitor.h"

#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "tree/ParseTreeWalker.h"

#include <iostream>
#include <string>
#include <map>

namespace pfile {

class PropertyFileLoader : public PropertyFileBaseVisitor {
public:
	std::map<std::string, std::string> props;
	antlrcpp::Any visitProp(PropertyFileParser::PropContext *ctx) override {
		std::string id = ctx->ID()->getText();
		std::string value = ctx->STRING()->getText();
		props[id] = value;
		return nullptr; // must return something, even if we aren't using it
	}
};

}

void print_props(std::map<std::string, std::string> &props) {
	std::cout << '{';

	std::string comma = "";
	for (auto iter = props.begin(); iter != props.end(); iter++) {
		std::string id = iter->first;
		std::string value = iter->second;
		std::cout << comma << id << '=' << value;
		comma = ", ";
	}

	std::cout << "}\n";
}

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cout 
			<< "Missing required argument.\n"
			<< "Required arguments: <input file path>\n";
		return 1;
	}

	// ANTLRFileStream is a shortcut for creating your own 
	// input stream and ANTLRInputStream given a file name
	antlr4::ANTLRFileStream afs(argv[1]);

	pfile::PropertyFileLexer lexer(&afs);
	antlr4::CommonTokenStream tokens(&lexer);
	pfile::PropertyFileParser parser(&tokens);

	antlr4::tree::ParseTree *tree = parser.file();

	pfile::PropertyFileLoader loader;
	loader.visit(tree);
	print_props(loader.props);

	return 0;
}
