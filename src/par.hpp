#ifndef __PAR_HPP__
#define __PAR_HPP__

#include "ast.hpp"

class Par : public AST{
  virtual void print(std::ostream &out) const override {  }
};

#endif