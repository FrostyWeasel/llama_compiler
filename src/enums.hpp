#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

enum class OpType       { Plus, Minus, Times, Divide, Equals, NotEquals, LessThan, GreaterThan, LessOrEqualThan, GreaterOrEqualThan, NatEquals, NatNotEquals, And, Or, Concat, Assign, Dereference, Not, Modulo };
enum class TypeTag      { Unit, Int, Char, Bool, Unknown, Array, Function, Reference };
enum class LetType      { Rec, NoRec };
enum class DefType      { Mutable, NonMutable };


/* Τύποι εγγραφών του πίνακα συμβόλων */
enum class EntryType    {   ENTRY_VARIABLE,                       /* Μεταβλητές                 */
                            ENTRY_CONSTANT,                       /* Σταθερές                   */
                            ENTRY_FUNCTION,                       /* Συναρτήσεις                */
                            ENTRY_PARAMETER,                      /* Παράμετροι συναρτήσεων     */
                            // ENTRY_TYPE,                        /* User defined Types         */
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
                            
                        }


#endif