/* code without explicit authorization from CMPUT 415
 * Teaching Staff is prohibited.
 * 
 * If this code is found in any public website or public repository, the
 * person finding it is kindly requested to immediately report, including 
 * the URL or other repository locating information, to the following email
 * address:
 *
 *          cmput415@ualberta.ca
***/

#include "ScopedSymbol.h"

ScopedSymbol::ScopedSymbol(std::string name, std::shared_ptr<Scope> scope)
    : Symbol(name), enclosingScope(scope) {}
ScopedSymbol::ScopedSymbol(std::string name, std::shared_ptr<Type> type,
                           std::shared_ptr<Scope> scope)
    : Symbol(name, type), enclosingScope(scope) {}

std::shared_ptr<Scope> ScopedSymbol::getEnclosingScope() {
    return enclosingScope;
}

ScopedSymbol::~ScopedSymbol() {}

