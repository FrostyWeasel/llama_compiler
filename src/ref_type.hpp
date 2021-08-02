#ifndef __REFTYPE_HPP__
#define __REFTYPE_HPP__

#include "enums.hpp"
#include "type.hpp"
#include <memory>
#include <iostream>

class TypeVariable;

class RefType : public Type {
public:
    RefType(TypeVariable* type_variable);
    RefType(std::shared_ptr<TypeVariable> type_variable);

    virtual ~RefType();

    virtual bool contains(std::shared_ptr<TypeVariable> type_variable) override;

    std::shared_ptr<TypeVariable> get_referenced_variable();

    virtual void print(std::ostream &out) const override;

    unsigned int get_depth();

    TypeTag get_bottom_tag();
    
private:
    std::shared_ptr<TypeVariable> type_variable;
};

#endif