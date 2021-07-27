#ifndef __CONSTANTDEF_HPP__
#define __CONSTANTDEF_HPP__

#include "expr.hpp"
#include "def.hpp"
#include "type.hpp"
#include "symbol_entry.hpp"
#include "constant_entry.hpp"
#include <string>

class ConstDef : public Def{
public:
    ConstDef(std::string* id, Expr* expr): id(*id), expr(expr), Def(new TypeVariable()) {}
    ConstDef(std::string* id, std::shared_ptr<TypeVariable> type_variable, Expr* expr): id(*id), Def(type_variable), expr(expr) {}

    virtual ~ConstDef() {
        delete expr;
    }

    virtual void print(std::ostream& out) const override;

    virtual void add_to_symbol_table() override;

    virtual void allocate() override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;
private:
    std::string id;
    Expr* expr;
};

#endif