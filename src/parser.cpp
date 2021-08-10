/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./src/parser.y"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include "block.hpp"
#include "constructor.hpp"
#include "pattern.hpp"
#include "clause.hpp"
#include "int_pattern.hpp"
#include "float_pattern.hpp"
#include "char_pattern.hpp"
#include "bool_pattern.hpp"
#include "id_pattern.hpp"
#include "match.hpp"
#include "definition.hpp"
#include "type_def.hpp"
#include "constructor_pattern.hpp"
#include "constructor_call.hpp"
#include "t_def.hpp"
#include "includes.hpp"
#include "lexer.hpp"
#include <memory>
#include <vector>
#include <unistd.h>
#include <cstdio>

std::vector<std::string*> str_to_delete;
constexpr bool debug = false;

std::string compiler_path;
std::string input_filename;

bool intermediate_flag;
bool final_flag;
bool optimizations_flag;

extern FILE* yyin;
extern int yylineno;


#line 113 "./src/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_AND = 3,                      /* "and"  */
  YYSYMBOL_T_ARRAY = 4,                    /* "array"  */
  YYSYMBOL_T_BEGIN = 5,                    /* "begin"  */
  YYSYMBOL_T_BOOL = 6,                     /* "bool"  */
  YYSYMBOL_T_CHAR = 7,                     /* "char"  */
  YYSYMBOL_T_DELETE = 8,                   /* "delete"  */
  YYSYMBOL_T_DIM = 9,                      /* "dim"  */
  YYSYMBOL_T_DO = 10,                      /* "do"  */
  YYSYMBOL_T_DONE = 11,                    /* "done"  */
  YYSYMBOL_T_DOWNTO = 12,                  /* "downto"  */
  YYSYMBOL_T_ELSE = 13,                    /* "else"  */
  YYSYMBOL_T_END = 14,                     /* "end"  */
  YYSYMBOL_T_FALSE = 15,                   /* "false"  */
  YYSYMBOL_T_FOR = 16,                     /* "for"  */
  YYSYMBOL_T_IF = 17,                      /* "if"  */
  YYSYMBOL_T_IN = 18,                      /* "in"  */
  YYSYMBOL_T_INT = 19,                     /* "int"  */
  YYSYMBOL_T_FLOAT = 20,                   /* "float"  */
  YYSYMBOL_T_LET = 21,                     /* "let"  */
  YYSYMBOL_T_MATCH = 22,                   /* "match"  */
  YYSYMBOL_T_MOD = 23,                     /* "mod"  */
  YYSYMBOL_T_MUTABLE = 24,                 /* "mutable"  */
  YYSYMBOL_T_NEW = 25,                     /* "new"  */
  YYSYMBOL_T_NOT = 26,                     /* "not"  */
  YYSYMBOL_T_OF = 27,                      /* "of"  */
  YYSYMBOL_T_REC = 28,                     /* "rec"  */
  YYSYMBOL_T_REF = 29,                     /* "ref"  */
  YYSYMBOL_T_THEN = 30,                    /* "then"  */
  YYSYMBOL_T_TO = 31,                      /* "to"  */
  YYSYMBOL_T_TRUE = 32,                    /* "true"  */
  YYSYMBOL_T_TYPE = 33,                    /* "type"  */
  YYSYMBOL_T_UNIT = 34,                    /* "unit"  */
  YYSYMBOL_T_WHILE = 35,                   /* "while"  */
  YYSYMBOL_T_WITH = 36,                    /* "with"  */
  YYSYMBOL_T_TYPE_ARROW_OP = 37,           /* "->"  */
  YYSYMBOL_T_AND_OP = 38,                  /* "&&"  */
  YYSYMBOL_T_OR_OP = 39,                   /* "||"  */
  YYSYMBOL_T_NOT_EQ_OP = 40,               /* "<>"  */
  YYSYMBOL_T_LESS_THAN_OR_EQ_OP = 41,      /* "<="  */
  YYSYMBOL_T_GREATER_THAN_OR_EQ_OP = 42,   /* ">="  */
  YYSYMBOL_T_NAT_EQ_OP = 43,               /* "=="  */
  YYSYMBOL_T_NAT_NOT_EQ_OP = 44,           /* "!="  */
  YYSYMBOL_T_ASSIGNMENT_OP = 45,           /* ":="  */
  YYSYMBOL_T_PLUS_FLOAT = 46,              /* "+."  */
  YYSYMBOL_T_MINUS_FLOAT = 47,             /* "-."  */
  YYSYMBOL_T_TIMES_FLOAT = 48,             /* "*."  */
  YYSYMBOL_T_DIVIDE_FLOAT = 49,            /* "/."  */
  YYSYMBOL_T_EXPONENTIATE_FLOAT = 50,      /* "**"  */
  YYSYMBOL_T_ID = 51,                      /* T_ID  */
  YYSYMBOL_T_CONSTRUCTOR_ID = 52,          /* T_CONSTRUCTOR_ID  */
  YYSYMBOL_T_CONST_CHAR = 53,              /* T_CONST_CHAR  */
  YYSYMBOL_T_CONST_INT = 54,               /* T_CONST_INT  */
  YYSYMBOL_T_CONST_FLOAT = 55,             /* T_CONST_FLOAT  */
  YYSYMBOL_T_STRING_LITERAL = 56,          /* T_STRING_LITERAL  */
  YYSYMBOL_57_ = 57,                       /* ';'  */
  YYSYMBOL_IF_THEN = 58,                   /* IF_THEN  */
  YYSYMBOL_IF_THEN_ELSE = 59,              /* IF_THEN_ELSE  */
  YYSYMBOL_60_ = 60,                       /* '='  */
  YYSYMBOL_61_ = 61,                       /* '>'  */
  YYSYMBOL_62_ = 62,                       /* '<'  */
  YYSYMBOL_63_ = 63,                       /* '+'  */
  YYSYMBOL_64_ = 64,                       /* '-'  */
  YYSYMBOL_65_ = 65,                       /* '*'  */
  YYSYMBOL_66_ = 66,                       /* '/'  */
  YYSYMBOL_UNOP = 67,                      /* UNOP  */
  YYSYMBOL_68_ = 68,                       /* '!'  */
  YYSYMBOL_69_ = 69,                       /* ':'  */
  YYSYMBOL_70_ = 70,                       /* '['  */
  YYSYMBOL_71_ = 71,                       /* ']'  */
  YYSYMBOL_72_ = 72,                       /* '|'  */
  YYSYMBOL_73_ = 73,                       /* '('  */
  YYSYMBOL_74_ = 74,                       /* ')'  */
  YYSYMBOL_75_ = 75,                       /* ','  */
  YYSYMBOL_YYACCEPT = 76,                  /* $accept  */
  YYSYMBOL_program = 77,                   /* program  */
  YYSYMBOL_definition_list = 78,           /* definition_list  */
  YYSYMBOL_letdef = 79,                    /* letdef  */
  YYSYMBOL_def_list = 80,                  /* def_list  */
  YYSYMBOL_def = 81,                       /* def  */
  YYSYMBOL_typedef = 82,                   /* typedef  */
  YYSYMBOL_tdef_list = 83,                 /* tdef_list  */
  YYSYMBOL_tdef = 84,                      /* tdef  */
  YYSYMBOL_constr_list = 85,               /* constr_list  */
  YYSYMBOL_constr = 86,                    /* constr  */
  YYSYMBOL_par_list = 87,                  /* par_list  */
  YYSYMBOL_par = 88,                       /* par  */
  YYSYMBOL_expr_comma_list = 89,           /* expr_comma_list  */
  YYSYMBOL_expr = 90,                      /* expr  */
  YYSYMBOL_func_expr = 91,                 /* func_expr  */
  YYSYMBOL_func_expr_list = 92,            /* func_expr_list  */
  YYSYMBOL_type_list = 93,                 /* type_list  */
  YYSYMBOL_type = 94,                      /* type  */
  YYSYMBOL_asterisk_list = 95,             /* asterisk_list  */
  YYSYMBOL_clause_list = 96,               /* clause_list  */
  YYSYMBOL_clause = 97,                    /* clause  */
  YYSYMBOL_pattern = 98,                   /* pattern  */
  YYSYMBOL_pattern_high_list = 99,         /* pattern_high_list  */
  YYSYMBOL_pattern_high = 100              /* pattern_high  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1029

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  120
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  238

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   314


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    68,     2,     2,     2,     2,     2,     2,
      73,    74,    65,    63,    75,    64,     2,    66,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    69,    57,
      62,    60,    61,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    70,     2,    71,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    72,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    58,    59,    67
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   182,   182,   206,   207,   208,   212,   213,   217,   218,
     222,   223,   224,   225,   226,   227,   228,   229,   233,   237,
     238,   242,   246,   247,   251,   252,   256,   257,   261,   262,
     266,   267,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   331,   332,   336,   337,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   355,   356,   360,   361,   365,   369,   370,   374,   375,
     379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     389
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"and\"", "\"array\"",
  "\"begin\"", "\"bool\"", "\"char\"", "\"delete\"", "\"dim\"", "\"do\"",
  "\"done\"", "\"downto\"", "\"else\"", "\"end\"", "\"false\"", "\"for\"",
  "\"if\"", "\"in\"", "\"int\"", "\"float\"", "\"let\"", "\"match\"",
  "\"mod\"", "\"mutable\"", "\"new\"", "\"not\"", "\"of\"", "\"rec\"",
  "\"ref\"", "\"then\"", "\"to\"", "\"true\"", "\"type\"", "\"unit\"",
  "\"while\"", "\"with\"", "\"->\"", "\"&&\"", "\"||\"", "\"<>\"",
  "\"<=\"", "\">=\"", "\"==\"", "\"!=\"", "\":=\"", "\"+.\"", "\"-.\"",
  "\"*.\"", "\"/.\"", "\"**\"", "T_ID", "T_CONSTRUCTOR_ID", "T_CONST_CHAR",
  "T_CONST_INT", "T_CONST_FLOAT", "T_STRING_LITERAL", "';'", "IF_THEN",
  "IF_THEN_ELSE", "'='", "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "UNOP",
  "'!'", "':'", "'['", "']'", "'|'", "'('", "')'", "','", "$accept",
  "program", "definition_list", "letdef", "def_list", "def", "typedef",
  "tdef_list", "tdef", "constr_list", "constr", "par_list", "par",
  "expr_comma_list", "expr", "func_expr", "func_expr_list", "type_list",
  "type", "asterisk_list", "clause_list", "clause", "pattern",
  "pattern_high_list", "pattern_high", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,    59,   312,   313,
      61,    62,    60,    43,    45,    42,    47,   314,    33,    58,
      91,    93,   124,    40,    41,    44
};
#endif

#define YYPACT_NINF (-82)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -82,    11,     8,   -82,    10,    -9,   -82,   -82,     6,    -5,
      65,   -82,   -23,   -82,   -19,   -82,   -82,   244,    92,    12,
     -82,    61,    13,    63,    92,   244,    61,   244,   244,     1,
     -82,    40,   244,   244,    92,   244,   -82,   244,   244,   244,
     269,   278,   -82,   -82,   -82,   -82,   244,   244,   278,   183,
      74,   820,   -82,   -21,   -82,   -82,   -82,   -82,   -82,   -82,
      92,   -20,    24,    67,    -5,    75,   -82,    -9,     7,   820,
     686,   -82,   -82,    43,    41,   760,   791,     7,   -82,   333,
     -82,   -82,    33,   -82,   244,   -82,   -82,   -82,   -82,   -82,
     -82,   715,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,    92,    49,   -14,   -82,    92,
     244,    92,   244,    92,   -82,   -82,    92,    34,   -82,   -55,
     -82,   -82,   244,   244,   109,   244,   820,   278,   278,   -82,
     820,    55,   935,   907,   963,   963,   963,   963,   963,   849,
     -18,   -18,    55,    55,    55,   878,   963,   963,   963,   -18,
     -18,    55,    55,    90,   -82,   -32,   -82,     7,   820,    16,
     820,    -2,     7,    13,    52,   244,   597,   642,   -82,   -82,
      73,    76,   -82,   -82,   -82,   -82,   -82,    78,    79,   109,
     -82,    93,   -82,   465,    29,   -82,   102,    70,   -82,   244,
      92,   -82,    92,   820,   244,   244,   244,   -82,   -82,   294,
     -82,   -82,    68,   -10,   244,   -82,   -82,    92,   -82,   820,
       7,     7,   377,   421,   878,   -82,   -82,   -82,   109,   820,
      90,   244,   244,   -82,   509,   553,   -82,   -82
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     4,     5,     0,     0,
       0,     8,     0,    19,    14,     8,    28,     0,     0,     0,
      26,     7,     0,    18,     0,     0,     6,     0,     0,     0,
      84,     0,     0,     0,     0,     0,    83,     0,     0,     0,
      77,    78,    81,    79,    80,    82,     0,     0,     0,     0,
       0,    10,    73,     0,    93,    92,    91,    94,    90,   100,
       0,     0,     0,     0,     0,    24,    22,     0,    15,    30,
       0,    37,    34,     0,     0,     0,     0,    36,    49,     0,
      47,    48,    77,    78,     0,    86,    86,    45,    46,    74,
      76,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    97,     0,
       0,     0,     0,     0,    27,     9,     0,    21,    20,     0,
      39,    35,     0,     0,     0,     0,    30,    32,    33,    75,
      38,    71,    67,    68,    60,    63,    64,    65,    66,    70,
      54,    55,    56,    57,    58,    69,    59,    62,    61,    50,
      51,    52,    53,    98,   101,     0,    95,    96,    11,     0,
      13,     0,    88,     0,    16,     0,     0,    40,   118,   117,
       0,     0,   119,   108,   116,   112,   115,     0,     0,     0,
     103,     0,   106,     0,     0,    87,     0,     0,    29,     0,
      25,    23,     0,    31,     0,     0,     0,   113,   114,   107,
     110,   111,     0,     0,     0,    42,    85,     0,   102,    12,
      89,    17,     0,     0,    41,   109,   120,    72,     0,   105,
      99,     0,     0,   104,     0,     0,    44,    43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -82,   -82,   -82,   135,   124,    -8,   -82,   -82,    77,   -82,
     -28,   -82,    83,    15,   -25,   -15,    62,   -82,    -6,   -82,
     -82,   -81,   -40,   -82,   -57
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    50,    21,    11,     7,    23,    13,   127,
      66,    63,    20,   129,    51,    52,   137,   200,    61,   165,
     213,   190,   191,   209,   192
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      69,    15,    70,    71,   227,    93,   115,    75,    76,   118,
      78,     3,    79,    80,    81,   118,   174,   119,    68,     8,
     175,    87,    88,   119,    91,    85,    86,   118,    77,     4,
     104,   105,   106,    89,     8,   119,   118,    22,     9,   196,
     120,     5,    12,   197,   119,   118,    10,   113,   114,   116,
      24,    25,    72,   119,   117,    73,   125,    14,   199,   136,
     166,    10,   228,    62,    64,    65,    67,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     198,    74,    92,   121,   131,   168,    53,   170,    54,    55,
     216,   132,   126,    84,   175,   106,   173,   176,   177,   163,
     193,    56,    57,   167,   164,   169,    16,   171,    16,   118,
     172,   202,   195,   195,   178,    17,    58,   122,   207,   217,
     214,   208,   210,   211,    18,   218,   123,     6,    19,    26,
      19,   179,   226,    59,   128,   201,   124,   233,   138,   212,
     203,   194,   225,     0,     0,   180,   181,     0,     0,     0,
     182,   183,   184,   185,   186,    60,     0,     0,     0,     0,
       0,     0,   187,   188,   219,     0,     0,     0,     0,   222,
     223,   224,   189,     0,     0,     0,     0,     0,    27,   229,
       0,    28,    29,     0,   220,     0,   221,     0,    30,    31,
      32,     0,     0,     0,     4,    33,   234,   235,    34,    35,
       0,   230,     0,     0,     0,    36,     0,     0,    37,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
      39,     0,     0,     0,    40,    41,    42,    43,    44,    45,
       0,     0,     0,     0,     0,     0,    46,    47,     0,    27,
       0,    48,    28,    29,     0,     0,    49,    90,     0,    30,
      31,    32,     0,     0,     0,     4,    33,     0,     0,    34,
      35,     0,     0,     0,     0,     0,    36,     0,     0,    37,
       0,     0,     0,     0,    30,     0,     0,     0,     0,     0,
      38,    39,     0,    30,     0,    40,    41,    42,    43,    44,
      45,    36,     0,     0,     0,     0,     0,    46,    47,   178,
      36,     0,    48,     0,     0,     0,     0,    49,     0,     0,
      82,    83,    42,    43,    44,    45,   179,     0,     0,    82,
      83,    42,    43,    44,    45,     0,     0,    48,     0,    84,
     180,   181,    49,   135,     0,   182,    48,   184,   185,   186,
       0,    49,     0,     0,     0,     0,    93,   187,   188,     0,
       0,     0,     0,     0,     0,     0,     0,   189,     0,     0,
       0,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,     0,     0,     0,   231,     0,     0,
     107,     0,     0,   108,   109,   110,   111,   112,   113,   114,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,     0,     0,
       0,   232,     0,     0,   107,     0,     0,   108,   109,   110,
     111,   112,   113,   114,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,     0,     0,     0,     0,   215,     0,   107,     0,
       0,   108,   109,   110,   111,   112,   113,   114,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,     0,     0,     0,     0,
     236,     0,   107,     0,     0,   108,   109,   110,   111,   112,
     113,   114,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
       0,     0,     0,     0,   237,     0,   107,     0,     0,   108,
     109,   110,   111,   112,   113,   114,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,     0,     0,     0,     0,     0,   204,
     107,     0,     0,   108,   109,   110,   111,   112,   113,   114,
      93,     0,     0,     0,     0,     0,     0,     0,   205,     0,
       0,     0,     0,     0,     0,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,     0,     0,
       0,     0,     0,     0,   107,   206,     0,   108,   109,   110,
     111,   112,   113,   114,     0,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,     0,     0,     0,     0,     0,     0,     0,
     130,     0,   108,   109,   110,   111,   112,   113,   114,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,     0,    93,     0,
       0,     0,     0,   107,     0,     0,   108,   109,   110,   111,
     112,   113,   114,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,     0,     0,     0,     0,
       0,     0,   107,     0,     0,   108,   109,   110,   111,   112,
     113,   114,     0,    93,     0,     0,     0,     0,     0,   139,
     133,     0,     0,     0,     0,     0,     0,     0,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,     0,     0,     0,    93,     0,     0,   107,     0,     0,
     108,   109,   110,   111,   112,   113,   114,   134,     0,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,     0,    93,     0,     0,     0,     0,   107,     0,
       0,   108,   109,   110,   111,   112,   113,   114,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,     0,    93,     0,     0,     0,     0,   107,     0,     0,
     108,   109,   110,   111,   112,   113,   114,    94,    95,    96,
      97,    98,    99,   100,    -1,   102,   103,   104,   105,   106,
       0,    93,     0,     0,     0,     0,     0,     0,     0,   108,
     109,   110,   111,   112,   113,   114,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,     0,
      93,     0,     0,     0,     0,     0,     0,     0,   108,   109,
     110,   111,   112,   113,   114,    94,     0,    96,    97,    98,
      99,   100,     0,   102,   103,   104,   105,   106,    93,     0,
       0,     0,     0,     0,     0,     0,     0,   108,   109,   110,
     111,   112,   113,   114,     0,    96,    97,    98,    99,   100,
       0,   102,   103,   104,   105,   106,    93,     0,     0,     0,
       0,     0,     0,     0,     0,   108,   109,   110,   111,   112,
     113,   114,     0,    -1,    -1,    -1,    -1,    -1,     0,   102,
     103,   104,   105,   106,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    -1,    -1,    -1,   111,   112,   113,   114
};

static const yytype_int16 yycheck[] =
{
      25,     9,    27,    28,    14,    23,    27,    32,    33,    29,
      35,     0,    37,    38,    39,    29,    71,    37,    24,    24,
      75,    46,    47,    37,    49,    40,    41,    29,    34,    21,
      48,    49,    50,    48,    24,    37,    29,    60,    28,    71,
      60,    33,    51,    75,    37,    29,    51,    65,    66,    70,
      69,    70,    51,    37,    60,    54,    64,    51,    60,    84,
      74,    51,    72,    51,     3,    52,     3,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
      74,    51,    18,    69,    51,   120,     4,   122,     6,     7,
      71,    60,    27,    70,    75,    50,    72,   132,   133,   115,
     135,    19,    20,   119,    65,   121,    51,   123,    51,    29,
     126,    69,   137,   138,    15,    60,    34,    60,    55,    27,
      37,    55,    54,    54,    69,    65,    69,     2,    73,    15,
      73,    32,    74,    51,    67,   173,    63,   228,    86,   189,
     175,   136,   209,    -1,    -1,    46,    47,    -1,    -1,    -1,
      51,    52,    53,    54,    55,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    64,   199,    -1,    -1,    -1,    -1,   204,
     205,   206,    73,    -1,    -1,    -1,    -1,    -1,     5,   214,
      -1,     8,     9,    -1,   200,    -1,   202,    -1,    15,    16,
      17,    -1,    -1,    -1,    21,    22,   231,   232,    25,    26,
      -1,   217,    -1,    -1,    -1,    32,    -1,    -1,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      47,    -1,    -1,    -1,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    -1,     5,
      -1,    68,     8,     9,    -1,    -1,    73,    74,    -1,    15,
      16,    17,    -1,    -1,    -1,    21,    22,    -1,    -1,    25,
      26,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      46,    47,    -1,    15,    -1,    51,    52,    53,    54,    55,
      56,    32,    -1,    -1,    -1,    -1,    -1,    63,    64,    15,
      32,    -1,    68,    -1,    -1,    -1,    -1,    73,    -1,    -1,
      51,    52,    53,    54,    55,    56,    32,    -1,    -1,    51,
      52,    53,    54,    55,    56,    -1,    -1,    68,    -1,    70,
      46,    47,    73,    10,    -1,    51,    68,    53,    54,    55,
      -1,    73,    -1,    -1,    -1,    -1,    23,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    10,    -1,    -1,
      57,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    10,    -1,    -1,    57,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    -1,    -1,    -1,    -1,    11,    -1,    57,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,
      11,    -1,    57,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    -1,    11,    -1,    57,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,    12,
      57,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    13,    -1,    60,    61,    62,
      63,    64,    65,    66,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    60,    61,    62,    63,    64,    65,    66,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    -1,    23,    -1,
      -1,    -1,    -1,    57,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    -1,    23,    -1,    -1,    -1,    -1,    -1,    74,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    23,    -1,    -1,    57,    -1,    -1,
      60,    61,    62,    63,    64,    65,    66,    36,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    -1,    23,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    -1,    23,    -1,    -1,    -1,    -1,    57,    -1,    -1,
      60,    61,    62,    63,    64,    65,    66,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    65,    66,    38,    -1,    40,    41,    42,
      43,    44,    -1,    46,    47,    48,    49,    50,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    -1,    40,    41,    42,    43,    44,
      -1,    46,    47,    48,    49,    50,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    -1,    40,    41,    42,    43,    44,    -1,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    66
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    77,    78,     0,    21,    33,    79,    82,    24,    28,
      51,    81,    51,    84,    51,    81,    51,    60,    69,    73,
      88,    80,    60,    83,    69,    70,    80,     5,     8,     9,
      15,    16,    17,    22,    25,    26,    32,    35,    46,    47,
      51,    52,    53,    54,    55,    56,    63,    64,    68,    73,
      79,    90,    91,     4,     6,     7,    19,    20,    34,    51,
      73,    94,    51,    87,     3,    52,    86,     3,    94,    90,
      90,    90,    51,    54,    51,    90,    90,    94,    90,    90,
      90,    90,    51,    52,    70,    91,    91,    90,    90,    91,
      74,    90,    18,    23,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    57,    60,    61,
      62,    63,    64,    65,    66,    27,    70,    94,    29,    37,
      60,    69,    60,    69,    88,    81,    27,    85,    84,    89,
      14,    51,    60,    30,    36,    10,    90,    92,    92,    74,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    94,    65,    95,    74,    94,    90,    94,
      90,    94,    94,    72,    71,    75,    90,    90,    15,    32,
      46,    47,    51,    52,    53,    54,    55,    63,    64,    73,
      97,    98,   100,    90,    89,    91,    71,    75,    74,    60,
      93,    86,    69,    90,    12,    31,    13,    55,    55,    99,
      54,    54,    98,    96,    37,    11,    71,    27,    65,    90,
      94,    94,    90,    90,    90,   100,    74,    14,    72,    90,
      94,    10,    10,    97,    90,    90,    11,    11
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    76,    77,    78,    78,    78,    79,    79,    80,    80,
      81,    81,    81,    81,    81,    81,    81,    81,    82,    83,
      83,    84,    85,    85,    86,    86,    87,    87,    88,    88,
      89,    89,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    92,    92,    93,    93,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    95,    95,    96,    96,    97,    98,    98,    99,    99,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     4,     3,     0,     3,
       3,     5,     7,     5,     2,     4,     6,     8,     3,     0,
       3,     4,     0,     3,     1,     4,     0,     2,     1,     5,
       0,     3,     3,     3,     2,     3,     2,     2,     3,     3,
       4,     6,     5,     9,     9,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     6,     1,     2,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     0,     2,     0,     2,
       1,     1,     1,     1,     1,     3,     3,     2,     3,     6,
       1,     1,     3,     0,     3,     3,     1,     2,     0,     2,
       2,     2,     1,     2,     2,     1,     1,     1,     1,     1,
       3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: definition_list  */
