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
    ConstDef(std::string* id, TypeVariable* type_variable, Expr* expr): id(*id), Def(type_variable), expr(expr) {}

    ~ConstDef() {
        delete expr;
    }

    virtual void print(std::ostream& out) const override{
        out << "ConstDef(";
        out << " Id: " << id;
        out << " Type: ";
        if(type_variable != nullptr)
            type_variable->print(out);
        else
            out << "null ";
        out << " Expr: ";
        if(expr != nullptr)
            expr->print(out);
        else
            out << "null ";
        out << ") ";
    }

    virtual TypeVariable* infer() override {
        ConstantEntry* entry = new ConstantEntry(id, EntryType::ENTRY_CONSTANT, this->type_variable);
        
        st->insert_entry(entry);

        auto expr_type = this->expr->infer();

        st->add_constraint(this->type_variable, expr_type);

        return this->type_variable;
    }

    virtual void sem() override {

    }

private:
    std::string id;
    Expr* expr;
};

#endif