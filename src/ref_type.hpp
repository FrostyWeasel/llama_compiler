#ifndef __REFTYPE_HPP__
#define __REFTYPE_HPP__

#include "type.hpp"
#include "includes.hpp"


class RefType : public Type{
public:
    RefType(Type* type) : type(type) {}

    ~RefType() {
	std::cout << "RefType deleted\n";
        delete type;
    }

    virtual void print(std::ostream &out) const { 
        if (type == nullptr)
            out << "Type: Null";
        else
            out << *type << " ref ";
    }
    
private:
    Type* type;

};

#endif