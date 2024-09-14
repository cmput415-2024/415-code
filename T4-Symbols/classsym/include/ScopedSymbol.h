#pragma once

#include <string>
#include <memory>
#include <map>

#include "Symbol.h"
#include "Scope.h"
#include "Type.h"

class ScopedSymbol : public Symbol, public Scope {
 public:
    std::shared_ptr<Scope> enclosingScope;

    ScopedSymbol(std::string name, std::shared_ptr<Scope> enClosingScope);
    ScopedSymbol(std::string name, std::shared_ptr<Type> type,
                 std::shared_ptr<Scope> enClosingScope);

    virtual std::shared_ptr<Scope> getEnclosingScope() override;
    virtual void setEnclosingScope(std::shared_ptr<Scope> scope) override;
    virtual std::string getScopeName() override;

    virtual ~ScopedSymbol();
};

class StructSymbol : public ScopedSymbol, public Type {
public:
	std::map<std::string, std::shared_ptr<Symbol>> fields;

    StructSymbol(std::string name, std::shared_ptr<Scope> enclosingScope);

    void define(std::shared_ptr<Symbol> sym) override;

    virtual std::shared_ptr<Symbol> resolve(const std::string &name) override;
    virtual std::shared_ptr<Symbol> resolveMember(const std::string &name);

    virtual std::string getName() override;

    virtual std::string toString() override;
};

class ClassSymbol : public StructSymbol {
public:
    std::shared_ptr<ClassSymbol> superClass;

    ClassSymbol(std::string name, std::shared_ptr<Scope> enclosingScope)
        : StructSymbol(name, enclosingScope) {}

    virtual std::shared_ptr<Symbol> resolveMember(const std::string &name) override;

    virtual std::string toString() override;
};
