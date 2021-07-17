#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

enum class OpType           { Plus, Minus, Times, Divide, Equals, NotEquals, LessThan, GreaterThan, LessOrEqualThan, GreaterOrEqualThan, NatEquals, NatNotEquals, And, Or, Concat, Assign, Dereference, Not, Modulo };
enum class TypeTag          { Unit, Int, Char, Bool, Unknown, Array, Function, Reference };
enum class TypeVariableTag  { Free, Bound };
enum class LetType          { Rec, NoRec };
enum class DefType          { Mutable, NonMutable };


/* Τύποι εγγραφών του πίνακα συμβόλων */
enum class EntryType    {   ENTRY_VARIABLE,                       /* Μεταβλητές                 */
                            ENTRY_CONSTANT,                       /* Σταθερές                   */
                            ENTRY_FUNCTION,                       /* Συναρτήσεις                */
                            ENTRY_PARAMETER,                      /* Παράμετροι συναρτήσεων     */
                            ENTRY_IDENTIFIER
                        };

/* Τύπος αναζήτησης στον πίνακα συμβόλων */
enum class LookupType   {
                            LOOKUP_CURRENT_SCOPE,
                            LOOKUP_ALL_SCOPES
                        };

enum class BlockType    {
                            LetDef,
                            Def,
                            Par,
                            Expr,
                            ExprComma
                        };

enum class NodeType     {
                            Par,
                            Expr,
                            Def
                        };   

enum class DimType      {
                            Exact, //Array has exactly this dimension
                            AtLeast //Array has at least this dimension
                        };

#endif