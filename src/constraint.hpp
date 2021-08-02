#ifndef __CONSTRAINT_HPP__
#define __CONSTRAINT_HPP__

#include "enums.hpp"
#include <memory>

class TypeVariable;

class Constraint {
public:
    Constraint(std::shared_ptr<TypeVariable> t1, std::shared_ptr<TypeVariable> t2);
    virtual ~Constraint();

    std::shared_ptr<TypeVariable> get_t1() { return t1; }
    std::shared_ptr<TypeVariable> get_t2() { return t2; }

    void set_t1(std::shared_ptr<TypeVariable> type) { this->t1 = type; }
    void set_t2(std::shared_ptr<TypeVariable> type) { this->t2 = type; }

private:
    std::shared_ptr<TypeVariable> t1;
    std::shared_ptr<TypeVariable> t2;
};

#endif