#ifndef __ID_HPP__
#define __ID_HPP__

#include <iostream>
#include <string>
#include "expr.hpp"
#include "type.hpp"
#include "enums.hpp"
#include "includes.hpp"

//TODO: Search ST for type
class ID : public Expr{
public:
    ID(std::string* id): id(*id) {}

    virtual void print(std::ostream& out) const override{
        out << "ID(" << id << ") ";
    }

    std::string get_id() { return id; }

private:
    std::string id;
    
};

#endif