#line 182 "./src/parser.y"
                    { 
            (yyvsp[0].definition_list)->add_library_functions();
            if(debug) std::cout << "AST: " << *(yyvsp[0].definition_list) << std::endl;
            
            (yyvsp[0].definition_list)->infer();
            (yyvsp[0].definition_list)->unify();
            (yyvsp[0].definition_list)->clear_inference_structures();
            (yyvsp[0].definition_list)->close_all_program_scopes();

            (yyvsp[0].definition_list)->sem();
            (yyvsp[0].definition_list)->bind_to_default_types();
            if(debug) std::cout << "AST: " << *(yyvsp[0].definition_list) << std::endl;
            (yyvsp[0].definition_list)->close_all_program_scopes();

            (yyvsp[0].definition_list)->llvm_compile_and_dump(optimizations_flag, intermediate_flag, final_flag, input_filename, compiler_path);

            (yyvsp[0].definition_list)->close_all_program_scopes();
            (yyvsp[0].definition_list)->close_library_function_scope();
            
            delete (yyvsp[0].definition_list);
        }
#line 1542 "./src/parser.cpp"
    break;

  case 3: /* definition_list: %empty  */
#line 206 "./src/parser.y"
                                { (yyval.definition_list) = new Block<Definition>(BlockType::Definition); }
