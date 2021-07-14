#ifndef __VARDEF_HPP__
#define __VARDEF_HPP__

#include "includes.hpp"

//TODO: Symboltable: Should have a memory slot capable of holding an elements of its type.
//TODO: TypeCheck: Type can be whatever.
//TODO: TypeInference: Type is type ref

class VarDef : public Def{
public:
    VarDef(std::string* id): id(*id), Def(new Type(TypeTag::Unknown)) {}
    VarDef(std::string* id, Type* type): id(*id), Def(type) {}

    virtual void print(std::ostream& out) const override{
        out << "VarDef(";
        out << " Id: " << id;
        out << " Type: ";
        if(type != nullptr)
            type->print(out);
        else
            out << "null ";
        out << ") ";
    }

    virtual void sem() override {
        
    }

private:
    std::string id;
};

#endif