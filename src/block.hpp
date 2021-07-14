#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include <vector>
#include "ast.hpp"
#include "type.hpp"
#include "enums.hpp"
#include "function_type.hpp"

template <class T>
class Block : public AST {
public:

  Block<T>(BlockType block_type) : block_type(block_type) {}
  
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

  virtual Type* infer() override {
    Type* block_type = nullptr;

    //TODO: Do all cases
    switch (this->block_type) {
      case BlockType::Par: {
        if(list.size() == 0) {
          std::cerr << "Parameter list is empty.\n";
          exit(1); //TODO: Error handling
        }
        else {
          block_type = list[0]->infer();
            for(auto element_it = ++this->list.begin(); element_it != this->list.end(); element_it++) {
              if(*element_it != nullptr){
                block_type = new FunctionType(block_type, (*element_it)->infer());
              }
              else {
                std::cerr << "Nullptr in block list.\n";
                exit(1); //TODO: Error handling
              }
          }
        }
        break;
      }
      default:
        std::cerr << "Unknown block type\n"; //TODO: Error Handling.
        exit(1);
        break;
    }

    return block_type;
  }

  virtual void sem() override {
  }

private:
    std::vector<T*> list;
    BlockType block_type;
};

#endif