#line 1548 "./src/parser.cpp"
    break;

  case 4: /* definition_list: definition_list letdef  */
#line 207 "./src/parser.y"
                                { (yyvsp[-1].definition_list)->append((yyvsp[0].let_def)); }
#line 1554 "./src/parser.cpp"
    break;

  case 5: /* definition_list: definition_list typedef  */
#line 208 "./src/parser.y"
                                { (yyvsp[-1].definition_list)->append((yyvsp[0].type_def)); }
#line 1560 "./src/parser.cpp"
    break;

  case 6: /* letdef: "let" "rec" def def_list  */
#line 212 "./src/parser.y"
                                { (yyvsp[0].def_list)->insert((yyvsp[0].def_list)->begin(), (yyvsp[-1].def)); (yyval.let_def) = new LetDef((yyvsp[0].def_list), LetType::Rec); }
#line 1566 "./src/parser.cpp"
    break;

  case 7: /* letdef: "let" def def_list  */
#line 213 "./src/parser.y"
                                { (yyvsp[0].def_list)->insert((yyvsp[0].def_list)->begin(), (yyvsp[-1].def)); (yyval.let_def) = new LetDef((yyvsp[0].def_list), LetType::NoRec); }
#line 1572 "./src/parser.cpp"
    break;

  case 8: /* def_list: %empty  */
