#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include <iostream>
#include <vector>
#include "ast.hpp"
#include "enums.hpp"
#include "type_variable.hpp"

// class FunctionType;

template <class T>
class Block : public AST {
public:

  Block<T>(BlockType block_type) : block_type(block_type) {}
  
  virtual ~Block<T>() {
    for(auto element: list)
      delete element;
  }

  virtual void print(std::ostream &out) const override{
    int i = 0;

    switch (this->block_type) {
      case BlockType::Par:
        for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
          (*element_it)->print(out);
          // if(i < list.size() - 1)
          //   out << "";
          i++;
        }
        break;
      case BlockType::Expr:
        for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
          (*element_it)->print(out);
          if(i < list.size() - 1)
            out << " ";
          i++;
        }
        break;
      case BlockType::ExprComma:
        for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
          (*element_it)->print(out);
          if(i < list.size() - 1)
            out << ", ";
          i++;
        }
        break;
      case BlockType::Def:
        for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
          (*element_it)->print(out);
        }
        break;
      case BlockType::LetDef:
        for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
          (*element_it)->print(out);
          out << "\n";
        }
        break;
      default:
        std::cerr << "Uknown block type\n";
        exit(1); //TODO: Error handling.
        break;
    }
  }

  virtual void append(T* element) { list.push_back(element); }
  virtual void insert(typename std::vector<T*>::const_iterator it, T* element) { list.insert(it, element); }
  virtual const typename std::vector<T*>::const_iterator begin() const { return list.cbegin(); }

  virtual unsigned int block_size() { return list.size(); }

  virtual void add_to_symbol_table() {
    switch (this->block_type) {
          case BlockType::Def:
            for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
              if(*element_it != nullptr){
                (*element_it)->add_to_symbol_table();
              }
              else {
                std::cerr << "Nullptr in block list.\n";
                exit(1); //TODO: Error handling
              }
            }
            break;

      default:
          std::cerr << "Attempting to add non definitions to symbol table.\n";
          exit(1); //TODO: Error handling
      break;
    }
  }

  virtual void allocate() {
    switch (this->block_type) {
          case BlockType::Def:
            for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
              if(*element_it != nullptr){
                (*element_it)->allocate();
              }
              else {
                std::cerr << "Nullptr in block list.\n";
                exit(1); //TODO: Error handling
              }
            }
            break;

      default:
          std::cerr << "Attempting to allocate non definitions.\n";
          exit(1); //TODO: Error handling
      break;
    }
  }

  virtual std::shared_ptr<TypeVariable> infer() override {
    std::shared_ptr<TypeVariable> block_type = nullptr;

    switch (this->block_type) {
      case BlockType::Par:
        if(this->list.size() == 0) {
          std::cerr << "Parameter list is empty.\n";
          exit(1); //TODO: Error handling
        }
        else {
          block_type = list[0]->infer();
            for(auto element_it = ++this->list.begin(); element_it != this->list.end(); element_it++) {
              if(*element_it != nullptr){
                std::shared_ptr<TypeVariable> new_type = (*element_it)->infer();
                block_type = std::make_shared<TypeVariable>(TypeTag::Function, block_type, new_type, FunctionTypeTag::Curry);
              }
              else {
                std::cerr << "Nullptr in block list.\n";
                exit(1); //TODO: Error handling
              }
          }
        }
        break;

      case BlockType::Expr:
        if(this->list.size() == 0) {
          std::cerr << "Expression list is empty.\n";
          exit(1); //TODO: Error handling
        }
        else {
          block_type = list[0]->infer();
            for(auto element_it = ++this->list.begin(); element_it != this->list.end(); element_it++) {
              if(*element_it != nullptr){
                std::shared_ptr<TypeVariable> new_type = (*element_it)->infer();
                block_type = std::make_shared<TypeVariable>(TypeTag::Function, block_type, new_type, FunctionTypeTag::Curry);
              }
              else {
                std::cerr << "Nullptr in block list.\n";
                exit(1); //TODO: Error handling
              }
          }
        }
        break;

      case BlockType::ExprComma:
          for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
            if(*element_it != nullptr){
              std::shared_ptr<TypeVariable> new_type = (*element_it)->infer();
              st->add_constraint(new_type, std::make_shared<TypeVariable>(TypeTag::Int));
            }
            else {
              std::cerr << "Nullptr in block list.\n";
              exit(1); //TODO: Error handling
            }
        }
      break;
      default:
          for(T* element: list) {
            if(element != nullptr)
              element->infer();
          }
        break;
    }

    return block_type;
  }

  virtual void sem() override {
    for(T* element: list) {
      if(element != nullptr)
        element->sem();
    }
  }

  virtual llvm::Value* codegen()  override {
      llvm::Value* block_value = nullptr;

    
      for(T* element: list) {
        if(element != nullptr)
          element->codegen();
      }

      return block_value;
    }

  virtual void make_non_local_variable_stack()  override {

    for(T* element: list) {
      if(element != nullptr)
        element->make_non_local_variable_stack();
    }

  }

  std::vector<T*>& get_list() { return list; }

private:
    std::vector<T*> list;
    BlockType block_type;
};

#endif