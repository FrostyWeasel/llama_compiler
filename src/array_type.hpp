#ifndef __ARRAYTYPE_HPP__
#define __ARRAYTYPE_HPP__

#include "enums.hpp"
#include "type.hpp"
#include <memory>

class TypeVariable;

class ArrayType : public Type {
public:
    ArrayType(TypeVariable* type_variable, DimType dim_type);
    ArrayType(TypeVariable* type_variable, unsigned int dimensions, DimType dim_type);
    ArrayType(std::shared_ptr<TypeVariable> type_variable, DimType dim_type);
    ArrayType(std::shared_ptr<TypeVariable> type_variable, unsigned int dimensions, DimType dim_type);

    virtual ~ArrayType();

    virtual bool contains(std::shared_ptr<TypeVariable> type_variable) override;

    std::shared_ptr<TypeVariable> get_array_type();

    DimType get_dim_type();
    void set_dim_type(DimType dim_type);
    unsigned int get_dim();
    void set_dim(unsigned int dim);


    virtual void print(std::ostream &out) const override;

private:
    std::shared_ptr<TypeVariable> type_variable;
    unsigned int dimensions;
    DimType dim_type;
};

#endif