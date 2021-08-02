#include "constraint.hpp"
#include "type_variable.hpp"
#include <memory>

Constraint::Constraint(std::shared_ptr<TypeVariable> t1, std::shared_ptr<TypeVariable> t2) : t1(t1), t2(t2) { }
Constraint::~Constraint() { }