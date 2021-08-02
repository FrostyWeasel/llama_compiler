#ifndef __SEMANTIC_ANALYZER_HPP__
#define __SEMANTIC_ANALYZER_HPP__

#include "type_variable.hpp"
#include <memory>
#include <vector>

class TypeVariable;

class SemanticAnalyzer {
public:
    SemanticAnalyzer() { }
    ~SemanticAnalyzer() { }

    //t1 same type as t2
    bool is_same_type(std::shared_ptr<TypeVariable> t1, std::shared_ptr<TypeVariable> t2);

    //t1 same type with at least one type in t2 list
    bool is_same_type(std::shared_ptr<TypeVariable> t1, std::vector<std::shared_ptr<TypeVariable>> t2_list);

    //t1 not same type as t2
    bool is_not_same_type(std::shared_ptr<TypeVariable> t1, std::shared_ptr<TypeVariable> t2);

    //t1 not same type with any type in t2 list
    bool is_not_same_type(std::shared_ptr<TypeVariable> t1, std::vector<std::shared_ptr<TypeVariable>> t2_list);

    //t1 has same tag (Function, Array, Reference, int etc.) as t2
    bool is_same_tag(std::shared_ptr<TypeVariable> t1, TypeTag tag);

    //t1 has same tag (Function, Array, Reference, int etc.) with at least one type in t2 list
    bool is_same_tag(std::shared_ptr<TypeVariable> t1, std::vector<TypeTag> tag_list);

    //t1 has same tag (Function, Array, Reference, int, etc.) as t2
    bool is_not_same_tag(std::shared_ptr<TypeVariable> t1, TypeTag tag);

    //t1 not same type class (Function, Array, Reference, int, etc.) with any type in t2 list
    bool is_not_same_tag(std::shared_ptr<TypeVariable> t1, std::vector<TypeTag> tag_list);

};

#endif
