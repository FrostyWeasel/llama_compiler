#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include "ast.hpp"

class Expr : public AST{
  virtual void print(std::ostream &out) const override {  }
};

#endif