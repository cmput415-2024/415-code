#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "VerboseErrorListener.h"

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

using namespace antlr4;

void VerboseErrorListener::syntaxError(Recognizer *recognizer, Token * offendingSymbol,
                                     size_t line, size_t charPositionInLine,
                                     const std::string &msg, std::exception_ptr e) {
    std::cerr << "syntax error line " << line << ": " << msg << std::endl;

    std::cerr << std::endl << "Something to think about:" << std::endl;
    std::cerr << exec("fortune") << std::endl;
}
