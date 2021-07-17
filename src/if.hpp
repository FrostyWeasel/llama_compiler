#ifndef __IF_HPP__
#define __IF_HPP__

#include "expr.hpp"
#include "enums.hpp"
#include "type_variable.hpp"

//TODO:
/*
Η αποτίμησή της γίνεται ξεκινώντας από την αποτίμηση της e. Αν η τιμή
αυτής είναι true, τότε αποτιμάται η e1 και η τιμή αυτής είναι το αποτέλεσμα. Διαφορετικά, αποτιμάται
η e2 και η τιμή αυτής είναι το αποτέλεσμα. Σε κάθε περίπτωση, αποτιμάται μόνο ένα από τα τελούμενα
e1 και e2.
Το σκέλος else e2 μπορεί να παραλειφθεί, στην περίπτωση που η έκφραση e1 είναι τύπου unit.
Στην περίπτωση αυτή αν η συνθήκη είναι ψευδής δε γίνεται τίποτα.
*/
class If : public Expr{
public:
    If(Expr* condition, Expr* if_expr): condition(condition), if_expr(if_expr), else_expr(nullptr), Expr(new TypeVariable(TypeTag::Unit)) {}
    If(Expr* condition, Expr* if_expr, Expr* else_expr): condition(condition), if_expr(if_expr), else_expr(else_expr), Expr(new TypeVariable()) {}

    ~If() {
        delete condition;
        delete if_expr;
        delete else_expr;
    }

    virtual void print(std::ostream &out) const override {
        out << " if";
        if(condition != nullptr)
            condition->print(out);
        else
            out << " null";
        out << " then";
        if(if_expr != nullptr)
            if_expr->print(out);
        else
            out << " null";
        if(else_expr != nullptr){
            out << " else";
            else_expr->print(out);
        }
    }

    virtual std::shared_ptr<TypeVariable> infer() override {
        auto if_expr_type = this->if_expr->infer();
        
        if (else_expr != nullptr) {
            auto else_expr_type = this->else_expr->infer();

            st->add_constraint(if_expr_type, else_expr_type);
        }
        else {
            st->add_constraint(if_expr_type, std::make_shared<TypeVariable>(TypeTag::Unit));
        }

        auto condition_type = this->condition->infer();

        st->add_constraint(condition_type, std::make_shared<TypeVariable>(TypeTag::Bool));
        st->add_constraint(this->type_variable, if_expr_type);

        return if_expr_type;
    }

private:
    Expr* condition;
    Expr* if_expr;
    Expr* else_expr;

};

#endif