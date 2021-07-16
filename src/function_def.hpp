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

class FunctionDef : public Def{
public:
    FunctionDef(std::string* id, Block<Par>* par_list, Expr* expr): id(*id), par_list(par_list), Def(new Type(TypeTag::Unknown, this)), expr(expr) {}
    FunctionDef(std::string* id, Block<Par>* par_list, Expr* expr, Type* type): id(*id), par_list(par_list), Def(type), expr(expr) {}

    ~FunctionDef() {
        delete expr;
        delete par_list;
    }

    virtual void print(std::ostream& out) const override{
        out << "FunctionDef(";
        out << " Id: " << id;
        out << " Type: ";
        if(type != nullptr)
            type->print(out);
        else
            out << "null ";
        out << ", Par_list: ";
        if(par_list != nullptr)
            par_list->print(out);
        else
            out << "null ";
        out << ", Expr: ";
        if(expr != nullptr)
            expr->print(out);
        else
            out << "null ";
        out << ") ";
    }

    virtual Type* infer() override {
        FunctionEntry* entry = new FunctionEntry(id, EntryType::ENTRY_FUNCTION, this->type, nullptr);

        this->st->insert_entry(entry);

        //Function scope includes parameters and body
        this->st->scope_open(); 

        Type* from_type = this->par_list->infer();

        entry->set_from_type(from_type);

        Type* to_type = this->expr->infer();

        //TODO: to type cannot be a function 

        //Function return type must be the same as its body expr type.
        this->st->add_constraint(this->type, to_type);

        this->st->scope_close();

        return this->type;
    }

private:
    std::string id;
    Block<Par>* par_list;
    Expr* expr;
};

#endif