#line 217 "./src/parser.y"
                        { (yyval.def_list) = new Block<Def>(BlockType::Def); }
#line 1578 "./src/parser.cpp"
    break;

  case 9: /* def_list: def_list "and" def  */
#line 218 "./src/parser.y"
                        { (yyvsp[-2].def_list)->append((yyvsp[0].def)); }
#line 1584 "./src/parser.cpp"
    break;

  case 10: /* def: T_ID '=' expr  */
#line 222 "./src/parser.y"
                                                            { (yyval.def) = new ConstDef((yyvsp[-2].id), (yyvsp[0].expr)); str_to_delete.push_back((yyvsp[-2].id)); }
#line 1590 "./src/parser.cpp"
    break;

  case 11: /* def: T_ID ':' type '=' expr  */
#line 223 "./src/parser.y"
                                                            { (yyval.def) = new ConstDef((yyvsp[-4].id), std::shared_ptr<TypeVariable>((yyvsp[-2].type)), (yyvsp[0].expr)); str_to_delete.push_back((yyvsp[-4].id)); }
#line 1596 "./src/parser.cpp"
    break;

  case 12: /* def: T_ID par par_list ':' type '=' expr  */
#line 224 "./src/parser.y"
                                                            { (yyvsp[-4].par_list)->insert((yyvsp[-4].par_list)->begin(), (yyvsp[-5].par)); (yyval.def) = new FunctionDef((yyvsp[-6].id), (yyvsp[-4].par_list), (yyvsp[0].expr), std::shared_ptr<TypeVariable>((yyvsp[-2].type))); str_to_delete.push_back((yyvsp[-6].id)); }
