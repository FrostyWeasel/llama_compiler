#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include <vector>
#include "ast.hpp"

template <class T>
class Block : public AST{
public:

  Block<T>() {}
  
  virtual ~Block<T>() {
    for(auto element: list)
      delete element;
  }

  virtual void print(std::ostream &out) const override{
    out << "Block(";
    for(T* element: list){
      if(element != nullptr)
        element->print(out);
    }
    out << ") ";
  }

  virtual void append(T* element) { list.push_back(element); }
  virtual void insert(typename std::vector<T*>::const_iterator it, T* element) { list.insert(it, element); }
  virtual const typename std::vector<T*>::const_iterator begin() const { return list.cbegin(); }

  virtual void sem() override {
    for(T* element: list) {
      if(element != nullptr)
        element->sem();
    }
  }

private:
    std::vector<T*> list;
};

#endif