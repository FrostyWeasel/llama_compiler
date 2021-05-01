#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

// enum class BoolType     { True = true, False = false };
enum class OpType       { Plus, Minus, Times, Divide, Equals, NotEquals, LessThan, GreaterThan, LessOrEqualThan, GreaterOrEqualThan, NatEquals, NatNotEquals, And, Or, Concat, Assign, Dereference, Not, Modulo };
enum class TypeTag      { Unit, Int, Char, Bool, Unkown };
enum class LetType      { Rec, NoRec };
enum class DefType      { Mutable, NonMutable };

#endif