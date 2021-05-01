#ifndef __PAR_HPP__
#define __PAR_HPP__

#include "ast.hpp"
#include "includes.hpp"

class Par : public AST{
public:
    Par(std::string* id): id(*id) {}
    Par(std::string* id, Type* type): id(*id), type(type) {}

    virtual void print(std::ostream &out) const override { 
        out << "Par(";
        out << "Id: " << id << " ";
        out << "Type: ";
        if(type != nullptr)
            type->print(out);
        else
            out << "null ";
        out << ") ";
    }

private:
    std::string id;
    Type* type;

};

#endif