#ifndef __FUNCTIONTYPE_HPP__
#define __FUNCTIONTYPE_HPP__

#include "type.hpp"
#include "includes.hpp"

class FunctionType : public Type {
public:
    FunctionType(Type* from_type, Type* to_type): from_type(from_type), to_type(to_type), Type(TypeTag::Function) {}
    
    ~FunctionType() {
        delete from_type;
        delete to_type;
    }

    void set_from_type(TypeTag tag) { this->from_type->set_tag(tag); }
    void set_to_type(TypeTag tag) { this->to_type->set_tag(tag); }

    // //TODO: Perhaps we should check if from and to types are array or ref types.
    // bool contains(Type* type) {
    //     if(from_type != nullptr) {
    //         if(!from_type->is_function())
    //             return from_type == type;
    //         else {
    //             FunctionType* func_from_type = dynamic_cast<FunctionType*>(from_type);
    //             if(func_from_type->contains(type))
    //                 return true;
    //         } 
    //     }
    //     else if(to_type != nullptr) {
    //         if(!to_type->is_function())
    //             return to_type == type;
    //         else {
    //             FunctionType* func_to_type = dynamic_cast<FunctionType*>(to_type);
    //             if(func_to_type->contains(type))
    //                 return true;
    //         } 
    //     }

    //     return false;
    // }

    virtual void print(std::ostream &out) const override{ 
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