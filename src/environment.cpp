// #include "environment.hpp"
// #include "constraint.hpp"
// #include "function_type.hpp"

// //TODO: Function of the inference system:
/* 
    1.Simple constants have a 'named'(aka not uknown) type ex. int, string...
    2.For identifiers: 1.check that the id is in scope, 2. its type is the type in the symbol table
    3.Function: add parameter and parameter type(type known ex x:int) or type variable(type unkwown)
        to the st, infer the functions expr(aka body)

    4.generate type variables(derived from type) and place type variables in st (they have an unknown tag and an autoincrementing unique id)
    4.OR just use the pointer value of the Type objects as the unique identifier of the type variables.

    5.make a substitution function (type variables -> types or other type variables) (where type variable == Uknown and type is any other typetag)
        if is type then do not substitute
        if is type variable then substitute
        if is function type the sumbstitute(from_type) and suvstitute(to_type)

    6.unify:
        1.if t1 and t2 known types(known typetag) and the same(same typetag) remove contraint
        2.if t1 is a type variable(unkwown typetag) then bind all t1 variables to t2 (replace all Type* t1 in contraints list with Type* t2)
        3.if t2 is a type variable the bind all t2 variables to t1
        4.if t1 and t2 are function types(t1: t11->t12, t2: t21->t22) add contraints t11=t21, t12->t22
*/

// void Environment::unify() {
    // bool matched_rule;

    // while(!this->contraints.empty()) {
    //     matched_rule = false;

    //     Constraint constraint = this->contraints[this->contraints.size()-1]; 
    //     this->contraints.pop_back();

//         if((!constraint.get_t1()->is_function() && !constraint.get_t2()->is_function()) && (constraint.get_t1()->get_tag() == constraint.get_t1()->get_tag())) {
//             matched_rule = true;
//         }

//         if(!matched_rule && (!constraint.get_t1()->is_function() && constraint.get_t2()->is_function())) {
//             FunctionType* t2 = dynamic_cast<FunctionType*>(constraint.get_t2());
//             if(!t2->contains(constraint.get_t1())) {
//                 matched_rule = true;
//             }
//         }

//         if(!matched_rule && 0) {

//         }

//         if(!matched_rule && 0) {

//         }

//         if(!matched_rule && 0) {

//         }
//     }
// }