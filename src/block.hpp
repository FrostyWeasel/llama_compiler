#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include <vector>
#include "ast.hpp"

template <class T>
class Block : public AST{
public:
  virtual void print(std::ostream &out) const override {}
  virtual void append(T element) {}
  virtual void insert(std::vector::iterator it, T element) {}

private:
    std::vector<T> list;
};

#endif