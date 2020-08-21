#pragma once

#include "BaseScope.h"

class GlobalScope : public BaseScope {
public:
    GlobalScope();
    std::string getScopeName() override;
};
