#ifndef __TYPEVARIABLE_HPP__
#define __TYPEVARIABLE_HPP__

#include <memory>
#include <vector>
#include "iostream"
#include "enums.hpp"

class Type;
class ErrorHandler;

class TypeVariable {
public:
    TypeVariable();
    TypeVariable(TypeTag type_tag);
    TypeVariable(TypeTag type_tag, TypeVariable* t1);
    TypeVariable(TypeTag type_tag, TypeVariable* t1, TypeVariable* t2, unsigned int parameter_count);
    TypeVariable(TypeTag type_tag, TypeVariable* t1, TypeVariable* t2, FunctionTypeTag function_tag=FunctionTypeTag::Actual);
    TypeVariable(TypeTag type_tag, TypeVariable* t1, unsigned int dim);
    TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1);
    TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1, std::shared_ptr<TypeVariable> t2, unsigned int parameter_count);
    TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1, std::shared_ptr<TypeVariable> t2, FunctionTypeTag function_tag=FunctionTypeTag::Actual);
    TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1, unsigned int dim);
    TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1, DimType dim_type);
    TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1, unsigned int dim, DimType dim_type);
    TypeVariable(TypeTag type_tag, std::string* user_type_id);
    TypeVariable(TypeTag type_tag, std::string user_type_id);

    ~TypeVariable() = default;

    bool operator== (const TypeVariable& rhs) const;

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

    unsigned int get_function_parameter_count();
    void set_function_parameter_count(unsigned int parameter_count);

    FunctionTypeTag get_function_type_tag();
    void set_function_type_tag(FunctionTypeTag function_type);

    TypeTag get_tag();
    TypeVariableTag get_variable_tag();

    unsigned int get_complex_type_depth();
    TypeTag get_bottom_tag();

    inline void set_default_type(TypeTag default_type) { this->default_type = default_type; }
    //inline TypeTag get_default_type() { return this->default_type; }

    inline unsigned int get_id() { return this->id; }

    void set_tag_to_default();

    std::string& get_user_type_id();

    static bool are_user_types_the_same(std::shared_ptr<TypeVariable> t1, std::shared_ptr<TypeVariable> t2);

private:
    std::shared_ptr<Type> type;
    TypeVariableTag tag;
    TypeTag default_type = TypeTag::Unit;
    unsigned int id;

    static unsigned int counter;

    bool is_bound();

    static std::unique_ptr<ErrorHandler> error_handler;
};

inline std::ostream& operator<<(std::ostream& out, const TypeVariable& type_variable){
    type_variable.print(out);
    return out;
}


#endif