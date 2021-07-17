#ifndef __FOR_HPP__
#define __FOR_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
#include "constant_entry.hpp"
#include "enums.hpp"
#include <memory>
#include <string>
#include <iostream>

class For : public Expr {
public:
    For() {}
    For(std::string* id, Expr* first_condition, Expr* second_condition, Expr* expr): id(*id), first_condition(first_condition), second_condition(second_condition), expr(expr), Expr(new TypeVariable(TypeTag::Unit)) {}

    ~For() {
        delete first_condition;
        delete second_condition;
        delete expr;
    }

    virtual void print(std::ostream &out) const override = 0;

    virtual std::shared_ptr<TypeVariable> infer() override {
        auto first_condition_type = this->first_condition->infer();
        auto second_condition_type = this->second_condition->infer();

        st->scope_open();

        ConstantEntry* entry = new ConstantEntry(id, EntryType::ENTRY_CONSTANT, std::make_shared<TypeVariable>(TypeTag::Int));
        st->insert_entry(entry);

        auto expr_type = this->expr->infer();        

        st->scope_close();
        
        st->add_constraint(first_condition_type, std::make_shared<TypeVariable>(TypeTag::Int));
        st->add_constraint(second_condition_type, std::make_shared<TypeVariable>(TypeTag::Int));
        st->add_constraint(expr_type, std::make_shared<TypeVariable>(TypeTag::Unit));

        return this->type_variable;
    }

protected:
    std::string id;
    Expr* first_condition;
    Expr* second_condition;
    Expr* expr;

};

#endif