#include "enums.hpp"
#include "type_variable.hpp"

class Constraint {
public:
    Constraint(TypeVariable* t1, TypeVariable* t2) : t1(t1), t2(t2) { 

    }
    ~Constraint() { }

    TypeVariable* get_t1() { return t1; }
    TypeVariable* get_t2() { return t2; }

    void set_t1(TypeVariable* type) { this->t1 = type; }
    void set_t2(TypeVariable* type) { this->t2 = type; }

private:
    TypeVariable* t1;
    TypeVariable* t2;
};