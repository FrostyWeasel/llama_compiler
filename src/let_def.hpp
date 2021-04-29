#ifndef __LETDEF_HPP__
#define __LETDEF_HPP__

#include "ast.hpp"
#include "includes.hpp"

class LetDef : public AST{
public:    
    LetDef(Block<Def>* def, LetType type) {}
    virtual void print(std::ostream &out) const override {}
};

#endif
