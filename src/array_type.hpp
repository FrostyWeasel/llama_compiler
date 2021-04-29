#ifndef __ARRAYTYPE_HPP__
#define __ARRAYTYPE_HPP__

#include "type.hpp"
#include "includes.hpp"


class ArrayType : public Type{
public:
    ArrayType(Type* type) {}
    ArrayType(Type* type, int dimensions) {}
};

#endif