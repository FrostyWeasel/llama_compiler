#ifndef __DELETE_HPP__
#define __DELETE_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
#include <memory>
#include <iostream>

class Delete : public Expr{
public:
    Delete(Expr* expr): expr(expr), Expr(new TypeVariable(TypeTag::Unit)) {}
    ~Delete()  {}

    virtual void print(std::ostream &out) const override {
        out << " delete";
        if(expr != nullptr)
            expr->print(out);
        else
            out << " null";
    }

    virtual std::shared_ptr<TypeVariable> infer() override {
        auto expr_type = this->expr->infer();

        //Expr must be t ref
        st->add_constraint(expr_type, std::make_shared<TypeVariable>(TypeTag::Reference, std::make_shared<TypeVariable>()));

        //Result is always type ()
        return this->type_variable;
    }

    virtual void sem() override {
        this->expr->sem();
    }

private:
    Expr* expr;
};

#endif