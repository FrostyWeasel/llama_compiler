#include "ast.hpp"
#include "function_entry.hpp"
#include "type_variable.hpp"
#include "enums.hpp"
#include "semantic_analyzer.hpp"
#include <iostream>

SymbolTable* AST::st = new SymbolTable(20000);
SemanticAnalyzer* AST::sa = new SemanticAnalyzer();

void AST::close_library_function_scope() {
    st->scope_close();
}

void AST::add_library_functions() {
    std::shared_ptr<TypeVariable> from_type = nullptr;
    std::shared_ptr<TypeVariable> to_type = nullptr;

    st->scope_open();

    from_type = std::make_shared<TypeVariable>(TypeTag::Int);
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_int", EntryType::ENTRY_FUNCTION, from_type, to_type));
   
    //Print Functions
    from_type = std::make_shared<TypeVariable>(TypeTag::Bool);
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_bool", EntryType::ENTRY_FUNCTION, from_type, to_type));

    from_type = std::make_shared<TypeVariable>(TypeTag::Char);
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_char", EntryType::ENTRY_FUNCTION, from_type, to_type));

    // from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    // to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    // st->insert_entry(new FunctionEntry("print_float", EntryType::ENTRY_FUNCTION, from_type, to_type));

    from_type = std::make_shared<TypeVariable>(TypeTag::Array, 
        std::make_shared<TypeVariable>(TypeTag::Char));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_string", EntryType::ENTRY_FUNCTION, from_type, to_type));

    //Read Functions
    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("read_int", EntryType::ENTRY_FUNCTION, from_type, to_type));

    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Bool);
    st->insert_entry(new FunctionEntry("read_bool", EntryType::ENTRY_FUNCTION, from_type, to_type));

    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Char);
    st->insert_entry(new FunctionEntry("read_char", EntryType::ENTRY_FUNCTION, from_type, to_type));

    // from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    // to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    // st->insert_entry(new FunctionEntry("read_float", EntryType::ENTRY_FUNCTION, from_type, to_type));

    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Array, 
        std::make_shared<TypeVariable>(TypeTag::Char));
    st->insert_entry(new FunctionEntry("read_string", EntryType::ENTRY_FUNCTION, from_type, to_type));

    from_type = std::make_shared<TypeVariable>(TypeTag::Reference, 
        std::make_shared<TypeVariable>(TypeTag::Int));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("incr", EntryType::ENTRY_FUNCTION, from_type, to_type));

    from_type = std::make_shared<TypeVariable>(TypeTag::Reference, 
        std::make_shared<TypeVariable>(TypeTag::Int));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("decr", EntryType::ENTRY_FUNCTION, from_type, to_type));

    from_type = std::make_shared<TypeVariable>(TypeTag::Char);
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("int_of_char", EntryType::ENTRY_FUNCTION, from_type, to_type));

    from_type = std::make_shared<TypeVariable>(TypeTag::Int);
    to_type = std::make_shared<TypeVariable>(TypeTag::Char);
    st->insert_entry(new FunctionEntry("char_of_int", EntryType::ENTRY_FUNCTION, from_type, to_type));

    from_type = std::make_shared<TypeVariable>(TypeTag::Array, 
        std::make_shared<TypeVariable>(TypeTag::Char));
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("strlen", EntryType::ENTRY_FUNCTION, from_type, to_type));

    from_type = std::make_shared<TypeVariable>(TypeTag::Function, 
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)),
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)));
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("strcmp", EntryType::ENTRY_FUNCTION, from_type, to_type));

    from_type = std::make_shared<TypeVariable>(TypeTag::Function, 
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)),
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("strcpy", EntryType::ENTRY_FUNCTION, from_type, to_type));

    from_type = std::make_shared<TypeVariable>(TypeTag::Function, 
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)),
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("strcat", EntryType::ENTRY_FUNCTION, from_type, to_type));
    
}