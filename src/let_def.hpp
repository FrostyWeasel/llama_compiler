#ifndef __LETDEF_HPP__
#define __LETDEF_HPP__

// #include "global_variables.hpp"
#include "ast.hpp"
#include "def.hpp"
#include "block.hpp"
#include "enums.hpp"
#include "symbol_table.hpp"

// *: This type of expression uses the new x whose value is undefined : let x = 5 let rec x = x + 6 (i think that this is correct)
class LetDef : public AST{
public:    
    LetDef(Block<Def>* def, LetType let_type): def(def), let_type(let_type) {}

    virtual ~LetDef() {
        delete def;
    }
  
    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    Block<Def>* def;
    LetType let_type;
};

#endif
