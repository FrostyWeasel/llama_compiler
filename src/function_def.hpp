#ifndef __FUNCTIONDEF_HPP__
#define __FUNCTIONDEF_HPP__

#include "enums.hpp"
#include "type.hpp"
#include "block.hpp"
#include "par.hpp"
#include "expr.hpp"
#include "def.hpp"
#include "symbol_entry.hpp"
#include "function_entry.hpp"
#include <string>
#include <iostream>

class FunctionEntry;

class FunctionDef : public Def {
public:
    FunctionDef(std::string* id, Block<Par>* par_list, Expr* expr): id(*id), par_list(par_list), Def(new TypeVariable()), expr(expr) {}
    FunctionDef(std::string* id, Block<Par>* par_list, Expr* expr, std::shared_ptr<TypeVariable> type_variable): id(*id), par_list(par_list), Def(type_variable), expr(expr) {}

    ~FunctionDef() {
        delete expr;
        delete par_list;
    }

    virtual void print(std::ostream& out) const override{
        out << " " << id;
        if(par_list != nullptr)
            par_list->print(out);
        else
            out << "null ";
        out << " :";
        if(type_variable != nullptr)
            type_variable->print(out);
        else
            out << "null ";

        out << " = ";
        if(expr != nullptr)
            expr->print(out);
        else
            out << "null ";
    }

    virtual void add_to_symbol_table() override {
        FunctionEntry* entry = new FunctionEntry(id, EntryType::ENTRY_FUNCTION, std::make_shared<TypeVariable>(), this->type_variable);
        
        st->insert_entry(entry);

        this->entry = entry;
    }

    virtual std::shared_ptr<TypeVariable> infer() override {
        FunctionEntry* func_entry = dynamic_cast<FunctionEntry*>(this->entry);

        //Function scope includes parameters and body
        st->scope_open(); 

        std::shared_ptr<TypeVariable> from_type = this->par_list->infer();

        //Function from type must be the same as the type of its parameter list.
        st->add_constraint(func_entry->get_from_type(), from_type);

        std::shared_ptr<TypeVariable> to_type = this->expr->infer();

        //TODO:Sem to type cannot be a function 

        //Function return type must be the same as its body expr type.
        st->add_constraint(this->type_variable, to_type);

        st->scope_close();

        return this->type_variable;
    }

private:
    std::string id;
    Block<Par>* par_list;
    Expr* expr;
};

#endif