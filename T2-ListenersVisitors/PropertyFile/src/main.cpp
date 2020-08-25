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

// Refer to comments such as this one to gain a basic understanding of the structure
// of this project. When talking about file paths, we refer to them relative to the
// root of the project directory.
// For reference, this main.cpp file is in the folder `src/`

// After building the project, the four header files below should appear in `gen/pfile/`.
#include "PropertyFileLexer.h"
#include "PropertyFileParser.h"
#include "PropertyFileBaseListener.h"
#include "PropertyFileBaseVisitor.h"
// `gen/pfile/` is configured to be in the include path of this project via CMake
// which is why we can simply refer to them by name instead of a full path.

// CMake also handles inclusion of the ANTLR API, so the four header files below are also available.
#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "tree/ParseTreeWalker.h"

// You can include your standard C++ libraries as usual
#include <iostream>
#include <string>
#include <map>

// CMake is configured to produce a namespace for the ANTLR generated parsers and lexers.
// In this case it is named `pfile` but it will be different for each project.
namespace pfile {

// Ideally you will want to keep the declarations and definitions separated between
// header and cpp files, but this is a small example so we will not do that here.

/* Listener */
class PropertyFileLoaderListener : public PropertyFileBaseListener {
public:
	std::map<std::string, std::string> props;
	void exitProp(PropertyFileParser::PropContext *ctx) override {
		std::string id = ctx->ID()->getText(); // prop : ID '=' STRING '\n' ;
		std::string value = ctx->STRING()->getText();
		props[id] = value;
	}
};

/* Visitor */
class PropertyFileLoaderVisitor : public PropertyFileBaseVisitor {
public:
	std::map<std::string, std::string> props;
	antlrcpp::Any visitProp(PropertyFileParser::PropContext *ctx) override {
		std::string id = ctx->ID()->getText();
		std::string value = ctx->STRING()->getText();
		props[id] = value;
		return nullptr; // must return something, even if we aren't using the return value
	}
};

} // namespace pfile

// A utility function for mimicing Java's map.toString() and printing it.
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


	// Open the file then parse and lex it.
	antlr4::ANTLRFileStream afs(argv[1]);
	pfile::PropertyFileLexer lexer(&afs);
	antlr4::CommonTokenStream tokens(&lexer);
	pfile::PropertyFileParser parser(&tokens);

	// Get the root of the parse tree. Use your base rule name.
	antlr4::tree::ParseTree *tree = parser.file();

	// Use our PropertyFileLoader listener to load the properties
	pfile::PropertyFileLoaderListener loaderListener;
	antlr4::tree::ParseTreeWalker::DEFAULT.walk(&loaderListener, tree);
	std::cout << "Listener result: ";
	print_props(loaderListener.props);

	// Use our PropertyFileLoader visitor to load the properties
	pfile::PropertyFileLoaderVisitor loaderVisitor;
	loaderVisitor.visit(tree);
	std::cout << "Visitor result: ";
	print_props(loaderListener.props);

	return 0;
}