#line 1602 "./src/parser.cpp"
    break;

  case 13: /* def: T_ID par par_list '=' expr  */
#line 225 "./src/parser.y"
                                                            { (yyvsp[-2].par_list)->insert((yyvsp[-2].par_list)->begin(), (yyvsp[-3].par)); (yyval.def) = new FunctionDef((yyvsp[-4].id), (yyvsp[-2].par_list), (yyvsp[0].expr)); str_to_delete.push_back((yyvsp[-4].id)); }
#line 1608 "./src/parser.cpp"
    break;

  case 14: /* def: "mutable" T_ID  */
#line 226 "./src/parser.y"
                                                            { (yyval.def) = new VarDef((yyvsp[0].id)); str_to_delete.push_back((yyvsp[0].id)); }
#line 1614 "./src/parser.cpp"
    break;

  case 15: /* def: "mutable" T_ID ':' type  */
#line 227 "./src/parser.y"
                                                            { (yyval.def) = new VarDef((yyvsp[-2].id), std::shared_ptr<TypeVariable>((yyvsp[0].type))); str_to_delete.push_back((yyvsp[-2].id)); }
#line 1620 "./src/parser.cpp"
    break;

  case 16: /* def: "mutable" T_ID '[' expr expr_comma_list ']'  */
#line 228 "./src/parser.y"
                                                            { (yyvsp[-1].expr_comma_list)->insert((yyvsp[-1].expr_comma_list)->begin(), (yyvsp[-2].expr)); (yyval.def) = new ArrayDef((yyvsp[-4].id), (yyvsp[-1].expr_comma_list)); str_to_delete.push_back((yyvsp[-4].id)); }
#line 1626 "./src/parser.cpp"
    break;

  case 17: /* def: "mutable" T_ID '[' expr expr_comma_list ']' ':' type  */
#line 229 "./src/parser.y"
                                                            { (yyvsp[-3].expr_comma_list)->insert((yyvsp[-3].expr_comma_list)->begin(), (yyvsp[-4].expr)); (yyval.def) = new ArrayDef((yyvsp[-6].id), (yyvsp[-3].expr_comma_list), std::shared_ptr<TypeVariable>((yyvsp[0].type))); str_to_delete.push_back((yyvsp[-6].id)); }
#line 1632 "./src/parser.cpp"
    break;

  case 18: /* typedef: "type" tdef tdef_list  */
#line 233 "./src/parser.y"
                            { (yyvsp[0].t_def_list)->insert((yyvsp[0].t_def_list)->begin(), (yyvsp[-1].t_def)); (yyval.type_def) = new TypeDef((yyvsp[0].t_def_list)); }
#line 1638 "./src/parser.cpp"
    break;

  case 19: /* tdef_list: %empty  */
#line 237 "./src/parser.y"
                            { (yyval.t_def_list) = new Block<TDef>(BlockType::TDef); }
#line 1644 "./src/parser.cpp"
    break;

  case 20: /* tdef_list: tdef_list "and" tdef  */
#line 238 "./src/parser.y"
                            { (yyvsp[-2].t_def_list)->append((yyvsp[0].t_def)); }
#line 1650 "./src/parser.cpp"
    break;

  case 21: /* tdef: T_ID '=' constr constr_list  */
#line 242 "./src/parser.y"
                                    { (yyvsp[0].constructor_list)->insert((yyvsp[0].constructor_list)->begin(), (yyvsp[-1].constructor)); (yyval.t_def) = new TDef((yyvsp[-3].id), (yyvsp[0].constructor_list)); }
#line 1656 "./src/parser.cpp"
    break;

  case 22: /* constr_list: %empty  */
#line 246 "./src/parser.y"
                            { (yyval.constructor_list) = new Block<Constructor>(BlockType::Constructor); }
#line 1662 "./src/parser.cpp"
    break;

  case 23: /* constr_list: constr_list '|' constr  */
#line 247 "./src/parser.y"
                            { (yyvsp[-2].constructor_list)->append((yyvsp[0].constructor)); }
#line 1668 "./src/parser.cpp"
    break;

  case 24: /* constr: T_CONSTRUCTOR_ID  */
#line 251 "./src/parser.y"
                                            { (yyval.constructor) = new Constructor((yyvsp[0].id)); }
#line 1674 "./src/parser.cpp"
    break;

  case 25: /* constr: T_CONSTRUCTOR_ID "of" type type_list  */
#line 252 "./src/parser.y"
                                            { (yyvsp[0].type_list)->insert((yyvsp[0].type_list)->begin(), std::shared_ptr<TypeVariable>((yyvsp[-1].type))); (yyval.constructor) = new Constructor((yyvsp[-3].id), (yyvsp[0].type_list)); }
#line 1680 "./src/parser.cpp"
    break;

  case 26: /* par_list: %empty  */
#line 256 "./src/parser.y"
                    { (yyval.par_list) = new Block<Par>(BlockType::Par); }
#line 1686 "./src/parser.cpp"
    break;

  case 27: /* par_list: par_list par  */
#line 257 "./src/parser.y"
                    { (yyvsp[-1].par_list)->append((yyvsp[0].par)); }
#line 1692 "./src/parser.cpp"
    break;

  case 28: /* par: T_ID  */
#line 261 "./src/parser.y"
                            { (yyval.par) = new Par((yyvsp[0].id)); str_to_delete.push_back((yyvsp[0].id)); }
#line 1698 "./src/parser.cpp"
    break;

  case 29: /* par: '(' T_ID ':' type ')'  */
#line 262 "./src/parser.y"
                            { (yyval.par) = new Par((yyvsp[-3].id), std::shared_ptr<TypeVariable>((yyvsp[-1].type))); str_to_delete.push_back((yyvsp[-3].id)); }
#line 1704 "./src/parser.cpp"
    break;

  case 30: /* expr_comma_list: %empty  */
#line 266 "./src/parser.y"
                                { (yyval.expr_comma_list) = new Block<Expr>(BlockType::ExprComma); }
