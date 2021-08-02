#ifndef __VARDEF_HPP__
#define __VARDEF_HPP__

#include "enums.hpp"
#include "def.hpp"
#include <memory>
#include <string>

class TypeVariable;

class VarDef : public Def{
public:
    VarDef(std::string* id);
    VarDef(std::string* id, std::shared_ptr<TypeVariable> type_variable);

    virtual void print(std::ostream& out) const override;

    virtual void add_to_symbol_table() override;

    virtual void allocate() override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    std::string id;
};

#endif