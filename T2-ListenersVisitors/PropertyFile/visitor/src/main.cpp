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
