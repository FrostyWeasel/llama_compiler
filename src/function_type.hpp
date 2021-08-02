#ifndef __FUNCTIONTYPE_HPP__
#define __FUNCTIONTYPE_HPP__

#include "type.hpp"
#include "enums.hpp"
#include <iostream>
#include <memory>

class TypeVariable;

class FunctionType : public Type {
public:
    FunctionType(TypeVariable* from_type_variable, TypeVariable* to_type_variable, FunctionTypeTag function_type);
    FunctionType(std::shared_ptr<TypeVariable> from_type_variable, std::shared_ptr<TypeVariable> to_type_variable, FunctionTypeTag function_type);
    FunctionType(TypeVariable* from_type_variable, TypeVariable* to_type_variable, unsigned int parameter_count, FunctionTypeTag function_type);
    FunctionType(std::shared_ptr<TypeVariable> from_type_variable, std::shared_ptr<TypeVariable> to_type_variable, unsigned int parameter_count, FunctionTypeTag function_type);

    virtual ~FunctionType();

    virtual bool contains(std::shared_ptr<TypeVariable> type_variable) override;

    std::shared_ptr<TypeVariable> get_from_type_variable();

    std::shared_ptr<TypeVariable> get_to_type_variable();

    virtual void print(std::ostream &out) const override;

    unsigned int get_parameter_count();
    void set_parameter_count(unsigned int parameter_count);
    
private:
    std::shared_ptr<TypeVariable> from_type_variable;
    std::shared_ptr<TypeVariable> to_type_variable;
    unsigned int parameter_count;
    FunctionTypeTag function_type_tag;

    friend TypeVariable;
};

#endif