#line 1710 "./src/parser.cpp"
    break;

  case 31: /* expr_comma_list: expr_comma_list ',' expr  */
#line 267 "./src/parser.y"
                                { (yyvsp[-2].expr_comma_list)->append((yyvsp[0].expr)); }
#line 1716 "./src/parser.cpp"
    break;

  case 32: /* expr: T_ID func_expr func_expr_list  */
#line 271 "./src/parser.y"
                                                            { (yyvsp[0].func_expr_list)->insert((yyvsp[0].func_expr_list)->begin(), (yyvsp[-1].expr)); (yyval.expr) = new FunctionCall((yyvsp[-2].id), (yyvsp[0].func_expr_list)); str_to_delete.push_back((yyvsp[-2].id)); }
#line 1722 "./src/parser.cpp"
    break;

  case 33: /* expr: T_CONSTRUCTOR_ID func_expr func_expr_list  */
#line 272 "./src/parser.y"
                                                            { (yyvsp[0].func_expr_list)->insert((yyvsp[0].func_expr_list)->begin(), (yyvsp[-1].expr)); (yyval.expr) = new ConstructorCall((yyvsp[-2].id), (yyvsp[0].func_expr_list)); str_to_delete.push_back((yyvsp[-2].id)); }
#line 1728 "./src/parser.cpp"
    break;

  case 34: /* expr: "dim" T_ID  */
#line 273 "./src/parser.y"
                                                            { (yyval.expr) = new Dim((yyvsp[0].id)); str_to_delete.push_back((yyvsp[0].id)); }
#line 1734 "./src/parser.cpp"
    break;

  case 35: /* expr: "dim" T_CONST_INT T_ID  */
#line 274 "./src/parser.y"
                                                            { (yyval.expr) = new Dim((yyvsp[0].id), (yyvsp[-1].number)); str_to_delete.push_back((yyvsp[0].id)); }
#line 1740 "./src/parser.cpp"
    break;

  case 36: /* expr: "new" type  */
#line 275 "./src/parser.y"
                                                            { (yyval.expr) = new New(std::shared_ptr<TypeVariable>((yyvsp[0].type))); }
#line 1746 "./src/parser.cpp"
    break;

  case 37: /* expr: "delete" expr  */
#line 276 "./src/parser.y"
                                                            { (yyval.expr) = new Delete((yyvsp[0].expr)); }
#line 1752 "./src/parser.cpp"
    break;

  case 38: /* expr: letdef "in" expr  */
#line 277 "./src/parser.y"
                                                            { (yyval.expr) = new LetIn((yyvsp[-2].let_def), (yyvsp[0].expr)); }
#line 1758 "./src/parser.cpp"
    break;

  case 39: /* expr: "begin" expr "end"  */
#line 278 "./src/parser.y"
                                                            { (yyval.expr) = (yyvsp[-1].expr); }
#line 1764 "./src/parser.cpp"
    break;

  case 40: /* expr: "if" expr "then" expr  */
