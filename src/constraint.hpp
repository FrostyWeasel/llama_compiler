#include "enums.hpp"

class Type;

class Constraint {
public:
    Constraint(Type* t1, Type* t2) : t1(t1), t2(t2) { 

    }
    ~Constraint() { }

    Type* get_t1() { return t1; }
    Type* get_t2() { return t2; }

    void set_t1(Type* type) { this->t1 = type; }
    void set_t2(Type* type) { this->t2 = type; }

private:
    Type* t1;
    Type* t2;
};