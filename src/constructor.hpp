#ifndef __CONSTRUCTOR_HPP__
#define __CONSTRUCTOR_HPP__

#include "ast.hpp"
#include "block.hpp"
#include <string>
#include <memory>

class TypeVariable;
class TDef;
class TypeEntry;
class ConstructorEntry;

class Constructor : public AST {
public:
    Constructor(std::string* id);
    Constructor(std::string* id, std::vector<std::shared_ptr<TypeVariable>>* type_list);

    ~Constructor();

    virtual void print(std::ostream& out) const override;

    virtual void add_to_symbol_table() override ;
    void add_to_symbol_table(TypeEntry* owner_type);

    virtual void allocate() override ;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

    virtual std::string get_id() override { return this->id; }

    void set_type(std::shared_ptr<TypeVariable> type_constructed) { this->type_constructed = type_constructed; }
    std::shared_ptr<TypeVariable> get_type() { return this->type_constructed; }

    ConstructorEntry* get_entry() { return this->entry; }

    inline llvm::Function* get_function_declaration() { return this->constructor_structural_cmp_function; }

    inline unsigned int get_tag() { return this->count; }

private:
    std::string id;
    std::vector<std::shared_ptr<TypeVariable>>* type_list;

    std::shared_ptr<TypeVariable> type_constructed;

    //count is used to uniquely identify a constructor
    unsigned int count;
    static unsigned int counter;

    llvm::Function* constructor_structural_cmp_function; 

    //The entry in the ST corresponding to this definition 
    //* Do not delete this it is owned by the ST.
    ConstructorEntry* entry; 
};

#endif