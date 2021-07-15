#include "symbol_table.hpp"
#include "function_type.hpp"
#include "type.hpp"
#include "enums.hpp"
#include "expr.hpp"
#include "par.hpp"
#include "def.hpp"
#include "ast.hpp"

void SymbolTable::scope_open() {
    this->current_scope = new Scope(this->current_scope, nullptr, 
        this->current_scope != nullptr ? this->current_scope->get_nesting_level() + 1 : 1, false);
}

void SymbolTable::scope_close() {
    auto current_scope = this->current_scope;

    if(this->current_scope == nullptr) {
        std::cerr << "Can't close null Scope\n";
        exit(1); //TODO: Error Handling
    }

    for(auto entry = current_scope->get_entries(); entry != nullptr; entry = entry->get_next_in_scope()){
        hashtable[entry->get_hash_value()] = entry->get_next_hash();
        delete entry;
    }

    this->current_scope = current_scope->get_parent();

    delete current_scope;
}

void SymbolTable::scope_hide(Scope* scope, bool flag) {
    if(scope == nullptr)
        exit(1); //TODO: Error Handling

    scope->set_is_hidden(flag);
}

void SymbolTable::scope_hide(bool flag) {
    if(this->current_scope == nullptr)
        exit(1); //TODO: Error Handling

    this->current_scope->set_is_hidden(flag);
}

void SymbolTable::insert_entry(SymbolEntry* entry){
    //Check if entry already in table
    for(auto e = this->current_scope->get_entries(); e != nullptr; e = e->get_next_in_scope()){
        if(e->get_id() == entry->get_id()){
            std::cerr << "Identifier already exists in scope: " << e->get_id();
            exit(1); //TODO: Already exists error handling
        }
    }

    //Add entry to table
    unsigned int hash_value = PJW_hash(entry->get_id()) % hashtable_size;
    entry->set_hash_value(hash_value);

    entry->set_nesting_level(this->current_scope->get_nesting_level());
    entry->set_scope(this->current_scope);

    entry->set_next_hash(this->hashtable[hash_value]);
    this->hashtable[hash_value] = entry;     //Set current entry as first with this hash value so that its id is the first to be found on lookup from now on.
    entry->set_next_in_scope(this->current_scope->get_entries());
    this->current_scope->set_entries(entry);     //Set current entry as first with this scope so that its id is the first to be found on lookup from now on.

}

SymbolEntry* SymbolTable::lookup_entry(std::string id, LookupType lookup_type) {
    unsigned int hash_value = PJW_hash(id) % hashtable_size;
    SymbolEntry* entry = hashtable[hash_value];

    switch(lookup_type) {
        case LookupType::LOOKUP_CURRENT_SCOPE:
            while (entry != nullptr && entry->get_nesting_level() == this->current_scope->get_nesting_level()) {
                if(entry->get_id() == id)
                    return entry;
                else
                    entry = entry->get_next_hash();
            }
            break;
        case LookupType::LOOKUP_ALL_SCOPES:
            while (entry != nullptr) {
                if(entry->get_id() == id && !entry->get_scope()->get_hidden())
                    return entry;
                else
                    entry = entry->get_next_hash();
            }           
            break;
    }

    //TODO: Error if unknown identifier.
    std::cerr << "Unkown identifier: " << id << "\n";
    exit(1);
    return nullptr;
}

typedef unsigned long int HashType;
unsigned int SymbolTable::PJW_hash(std::string id) {
    /*
     *  P.J. Weinberger's hashing function. See also:
     *  Aho A.V., Sethi R. & Ullman J.D, "Compilers: Principles,
     *  Techniques and Tools", Addison Wesley, 1986, pp. 433-437.
     */

    const char* key = id.c_str(); 
    const HashType PJW_OVERFLOW =
        (((HashType) 0xf) << (8 * sizeof(HashType) - 4));
    const int PJW_SHIFT = (8 * (sizeof(HashType) - 1));
    
    HashType h, g;
    
    for (h = 0; *key != '\0'; key++) {
        h = (h << 4) + (*key);
        if ((g = h & PJW_OVERFLOW) != 0) {
            h ^= g >> PJW_SHIFT;
            h ^= g;
        }
    }
    return h;
}