#line 279 "./src/parser.y"
                                                            { (yyval.expr) = new If((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1770 "./src/parser.cpp"
    break;

  case 41: /* expr: "if" expr "then" expr "else" expr  */
#line 280 "./src/parser.y"
                                                            { (yyval.expr) = new If((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1776 "./src/parser.cpp"
    break;

  case 42: /* expr: "while" expr "do" expr "done"  */
#line 281 "./src/parser.y"
                                                            { (yyval.expr) = new While((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 1782 "./src/parser.cpp"
    break;

  case 43: /* expr: "for" T_ID '=' expr "to" expr "do" expr "done"  */
#line 282 "./src/parser.y"
                                                            { (yyval.expr) = new ForTo((yyvsp[-7].id), (yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr)); str_to_delete.push_back((yyvsp[-7].id)); }
#line 1788 "./src/parser.cpp"
    break;

  case 44: /* expr: "for" T_ID '=' expr "downto" expr "do" expr "done"  */
#line 283 "./src/parser.y"
                                                            { (yyval.expr) = new ForDownTo((yyvsp[-7].id), (yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr)); str_to_delete.push_back((yyvsp[-7].id)); }
#line 1794 "./src/parser.cpp"
    break;

  case 45: /* expr: '+' expr  */
#line 284 "./src/parser.y"
                                                            { (yyval.expr) = new UnOp((yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1800 "./src/parser.cpp"
    break;

  case 46: /* expr: '-' expr  */
#line 285 "./src/parser.y"
                                                            { (yyval.expr) = new UnOp((yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1806 "./src/parser.cpp"
    break;

  case 47: /* expr: "+." expr  */
#line 286 "./src/parser.y"
                                                            { (yyval.expr) = new UnOp((yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1812 "./src/parser.cpp"
    break;

  case 48: /* expr: "-." expr  */
#line 287 "./src/parser.y"
                                                            { (yyval.expr) = new UnOp((yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1818 "./src/parser.cpp"
    break;

  case 49: /* expr: "not" expr  */
#line 288 "./src/parser.y"
                                                            { (yyval.expr) = new UnOp((yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1824 "./src/parser.cpp"
    break;

  case 50: /* expr: expr '+' expr  */
#line 289 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1830 "./src/parser.cpp"
    break;

  case 51: /* expr: expr '-' expr  */
#line 290 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1836 "./src/parser.cpp"
    break;

  case 52: /* expr: expr '*' expr  */
#line 291 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1842 "./src/parser.cpp"
    break;

  case 53: /* expr: expr '/' expr  */
#line 292 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1848 "./src/parser.cpp"
    break;

  case 54: /* expr: expr "+." expr  */
#line 293 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1854 "./src/parser.cpp"
    break;

  case 55: /* expr: expr "-." expr  */
#line 294 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1860 "./src/parser.cpp"
    break;

  case 56: /* expr: expr "*." expr  */
#line 295 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1866 "./src/parser.cpp"
    break;

  case 57: /* expr: expr "/." expr  */
#line 296 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1872 "./src/parser.cpp"
    break;

  case 58: /* expr: expr "**" expr  */
#line 297 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1878 "./src/parser.cpp"
    break;

  case 59: /* expr: expr '=' expr  */
#line 298 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1884 "./src/parser.cpp"
    break;

  case 60: /* expr: expr "<>" expr  */
#line 299 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1890 "./src/parser.cpp"
    break;

  case 61: /* expr: expr '<' expr  */
#line 300 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1896 "./src/parser.cpp"
    break;

  case 62: /* expr: expr '>' expr  */
#line 301 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1902 "./src/parser.cpp"
    break;

  case 63: /* expr: expr "<=" expr  */
#line 302 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1908 "./src/parser.cpp"
    break;

  case 64: /* expr: expr ">=" expr  */
#line 303 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1914 "./src/parser.cpp"
    break;

  case 65: /* expr: expr "==" expr  */
#line 304 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1920 "./src/parser.cpp"
    break;

  case 66: /* expr: expr "!=" expr  */
#line 305 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1926 "./src/parser.cpp"
    break;

  case 67: /* expr: expr "&&" expr  */
#line 306 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1932 "./src/parser.cpp"
    break;

  case 68: /* expr: expr "||" expr  */
#line 307 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1938 "./src/parser.cpp"
    break;

  case 69: /* expr: expr ';' expr  */
#line 308 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1944 "./src/parser.cpp"
    break;

  case 70: /* expr: expr ":=" expr  */
#line 309 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1950 "./src/parser.cpp"
    break;

  case 71: /* expr: expr "mod" expr  */
#line 310 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1956 "./src/parser.cpp"
    break;

  case 72: /* expr: "match" expr "with" clause clause_list "end"  */
#line 311 "./src/parser.y"
                                                            { (yyvsp[-1].clause_list)->insert((yyvsp[-1].clause_list)->begin(), (yyvsp[-2].clause)); (yyval.expr) = new Match((yyvsp[-4].expr), (yyvsp[-1].clause_list)); }
#line 1962 "./src/parser.cpp"
    break;

  case 73: /* expr: func_expr  */
#line 312 "./src/parser.y"
                                                            { (yyval.expr) = (yyvsp[0].expr); }
#line 1968 "./src/parser.cpp"
    break;

  case 74: /* func_expr: '!' func_expr  */
#line 316 "./src/parser.y"
                                                            { (yyval.expr) = new UnOp((yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1974 "./src/parser.cpp"
    break;

  case 75: /* func_expr: '(' expr ')'  */
#line 317 "./src/parser.y"
                                                            { (yyval.expr) = (yyvsp[-1].expr); }
#line 1980 "./src/parser.cpp"
    break;

  case 76: /* func_expr: '(' ')'  */
#line 318 "./src/parser.y"
                                                            { (yyval.expr) = new Unit(); }
#line 1986 "./src/parser.cpp"
    break;

  case 77: /* func_expr: T_ID  */
#line 319 "./src/parser.y"
                                                            { (yyval.expr) = new Id((yyvsp[0].id)); str_to_delete.push_back((yyvsp[0].id)); }
#line 1992 "./src/parser.cpp"
    break;

  case 78: /* func_expr: T_CONSTRUCTOR_ID  */
#line 320 "./src/parser.y"
                                                            { (yyval.expr) = new ConstructorCall((yyvsp[0].id)); str_to_delete.push_back((yyvsp[0].id)); }
#line 1998 "./src/parser.cpp"
    break;

  case 79: /* func_expr: T_CONST_INT  */
#line 321 "./src/parser.y"
                                                            { (yyval.expr) = new Int((yyvsp[0].number)); }
#line 2004 "./src/parser.cpp"
    break;

  case 80: /* func_expr: T_CONST_FLOAT  */
#line 322 "./src/parser.y"
                                                            { (yyval.expr) = new Float((yyvsp[0].float_value)); }
#line 2010 "./src/parser.cpp"
    break;

  case 81: /* func_expr: T_CONST_CHAR  */
#line 323 "./src/parser.y"
                                                            { (yyval.expr) = new Char((yyvsp[0].const_char)); }
#line 2016 "./src/parser.cpp"
    break;

  case 82: /* func_expr: T_STRING_LITERAL  */
#line 324 "./src/parser.y"
                                                            { (yyval.expr) = new String((yyvsp[0].string_literal)); str_to_delete.push_back((yyvsp[0].string_literal)); }
#line 2022 "./src/parser.cpp"
    break;

  case 83: /* func_expr: "true"  */
#line 325 "./src/parser.y"
                                                            { (yyval.expr) = new Bool(true); }
#line 2028 "./src/parser.cpp"
    break;

  case 84: /* func_expr: "false"  */
#line 326 "./src/parser.y"
                                                            { (yyval.expr) = new Bool(false); }
#line 2034 "./src/parser.cpp"
    break;

  case 85: /* func_expr: T_ID '[' expr expr_comma_list ']'  */
#line 327 "./src/parser.y"
                                                            { (yyvsp[-1].expr_comma_list)->insert((yyvsp[-1].expr_comma_list)->begin(), (yyvsp[-2].expr)); (yyval.expr) = new ArrayIndex((yyvsp[-4].id), (yyvsp[-1].expr_comma_list)); str_to_delete.push_back((yyvsp[-4].id)); }
#line 2040 "./src/parser.cpp"
    break;

  case 86: /* func_expr_list: %empty  */
#line 331 "./src/parser.y"
                                                            { (yyval.func_expr_list) = new Block<Expr>(BlockType::Expr); }
#line 2046 "./src/parser.cpp"
    break;

  case 87: /* func_expr_list: func_expr_list func_expr  */
#line 332 "./src/parser.y"
                                                            { (yyvsp[-1].func_expr_list)->append((yyvsp[0].expr)); }
#line 2052 "./src/parser.cpp"
    break;

  case 88: /* type_list: %empty  */
#line 336 "./src/parser.y"
                                                            { (yyval.type_list) = new std::vector<std::shared_ptr<TypeVariable>>(); }
#line 2058 "./src/parser.cpp"
    break;

  case 89: /* type_list: type_list type  */
#line 337 "./src/parser.y"
                                                            { (yyvsp[-1].type_list)->push_back(std::shared_ptr<TypeVariable>((yyvsp[0].type))); }
#line 2064 "./src/parser.cpp"
    break;

  case 90: /* type: "unit"  */
#line 341 "./src/parser.y"
                                                            { (yyval.type) = new TypeVariable(TypeTag::Unit); }
#line 2070 "./src/parser.cpp"
    break;

  case 91: /* type: "int"  */
#line 342 "./src/parser.y"
                                                            { (yyval.type) = new TypeVariable(TypeTag::Int); }
#line 2076 "./src/parser.cpp"
    break;

  case 92: /* type: "char"  */
#line 343 "./src/parser.y"
                                                            { (yyval.type) = new TypeVariable(TypeTag::Char); }
#line 2082 "./src/parser.cpp"
    break;

  case 93: /* type: "bool"  */
#line 344 "./src/parser.y"
                                                            { (yyval.type) = new TypeVariable(TypeTag::Bool); }
#line 2088 "./src/parser.cpp"
    break;

  case 94: /* type: "float"  */
#line 345 "./src/parser.y"
                                                            { (yyval.type) = new TypeVariable(TypeTag::Float); }
#line 2094 "./src/parser.cpp"
    break;

  case 95: /* type: '(' type ')'  */
#line 346 "./src/parser.y"
                                                            { (yyval.type) = (yyvsp[-1].type); }
#line 2100 "./src/parser.cpp"
    break;

  case 96: /* type: type "->" type  */
#line 347 "./src/parser.y"
                                                            { (yyval.type) = new TypeVariable(TypeTag::Function, std::shared_ptr<TypeVariable>((yyvsp[-2].type)), std::shared_ptr<TypeVariable>((yyvsp[0].type)), FunctionTypeTag::Actual); }
#line 2106 "./src/parser.cpp"
    break;

  case 97: /* type: type "ref"  */
#line 348 "./src/parser.y"
                                                            { (yyval.type) = new TypeVariable(TypeTag::Reference, std::shared_ptr<TypeVariable>((yyvsp[-1].type))); }
#line 2112 "./src/parser.cpp"
    break;

  case 98: /* type: "array" "of" type  */
#line 349 "./src/parser.y"
                                                            { (yyval.type) = new TypeVariable(TypeTag::Array, std::shared_ptr<TypeVariable>((yyvsp[0].type)), 1, DimType::Exact); }
#line 2118 "./src/parser.cpp"
    break;

  case 99: /* type: "array" '[' asterisk_list ']' "of" type  */
#line 350 "./src/parser.y"
                                                            { (yyval.type) = new TypeVariable(TypeTag::Array, std::shared_ptr<TypeVariable>((yyvsp[0].type)), (yyvsp[-3].dimension_count), DimType::Exact); }
#line 2124 "./src/parser.cpp"
    break;

  case 100: /* type: T_ID  */
#line 351 "./src/parser.y"
                                                            { (yyval.type) = new TypeVariable(TypeTag::UserType, (yyvsp[0].id)); }
#line 2130 "./src/parser.cpp"
    break;

  case 101: /* asterisk_list: '*'  */
#line 355 "./src/parser.y"
                            { (yyval.dimension_count) = 1; }
#line 2136 "./src/parser.cpp"
    break;

  case 102: /* asterisk_list: asterisk_list ',' '*'  */
#line 356 "./src/parser.y"
                            { (yyval.dimension_count) = 1 + (yyvsp[-2].dimension_count); }
#line 2142 "./src/parser.cpp"
    break;

  case 103: /* clause_list: %empty  */
#line 360 "./src/parser.y"
                                { (yyval.clause_list) = new Block<Clause>(BlockType::Clause); }
#line 2148 "./src/parser.cpp"
    break;

  case 104: /* clause_list: clause_list '|' clause  */
#line 361 "./src/parser.y"
                                { (yyvsp[-2].clause_list)->append((yyvsp[0].clause)); }
#line 2154 "./src/parser.cpp"
    break;

  case 105: /* clause: pattern "->" expr  */
#line 365 "./src/parser.y"
                                { (yyval.clause) = new Clause((yyvsp[-2].pattern), (yyvsp[0].expr)); }
#line 2160 "./src/parser.cpp"
    break;

  case 106: /* pattern: pattern_high  */
#line 369 "./src/parser.y"
                                        { (yyval.pattern) = (yyvsp[0].pattern); }
#line 2166 "./src/parser.cpp"
    break;

  case 107: /* pattern: T_CONSTRUCTOR_ID pattern_high_list  */
#line 370 "./src/parser.y"
                                        { (yyval.pattern) = new ConstructorPattern((yyvsp[-1].id), (yyvsp[0].pattern_list)); }
#line 2172 "./src/parser.cpp"
    break;

  case 108: /* pattern_high_list: %empty  */
#line 374 "./src/parser.y"
                                        { (yyval.pattern_list) = new Block<Pattern>(BlockType::Pattern); }
#line 2178 "./src/parser.cpp"
    break;

  case 109: /* pattern_high_list: pattern_high_list pattern_high  */
#line 375 "./src/parser.y"
                                        { (yyvsp[-1].pattern_list)->append((yyvsp[0].pattern)); }
#line 2184 "./src/parser.cpp"
    break;

  case 110: /* pattern_high: '+' T_CONST_INT  */
#line 379 "./src/parser.y"
                                        { (yyval.pattern) = new IntPattern((yyvsp[0].number));      }
#line 2190 "./src/parser.cpp"
    break;

  case 111: /* pattern_high: '-' T_CONST_INT  */
#line 380 "./src/parser.y"
                                        { (yyval.pattern) = new IntPattern(-(yyvsp[0].number));     }
#line 2196 "./src/parser.cpp"
    break;

  case 112: /* pattern_high: T_CONST_INT  */
#line 381 "./src/parser.y"
                                        { (yyval.pattern) = new IntPattern((yyvsp[0].number));      }
#line 2202 "./src/parser.cpp"
    break;

  case 113: /* pattern_high: "+." T_CONST_FLOAT  */
#line 382 "./src/parser.y"
                                        { (yyval.pattern) = new FloatPattern((yyvsp[0].float_value));    }
#line 2208 "./src/parser.cpp"
    break;

  case 114: /* pattern_high: "-." T_CONST_FLOAT  */
#line 383 "./src/parser.y"
                                        { (yyval.pattern) = new FloatPattern(-(yyvsp[0].float_value));   }
#line 2214 "./src/parser.cpp"
    break;

  case 115: /* pattern_high: T_CONST_FLOAT  */
#line 384 "./src/parser.y"
                                        { (yyval.pattern) = new FloatPattern((yyvsp[0].float_value));    }
#line 2220 "./src/parser.cpp"
    break;

  case 116: /* pattern_high: T_CONST_CHAR  */
#line 385 "./src/parser.y"
                                        { (yyval.pattern) = new CharPattern((yyvsp[0].const_char));     }
#line 2226 "./src/parser.cpp"
    break;

  case 117: /* pattern_high: "true"  */
#line 386 "./src/parser.y"
                                        { (yyval.pattern) = new BoolPattern(true);   }
#line 2232 "./src/parser.cpp"
    break;

  case 118: /* pattern_high: "false"  */
#line 387 "./src/parser.y"
                                        { (yyval.pattern) = new BoolPattern(false);  }
#line 2238 "./src/parser.cpp"
    break;

  case 119: /* pattern_high: T_ID  */
#line 388 "./src/parser.y"
                                        { (yyval.pattern) = new IdPattern((yyvsp[0].id));       }
#line 2244 "./src/parser.cpp"
    break;

  case 120: /* pattern_high: '(' pattern ')'  */
#line 389 "./src/parser.y"
                                        { (yyval.pattern) = (yyvsp[-1].pattern);                      }
#line 2250 "./src/parser.cpp"
    break;


#line 2254 "./src/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 392 "./src/parser.y"


std::string get_file_name(std::string file_path, char seperator = '/') {
    auto dot_position = file_path.rfind('.');
    auto sep_position = file_path.rfind(seperator);

    if(sep_position != std::string::npos) {
        return file_path.substr(0, dot_position);
    }
    return "a";
}

void yyerror(const char* msg){
    fprintf(stderr, "Error in line %i: %s\n", yylineno, msg);
    exit(1);
}

int main(int argc, char** argv) {
    int option;
	compiler_path = argv[0];

    //If no option was given output help and exit
	if (argc == 1) {
		std::cerr <<
			"OVERVIEW: llama compiler\n"
            "USAGE: llamac [OPTIONS] [FILE]\n"
            "OPTIONS:\n"
			"-O:    enable optimizations\n"
			"-i:    the input must be given on standard input and the intermediate code will be printed on standard output\n"
			"-f:    the input must be given on standard input and the final code will be printed on standard output\n"
			"\n"
			"If no -i or -f options are selected the input file must be given as an argument\n";
		exit(1);
	}

	optimizations_flag = intermediate_flag = final_flag = false;
	while ((option = getopt(argc, argv, "Ofi")) != -1) {
		switch(option) {
			case 'O':
				optimizations_flag = true;
				break;
			case 'f':
				final_flag = true;
				break;
			case 'i':
				intermediate_flag = true;
				break;
			case '?':
				std::cerr << "Enter ./llamac to see usage information\n";
				exit(1);
			default:
				break;
		}
	}

	if(intermediate_flag || final_flag)
		yyin = stdin;
	else {
		yyin = fopen(argv[optind], "r");
		input_filename = get_file_name(std::string(argv[optind]));
	}

    int result = yyparse();

    //delete all allocated strings
    for(auto string_ptr: str_to_delete) {
        delete string_ptr;
    }

    return result;
}
