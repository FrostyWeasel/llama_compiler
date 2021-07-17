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
    TypeVariable(TypeTag type_tag, TypeVariable* t1, unsigned int dim);
    TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1);
    TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1, std::shared_ptr<TypeVariable> t2);
    TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1, unsigned int dim);
    TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1, DimType dim_type);
    TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1, unsigned int dim, DimType dim_type);

    ~TypeVariable() = default;

    void print(std::ostream& out) const;

    bool contains(std::shared_ptr<TypeVariable> type_variable);
    void bind(std::shared_ptr<TypeVariable> bound_type);

    std::shared_ptr<TypeVariable> get_function_from_type();
    std::shared_ptr<TypeVariable> get_function_to_type();
    std::shared_ptr<TypeVariable> get_referenced_type();
    std::shared_ptr<TypeVariable> get_array_type();

    unsigned int get_array_dim();
    void set_array_dim(unsigned int dim);
    DimType get_array_dim_type();
    void set_array_dim_type(DimType dim_type);

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