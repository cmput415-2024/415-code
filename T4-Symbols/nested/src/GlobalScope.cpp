#include "GlobalScope.h"

GlobalScope::GlobalScope() : BaseScope(nullptr) {}

std::string GlobalScope::getScopeName() {
    return "global";
}
