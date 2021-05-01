#ifndef __DIM_HPP__
#define __DIM_HPP__

#include "expr.hpp"
#include "includes.hpp"


class Dim : public Expr{
public:
    Dim(std::string* id): id(*id), dimension(1) {}
    Dim(std::string* id, int dimension): id(*id), dimension(dimension) {}

    virtual void print(std::ostream &out) const override {
        out << "Dim(";
        out << "Id: " << id << ", Dimension: " << dimension << ") ";
    }


private:
    std::string id;
    int dimension;

};

#endif