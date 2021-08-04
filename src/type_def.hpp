#ifndef __TYPE_DEF_HPP__
#define __TYPE_DEF_HPP__

#include "definition.hpp"
#include "block.hpp"
#include "enums.hpp"
#include "symbol_table.hpp"

class TDef;

class TypeDef : public Definition {
public:    
    TypeDef(Block<TDef>* t_defs);

    virtual ~TypeDef();
  
    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    Block<TDef>* t_defs;
};

#endif
