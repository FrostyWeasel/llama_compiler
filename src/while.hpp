#ifndef __WHILE_HPP__
#define __WHILE_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
#include "enums.hpp"
#include <memory>
#include <iostream>

class While : public Expr{
public:
    While(Expr* condition, Expr* expr): condition(condition), expr(expr), Expr(new TypeVariable(TypeTag::Unit)) {}

    ~While() {
        delete condition;
        delete expr;
    }

    virtual void print(std::ostream &out) const override {
        out << "while ";
        if(condition != nullptr)
            condition->print(out);
        else
            out << " null";
        out << " do";
        if(expr != nullptr)
            expr->print(out);
        else
            out << " null";
        out << " done";
    }

    virtual std::shared_ptr<TypeVariable> infer() override {
        auto condition_type = this->condition->infer();
        auto expr_type = this->expr->infer();        
        
        st->add_constraint(condition_type, std::make_shared<TypeVariable>(TypeTag::Bool));
        st->add_constraint(expr_type, std::make_shared<TypeVariable>(TypeTag::Unit));

        return this->type_variable;
    }

private:
    Expr* condition;
    Expr* expr;

};

#endif