//TODO: Fix let thrice f x = f (f (f (x+1)))
//TODO: Fix let twice f x y = f (f (x+1) y) (y+1)
void SymbolTable::unify() {
    bool matched_rule;

    while(!this->contraints.empty()) {
        matched_rule = false;

        Constraint constraint = this->contraints[this->contraints.size()-1]; 
        this->contraints.pop_back();

        Type* t1 = constraint.get_t1();
        Type* t2 = constraint.get_t2();

        t1 = this->find_substitute(t1);
        t2 = this->find_substitute(t2);

        //Check that they are not functions
        if(t1->get_tag() != TypeTag::Unknown && t2->get_tag() != TypeTag::Unknown && (t1->get_tag() == t2->get_tag()) && (t1->get_tag() != TypeTag::Function)){
            matched_rule = true;
        }

        if(!matched_rule && (t1->get_tag() == TypeTag::Unknown && !t2->contains(t1))) {
            matched_rule = true;
            this->substitute(t1, t2);
            this->bind(t1, t2);
        }

        if(!matched_rule && (t2->get_tag() == TypeTag::Unknown && !t1->contains(t2))) {
            matched_rule = true;
            this->substitute(t2, t1);
            this->bind(t2, t1);
        }

        if(!matched_rule && ((t1->get_tag() == TypeTag::Function) && (t2->get_tag() == TypeTag::Function))) {
            matched_rule = true;
            FunctionType* t1_func = dynamic_cast<FunctionType*>(t1);
            FunctionType* t2_func = dynamic_cast<FunctionType*>(t2);

            Type* from_type_t1 = t1_func->get_from_type();
            Type* to_type_t1 = t1_func->get_to_type();

            Type* from_type_t2 = t2_func->get_from_type();
            Type* to_type_t2 = t2_func->get_to_type();

            this->add_constraint(from_type_t1, from_type_t2);
            this->add_constraint(to_type_t1, to_type_t2);
        }

        if(!matched_rule){
            std::cerr << "Failed to unify : " << *t1 << "and " << *t2 << '\n'; 
            exit(1);
        }
    }

    //All contraints unified now set inferred values to all bindings. (type_variable, type)
    for(auto bound_pair = this->bound_types.rbegin(); bound_pair != this->bound_types.rend(); bound_pair++){
        //TODO: Implement all typetags
        switch (bound_pair->second->get_tag()) {
            case TypeTag::Function: {
                FunctionType* t2 = dynamic_cast<FunctionType*>(bound_pair->second);

                AST* parent_t1 = bound_pair->first->get_parent();
                Type* new_type = new FunctionType(new Type(t2->get_from_type()->get_tag(), bound_pair->first->get_parent()), new Type(t2->get_to_type()->get_tag(), bound_pair->first->get_parent()), bound_pair->first->get_parent());
                delete bound_pair->first;

                switch (parent_t1->get_node_type()) {
                    case NodeType::Expr: {
                        Expr* parent_node = dynamic_cast<Expr*>(parent_t1);
                        parent_node->set_type(new_type);
                        break;
                    }
                    case NodeType::Par: {
                        Par* parent_node = dynamic_cast<Par*>(parent_t1);
                        parent_node->set_type(new_type);
                        break;
                    }
                    case NodeType::Def: {
                        Def* parent_node = dynamic_cast<Def*>(parent_t1);
                        parent_node->set_type(new_type);
                        break;
                    }
                    default:
                        std::cerr << "Uknown node type\n";
                        exit(1);
                        break;
                }
                break;
            }
            default:
                bound_pair->first->set_tag(bound_pair->second->get_tag());
                break;
        }
    }
}

void SymbolTable::substitute(Type* type_variable, Type* type) {
    this->substitutions.insert({type_variable, type});
}


Type* SymbolTable::find_substitute(Type* type) {
    while (this->substitutions.find(type) != this->substitutions.end()) {
        type = this->substitutions.find(type)->second;
    }

    return type;
}

//Substitute every instance of type_variable in constraints with type.
// void SymbolTable::substitute(Type* type_variable, Type* type) {
    // for(auto constraint_it = this->contraints.begin(); constraint_it != this->contraints.end(); constraint_it++) {
    //     switch(constraint_it->get_t1()->get_tag()) {
    //         //TODO: Propably wont work because it replaces types in the function type with other types with different parent
    //         case TypeTag::Function:{
    //             constraint_substitute(type_variable, type, constraint_it->get_t1());
    //             break;
    //         }
    //         default:
    //             if(constraint_it->get_t1() == type_variable)
    //                 constraint_it->set_t1(type);
    //             break;
    //     }
    //     switch(constraint_it->get_t2()->get_tag()) {
    //         //TODO: Propably wont work because it replaces types in the function type with other types with different parent
    //         case TypeTag::Function:{
    //             constraint_substitute(type_variable, type, constraint_it->get_t2());
    //             break;
    //         }
    //         default:
    //             if(constraint_it->get_t2() == type_variable)
    //                 constraint_it->set_t2(type);
    //             break;
    //     }
    // }
// }

//TODO: Implement non type tags
// void SymbolTable::constraint_substitute(Type* type_variable, Type* type, Type* constraint_type) {
//     switch (constraint_type->get_tag()) {
//         //TODO: Propably wont work because it replaces types in the function type with other types with different parent
//         case TypeTag::Function:{
//             FunctionType* func_constraint = dynamic_cast<FunctionType*>(constraint_type);
//             if(func_constraint->get_to_type() == type_variable) {
//                 func_constraint->get_to_type()->set_tag(type->get_tag());
//             }
//             constraint_substitute(type_variable, type, func_constraint->get_from_type());
//             break;
//         }
//         default:
//             std::cerr << "Substitution is not a function\n";
//             break;
//     }
// }

void SymbolTable::bind(Type* type_variable, Type* type) {
    //If t1->t2 and now we bind t2->t3 then make sure that you make t1->t3 so that when t3 gets a value both t2 and t1 copy it.
    for(auto bound_pair = this->bound_types.begin(); bound_pair != this->bound_types.end(); bound_pair++){
        if(bound_pair->second == type_variable)
            bound_pair->second = type;
    }

    //Add new binding type_variable->type.
    bound_types.push_back(std::pair<Type*, Type*>(type_variable, type));
}