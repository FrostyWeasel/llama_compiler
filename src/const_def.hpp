#ifndef __CONSTANTDEF_HPP__
#define __CONSTANTDEF_HPP__

#include "def.hpp"
#include <string>
#include <memory>

class Expr;
class TypeVariable;

class ConstDef : public Def{
public:
    ConstDef(std::string* id, Expr* expr);
    ConstDef(std::string* id, std::shared_ptr<TypeVariable> type_variable, Expr* expr);

    virtual ~ConstDef();

    virtual void print(std::ostream& out) const override;

    virtual void add_to_symbol_table() override;

    virtual void allocate() override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

    virtual std::string get_id() override { return this->id; }

private:
    std::string id;
    Expr* expr;
};

#endif