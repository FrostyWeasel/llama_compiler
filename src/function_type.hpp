#ifndef __FUNCTIONTYPE_HPP__
#define __FUNCTIONTYPE_HPP__

#include "type.hpp"
#include "includes.hpp"

class FunctionType : public Type{
public:
    FunctionType(Type* from_type, Type* to_type): from_type(from_type), to_type(to_type) {}
    
    virtual void print(std::ostream &out) const { 
        if (from_type == nullptr)
            out << "from_type: Null ";
        else
            out << *from_type << " ";
        out << " -> ";
        if (to_type == nullptr)
            out << "to_type: Null ";
        else
            out << *to_type << " ";

    }
    
private:
    Type* from_type;
    Type* to_type;
};

#endif