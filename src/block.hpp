#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include <vector>
#include "ast.hpp"

template <class T>
class Block : public AST{
public:public:
  virtual void print(std::ostream &out) const override {}
  virtual void append(T* element) {}
  virtual void insert(typename std::vector<T>::iterator it, T* element) {}
  virtual typename std::vector<T>::iterator begin() { return list.begin(); }

private:
    std::vector<T> list;
};

#endif