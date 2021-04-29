#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include "includes.hpp"
class AST{
public:
    virtual ~AST() {}
    virtual void print(std::ostream& out) const = 0;
};

inline std::ostream& operator<<(std::ostream& out, const AST& ast){
    ast.print(out);
    return out;
}

#endif