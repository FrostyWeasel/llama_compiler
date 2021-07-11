#ifndef __ID_HPP__
#define __ID_HPP__

#include <iostream>
#include <string>
#include "expr.hpp"
#include "type.hpp"
#include "enums.hpp"
#include "includes.hpp"

//TODO: Search ST for type
class Id : public Expr{
public:
    Id(std::string* id): id(*id) {}

    virtual void print(std::ostream& out) const override{
        out << "Id(" << id << ") ";
    }

    std::string get_id() { return id; }

private:
    std::string id;
    
};

#endif