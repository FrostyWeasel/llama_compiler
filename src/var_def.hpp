#ifndef __VARDEF_HPP__
#define __VARDEF_HPP__

#include "type_variable.hpp"
#include "variable_entry.hpp"
#include "enums.hpp"
#include "def.hpp"
#include <memory>

class VarDef : public Def{
public:
    VarDef(std::string* id): id(*id), Def(new TypeVariable(TypeTag::Reference, std::make_shared<TypeVariable>(TypeTag::Unknown))) {}
    VarDef(std::string* id, std::shared_ptr<TypeVariable> type_variable): id(*id), Def(new TypeVariable(TypeTag::Reference, type_variable)) {}

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