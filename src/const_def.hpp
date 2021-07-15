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
    ConstDef(std::string* id, Expr* expr): id(*id), expr(expr), Def(new Type(TypeTag::Unknown, this)) {}
    ConstDef(std::string* id, Type* type, Expr* expr): id(*id), Def(type), expr(expr) {}

    ~ConstDef() {
        delete expr;
    }

    virtual void print(std::ostream& out) const override{
        out << "ConstDef(";
        out << " Id: " << id;
        out << " Type: ";
        if(type != nullptr)
            type->print(out);
        else
            out << "null ";
        out << " Expr: ";
        if(expr != nullptr)
            expr->print(out);
        else
            out << "null ";
        out << ") ";
    }

    virtual Type* infer() override {
        ConstantEntry* entry = new ConstantEntry(id, EntryType::ENTRY_CONSTANT, this->type);
        st->insert_entry(entry);

        auto expr_type = this->expr->infer();

        st->add_constraint(this->type, expr_type);

        return this->type;
    }

    virtual void sem() override {

    }

private:
    std::string id;
    Expr* expr;
};

#endif