#ifndef __DEF_HPP__
#define __DEF_HPP__

#include <iostream>
#include <string>
#include "ast.hpp"
#include "includes.hpp"

//TODO: Abstract Symbol table entry
class Def : public AST{
public:    
    Def() {}
    Def(Type* type): type(type) {}

    virtual ~Def() {
	std::cout << "Def deleted\n";
        delete type;
    }

protected:
    Type* type;
};

#endif