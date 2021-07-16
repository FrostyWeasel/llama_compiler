#ifndef __TYPEVARIABLE_HPP__
#define __TYPEVARIABLE_HPP__

#include <memory>
#include "iostream"
#include "enums.hpp"

class Type;

class TypeVariable {
public:
    TypeVariable();
    TypeVariable(TypeTag type_tag);
    TypeVariable(TypeTag type_tag, TypeVariable* t1);
    TypeVariable(TypeTag type_tag, TypeVariable* t1, TypeVariable* t2);
    TypeVariable(TypeTag type_tag, TypeVariable* t1, int dim);

    ~TypeVariable() = default;

    void print(std::ostream& out) const;

    bool contains(TypeVariable* type_variable);
    void bind(TypeVariable* bound_type);

    TypeVariable* get_function_from_type();
    TypeVariable* get_function_to_type();
    TypeVariable* get_referenced_type();

    TypeTag get_tag();
    TypeVariableTag get_variable_tag();

private:
    std::shared_ptr<Type> type;
    TypeVariableTag tag;
    unsigned int id;

    static unsigned int counter;

    bool is_bound();
};

inline std::ostream& operator<<(std::ostream& out, const TypeVariable& type_variable){
    type_variable.print(out);
    return out;
}


#endif