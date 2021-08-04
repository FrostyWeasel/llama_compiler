#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include "ast.hpp"
#include "enums.hpp"
#include "type_variable.hpp"
#include "error_handler.hpp"
#include "symbol_table.hpp"
#include "semantic_analyzer.hpp"
#include <iostream>
#include <vector>
#include <memory>

template <class T>
class Block : public AST {
public:

  Block<T>(BlockType block_type) : block_type(block_type) {}
  
  virtual ~Block<T>() {
    for(auto element: list)
      delete element;
  }

  virtual void print(std::ostream &out) const override{
    unsigned int i = 0;

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
      case BlockType::TDef:
        for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
          (*element_it)->print(out);
        }
        break;
      case BlockType::Clause:
        for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
          (*element_it)->print(out);
        }
        break;
      case BlockType::Constructor:
        for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
          (*element_it)->print(out);
        }
        break;
      case BlockType::Definition:
        for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
          (*element_it)->print(out);
          out << "\n";
        }
        break;
      default:
        error_handler->print_error("Uknown block type\n", ErrorType::Internal);
        break;
    }
  }

  virtual void append(T* element) { list.push_back(element); }
  virtual void insert(typename std::vector<T*>::const_iterator it, T* element) { list.insert(it, element); }
  virtual const typename std::vector<T*>::const_iterator begin() const { return list.cbegin(); }

  virtual unsigned int block_size() { return list.size(); }

  virtual void add_to_symbol_table() {
    for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
      if(*element_it != nullptr){
        (*element_it)->add_to_symbol_table();
      }
      else {
        error_handler->print_error("Nullptr in block list.\n", ErrorType::Internal);
      }
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
                error_handler->print_error("Nullptr in block list.\n", ErrorType::Internal);
              }
            }
            break;
          case BlockType::TDef:
            for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
              if(*element_it != nullptr){
                (*element_it)->allocate();
              }
              else {
                error_handler->print_error("Nullptr in block list.\n", ErrorType::Internal);
              }
            }
            break;
      default:
          error_handler->print_error("Attempting to allocate non definitions.\n", ErrorType::Internal);
      break;
    }
  }

  virtual std::shared_ptr<TypeVariable> infer() override {
    std::shared_ptr<TypeVariable> block_type = nullptr;

    switch (this->block_type) {
      case BlockType::Par:
        if(this->list.size() == 0) {
          error_handler->print_error("Parameter list is empty.\n", ErrorType::Internal);
        }
        else {
          block_type = list[0]->infer();
            for(auto element_it = ++this->list.begin(); element_it != this->list.end(); element_it++) {
              if(*element_it != nullptr){
                std::shared_ptr<TypeVariable> new_type = (*element_it)->infer();
                block_type = std::make_shared<TypeVariable>(TypeTag::Function, block_type, new_type, FunctionTypeTag::Curry);
                
                AST::type_variable_owners->insert({ block_type->get_id(), this });
              }
              else {
                error_handler->print_error("Nullptr in block list.\n", ErrorType::Internal);
              }
          }
        }
        break;

      case BlockType::Expr:
        if(this->list.size() == 0) {
          error_handler->print_error("Expression list is empty.\n", ErrorType::Internal);
        }
        else {
          block_type = list[0]->infer();
            for(auto element_it = ++this->list.begin(); element_it != this->list.end(); element_it++) {
              if(*element_it != nullptr){
                std::shared_ptr<TypeVariable> new_type = (*element_it)->infer();
                block_type = std::make_shared<TypeVariable>(TypeTag::Function, block_type, new_type, FunctionTypeTag::Curry);

                AST::type_variable_owners->insert({ block_type->get_id(), this });
              }
              else {
                error_handler->print_error("Nullptr in block list.\n", ErrorType::Internal);
              }
          }
        }
        break;

      case BlockType::ExprComma:
          for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
            if(*element_it != nullptr){
              std::shared_ptr<TypeVariable> new_type = (*element_it)->infer();
              auto int_type = std::make_shared<TypeVariable>(TypeTag::Int);
              st->add_constraint(new_type, int_type, this->lineno);
              
              AST::type_variable_owners->insert({ int_type->get_id(), this });
            }
            else {
              error_handler->print_error("Nullptr in block list.\n", ErrorType::Internal);
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