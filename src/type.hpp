#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include "ast.hpp"

class Type : public AST{
  virtual void print(std::ostream &out) const override {  }
};

#endif