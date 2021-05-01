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
#include "includes.hpp"
#include "lexer.hpp"


#line 81 "./src/parser.cpp"

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
  YYSYMBOL_T_LET = 20,                     /* "let"  */
  YYSYMBOL_T_MATCH = 21,                   /* "match"  */
  YYSYMBOL_T_MOD = 22,                     /* "mod"  */
  YYSYMBOL_T_MUTABLE = 23,                 /* "mutable"  */
  YYSYMBOL_T_NEW = 24,                     /* "new"  */
  YYSYMBOL_T_NOT = 25,                     /* "not"  */
  YYSYMBOL_T_OF = 26,                      /* "of"  */
  YYSYMBOL_T_REC = 27,                     /* "rec"  */
  YYSYMBOL_T_REF = 28,                     /* "ref"  */
  YYSYMBOL_T_THEN = 29,                    /* "then"  */
  YYSYMBOL_T_TO = 30,                      /* "to"  */
  YYSYMBOL_T_TRUE = 31,                    /* "true"  */
  YYSYMBOL_T_TYPE = 32,                    /* "type"  */
  YYSYMBOL_T_UNIT = 33,                    /* "unit"  */
  YYSYMBOL_T_WHILE = 34,                   /* "while"  */
  YYSYMBOL_T_WITH = 35,                    /* "with"  */
  YYSYMBOL_T_TYPE_ARROW_OP = 36,           /* "->"  */
  YYSYMBOL_T_AND_OP = 37,                  /* "&&"  */
  YYSYMBOL_T_OR_OP = 38,                   /* "||"  */
  YYSYMBOL_T_NOT_EQ_OP = 39,               /* "<>"  */
  YYSYMBOL_T_LESS_THAN_OR_EQ_OP = 40,      /* "<="  */
  YYSYMBOL_T_GREATER_THAN_OR_EQ_OP = 41,   /* ">="  */
  YYSYMBOL_T_NAT_EQ_OP = 42,               /* "=="  */
  YYSYMBOL_T_NAT_NOT_EQ_OP = 43,           /* "!="  */
  YYSYMBOL_T_ASSIGNMENT_OP = 44,           /* ":="  */
  YYSYMBOL_T_ID = 45,                      /* T_ID  */
  YYSYMBOL_T_CONSTRUCTOR_ID = 46,          /* T_CONSTRUCTOR_ID  */
  YYSYMBOL_T_CONST_CHAR = 47,              /* T_CONST_CHAR  */
  YYSYMBOL_T_CONST_INT = 48,               /* T_CONST_INT  */
  YYSYMBOL_T_STRING_LITERAL = 49,          /* T_STRING_LITERAL  */
  YYSYMBOL_EXPR_LIST = 50,                 /* EXPR_LIST  */
  YYSYMBOL_LOCAL_DEFS = 51,                /* LOCAL_DEFS  */
  YYSYMBOL_52_ = 52,                       /* ';'  */
  YYSYMBOL_IF_THEN = 53,                   /* IF_THEN  */
  YYSYMBOL_IF_THEN_ELSE = 54,              /* IF_THEN_ELSE  */
  YYSYMBOL_55_ = 55,                       /* '='  */
  YYSYMBOL_56_ = 56,                       /* '>'  */
  YYSYMBOL_57_ = 57,                       /* '<'  */
  YYSYMBOL_58_ = 58,                       /* '+'  */
  YYSYMBOL_59_ = 59,                       /* '-'  */
  YYSYMBOL_60_ = 60,                       /* '*'  */
  YYSYMBOL_61_ = 61,                       /* '/'  */
  YYSYMBOL_62_ = 62,                       /* "**"  */
  YYSYMBOL_UNOP = 63,                      /* UNOP  */
  YYSYMBOL_FUNCTION_CALL = 64,             /* FUNCTION_CALL  */
  YYSYMBOL_65_ = 65,                       /* '('  */
  YYSYMBOL_66_ = 66,                       /* '!'  */
  YYSYMBOL_ARRAY_INDEX = 67,               /* ARRAY_INDEX  */
  YYSYMBOL_68_ = 68,                       /* ':'  */
  YYSYMBOL_69_ = 69,                       /* '['  */
  YYSYMBOL_70_ = 70,                       /* ']'  */
  YYSYMBOL_71_ = 71,                       /* ')'  */
  YYSYMBOL_72_ = 72,                       /* ','  */
  YYSYMBOL_YYACCEPT = 73,                  /* $accept  */
  YYSYMBOL_program = 74,                   /* program  */
  YYSYMBOL_letdef_list = 75,               /* letdef_list  */
  YYSYMBOL_letdef = 76,                    /* letdef  */
  YYSYMBOL_def_list = 77,                  /* def_list  */
  YYSYMBOL_def = 78,                       /* def  */
  YYSYMBOL_par_list = 79,                  /* par_list  */
  YYSYMBOL_par = 80,                       /* par  */
  YYSYMBOL_expr_comma_list = 81,           /* expr_comma_list  */
  YYSYMBOL_expr = 82,                      /* expr  */
  YYSYMBOL_expr_list = 83,                 /* expr_list  */
  YYSYMBOL_type = 84,                      /* type  */
  YYSYMBOL_asterisk_list = 85              /* asterisk_list  */
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
#define YYLAST   694

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   312


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
       2,     2,     2,    66,     2,     2,     2,     2,     2,     2,
      65,    71,    60,    58,    72,    59,     2,    61,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    68,    52,
      57,    55,    56,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    69,     2,    70,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    53,    54,    62,
      63,    64,    67
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   120,   120,   124,   125,   129,   130,   134,   135,   139,
     140,   141,   142,   143,   144,   145,   146,   150,   151,   155,
     156,   160,   161,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   209,   210,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   227,   228
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
  "\"if\"", "\"in\"", "\"int\"", "\"let\"", "\"match\"", "\"mod\"",
  "\"mutable\"", "\"new\"", "\"not\"", "\"of\"", "\"rec\"", "\"ref\"",
  "\"then\"", "\"to\"", "\"true\"", "\"type\"", "\"unit\"", "\"while\"",
  "\"with\"", "\"->\"", "\"&&\"", "\"||\"", "\"<>\"", "\"<=\"", "\">=\"",
  "\"==\"", "\"!=\"", "\":=\"", "T_ID", "T_CONSTRUCTOR_ID", "T_CONST_CHAR",
  "T_CONST_INT", "T_STRING_LITERAL", "EXPR_LIST", "LOCAL_DEFS", "';'",
  "IF_THEN", "IF_THEN_ELSE", "'='", "'>'", "'<'", "'+'", "'-'", "'*'",
  "'/'", "\"**\"", "UNOP", "FUNCTION_CALL", "'('", "'!'", "ARRAY_INDEX",
  "':'", "'['", "']'", "')'", "','", "$accept", "program", "letdef_list",
  "letdef", "def_list", "def", "par_list", "par", "expr_comma_list",
  "expr", "expr_list", "type", "asterisk_list", YY_NULLPTR
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
     305,   306,    59,   307,   308,    61,    62,    60,    43,    45,
      42,    47,   309,   310,   311,    40,    33,   312,    58,    91,
      93,    41,    44
};
#endif

#define YYPACT_NINF (-45)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -45,    21,    17,   -45,     1,   -45,   -44,    54,    56,   -45,
      24,   -45,   -45,   140,     0,     6,   -45,     3,     6,   140,
       3,   140,   140,   -40,   -45,    27,   140,     6,   140,   -45,
     140,   -21,   -45,   -45,   -45,   140,   140,    71,   140,    60,
     528,    13,   -22,   -45,   -45,   -45,   -45,     6,   -14,    78,
      54,     4,   528,   463,   -45,   -45,    40,    48,   503,     4,
     -45,   192,   140,   177,   -45,   -45,   -45,   413,   -45,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,     6,     6,    44,
      -2,   -45,     6,   140,   140,     6,   -45,   -45,   -39,   -45,
     -45,   140,   140,   140,   528,   528,   -45,   528,   -45,   610,
     603,   633,   633,   633,   633,   633,   553,   578,   633,   633,
     633,    46,    46,   -45,   -45,    -1,   -45,   -45,   -45,     4,
     528,   528,   -13,    41,   140,   388,   453,   282,   -34,   -45,
      28,   140,     6,   528,   140,   140,   140,   -45,   -45,    82,
      50,   528,     4,   217,   257,   578,     6,   -45,   140,   140,
     -45,   322,   347,   -45,   -45
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     0,     4,     0,     0,     0,     7,
      13,     7,    19,     0,     0,     0,    17,     6,     0,     0,
       5,     0,     0,     0,    27,     0,     0,     0,     0,    26,
       0,    64,    24,    23,    25,     0,     0,     0,     0,     0,
       9,     0,     0,    69,    68,    67,    66,     0,     0,     0,
       0,    14,    21,     0,    35,    32,     0,     0,     0,    34,
      46,     0,     0,    30,    43,    44,    28,     0,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    72,     0,     0,     0,     0,    18,     8,     0,    37,
      33,     0,     0,     0,    21,    65,    29,    36,    63,    59,
      60,    52,    55,    56,    57,    58,    62,    61,    51,    54,
      53,    47,    48,    49,    50,     0,    73,    75,    70,    71,
      10,    12,     0,    15,     0,     0,    38,     0,     0,    20,
       0,     0,     0,    22,     0,     0,     0,    40,    31,     0,
       0,    11,    16,     0,     0,    39,     0,    76,     0,     0,
      74,     0,     0,    42,    41
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -45,   -45,   -45,   110,   102,    23,   -45,    65,    30,   -19,
     -45,     2,   -45
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    39,    17,     9,    49,    16,    98,    40,
      63,    48,   140
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      52,    10,    53,    54,    88,    55,    50,    58,    56,    60,
      42,    61,    43,    44,    91,    91,    64,    65,    67,    68,
      51,     3,    92,    92,     6,    45,    91,    91,     7,    59,
      11,   133,    91,   134,    92,    92,   148,     4,   134,    46,
      92,    93,   141,   104,   105,    41,     8,    89,    62,    90,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,    70,   128,
     139,    47,    57,    97,   130,   131,    21,     6,    69,    22,
      23,    87,   135,   136,   137,   100,    24,    25,    26,   125,
     126,     4,    18,    19,   129,    27,    28,   132,   149,     8,
     150,    12,    29,   101,   127,    30,    85,    86,   156,   142,
     157,    13,     5,    20,    96,   143,    31,     0,    32,    33,
      34,    14,   151,    12,    15,   153,   154,   155,     0,    35,
      36,     0,     0,    94,   138,     0,    37,    38,     0,   161,
     162,     0,    66,    14,   152,    21,    95,     0,    22,    23,
       0,     0,     0,     0,     0,    24,    25,    26,   160,     0,
       4,     0,     0,     0,    27,    28,     0,     0,     0,     0,
       0,    29,     0,     0,    30,     0,     0,     0,     0,     0,
       0,     0,    21,     0,     0,    31,    23,    32,    33,    34,
       0,     0,    24,    25,    26,     0,     0,     4,    35,    36,
       0,    27,   103,     0,     0,    37,    38,     0,    29,     0,
       0,    30,     0,     0,    70,     0,     0,     0,     0,     0,
       0,     0,    31,     0,    32,    33,    34,   158,     0,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    70,
       0,     0,    37,    38,    79,     0,     0,    80,    81,    82,
      83,    84,    85,    86,    71,    72,    73,    74,    75,    76,
      77,    78,     0,     0,     0,     0,     0,   159,     0,    79,
       0,     0,    80,    81,    82,    83,    84,    85,    86,    70,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   147,    71,    72,    73,    74,    75,    76,
      77,    78,     0,     0,    70,     0,     0,     0,     0,    79,
       0,     0,    80,    81,    82,    83,    84,    85,    86,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,     0,
       0,     0,     0,   163,    79,     0,     0,    80,    81,    82,
      83,    84,    85,    86,    70,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   164,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    70,
       0,     0,     0,     0,    79,     0,     0,    80,    81,    82,
      83,    84,    85,    86,    71,    72,    73,    74,    75,    76,
      77,    78,     0,     0,     0,     0,     0,     0,     0,    79,
     144,     0,    80,    81,    82,    83,    84,    85,    86,     0,
      70,     0,     0,     0,     0,     0,     0,     0,   145,     0,
       0,     0,     0,     0,     0,    71,    72,    73,    74,    75,
      76,    77,    78,     0,     0,    70,     0,     0,     0,     0,
      79,     0,     0,    80,    81,    82,    83,    84,    85,    86,
      71,    72,    73,    74,    75,    76,    77,    78,     0,     0,
       0,     0,     0,     0,     0,    79,   146,     0,    80,    81,
      82,    83,    84,    85,    86,    70,     0,    99,     0,     0,
       0,     0,     0,     0,   106,    70,     0,     0,     0,     0,
      71,    72,    73,    74,    75,    76,    77,    78,     0,     0,
      71,    72,    73,    74,    75,    76,    77,    78,    80,    81,
      82,    83,    84,    85,    86,    79,     0,     0,    80,    81,
      82,    83,    84,    85,    86,    70,     0,     0,     0,     0,
       0,     0,   102,     0,     0,     0,     0,     0,     0,     0,
      71,    72,    73,    74,    75,    76,    77,    78,     0,     0,
      70,     0,     0,     0,     0,    79,     0,     0,    80,    81,
      82,    83,    84,    85,    86,    71,    72,    73,    74,    75,
      76,    77,    78,     0,     0,    70,     0,     0,     0,     0,
      79,     0,     0,    80,    81,    82,    83,    84,    85,    86,
      71,    72,    73,    74,    75,    76,    77,    -1,     0,     0,
      70,     0,     0,     0,     0,     0,     0,     0,    80,    81,
      82,    83,    84,    85,    86,    71,    72,    73,    74,    75,
      76,    77,    78,     0,     0,    70,     0,     0,     0,     0,
       0,     0,    70,    80,    81,    82,    83,    84,    85,    86,
      71,     0,    73,    74,    75,    76,    77,     0,     0,    73,
      74,    75,    76,    77,     0,    70,     0,     0,    80,    81,
      82,    83,    84,    85,    86,    80,    81,    82,    83,    84,
      85,    86,    -1,    -1,    -1,    -1,    -1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    -1,    -1,
      -1,    83,    84,    85,    86
};

static const yytype_int16 yycheck[] =
{
      19,    45,    21,    22,    26,    45,     3,    26,    48,    28,
       4,    30,     6,     7,    28,    28,    35,    36,    37,    38,
      18,     0,    36,    36,    23,    19,    28,    28,    27,    27,
       7,    70,    28,    72,    36,    36,    70,    20,    72,    33,
      36,    55,    55,    62,    63,    45,    45,    69,    69,    47,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    22,    71,
      71,    65,    45,    50,    93,    94,     5,    23,    18,     8,
       9,    68,   101,   102,   103,    45,    15,    16,    17,    87,
      88,    20,    68,    69,    92,    24,    25,    95,    70,    45,
      72,    45,    31,    55,    60,    34,    60,    61,    26,    68,
      60,    55,     2,    11,    49,   134,    45,    -1,    47,    48,
      49,    65,   141,    45,    68,   144,   145,   146,    -1,    58,
      59,    -1,    -1,    55,   104,    -1,    65,    66,    -1,   158,
     159,    -1,    71,    65,   142,     5,    68,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    15,    16,    17,   156,    -1,
      20,    -1,    -1,    -1,    24,    25,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     5,    -1,    -1,    45,     9,    47,    48,    49,
      -1,    -1,    15,    16,    17,    -1,    -1,    20,    58,    59,
      -1,    24,    10,    -1,    -1,    65,    66,    -1,    31,    -1,
      -1,    34,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    47,    48,    49,    10,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    22,
      -1,    -1,    65,    66,    52,    -1,    -1,    55,    56,    57,
      58,    59,    60,    61,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    10,    -1,    52,
      -1,    -1,    55,    56,    57,    58,    59,    60,    61,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    11,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    22,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    55,    56,    57,    58,    59,    60,    61,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    11,    52,    -1,    -1,    55,    56,    57,
      58,    59,    60,    61,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    11,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    55,    56,    57,
      58,    59,    60,    61,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      12,    -1,    55,    56,    57,    58,    59,    60,    61,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    55,    56,    57,    58,    59,    60,    61,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    13,    -1,    55,    56,
      57,    58,    59,    60,    61,    22,    -1,    14,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    22,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    55,    56,
      57,    58,    59,    60,    61,    52,    -1,    -1,    55,    56,
      57,    58,    59,    60,    61,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      22,    -1,    -1,    -1,    -1,    52,    -1,    -1,    55,    56,
      57,    58,    59,    60,    61,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    55,    56,    57,    58,    59,    60,    61,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    61,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    22,    55,    56,    57,    58,    59,    60,    61,
      37,    -1,    39,    40,    41,    42,    43,    -1,    -1,    39,
      40,    41,    42,    43,    -1,    22,    -1,    -1,    55,    56,
      57,    58,    59,    60,    61,    55,    56,    57,    58,    59,
      60,    61,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    61
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    74,    75,     0,    20,    76,    23,    27,    45,    78,
      45,    78,    45,    55,    65,    68,    80,    77,    68,    69,
      77,     5,     8,     9,    15,    16,    17,    24,    25,    31,
      34,    45,    47,    48,    49,    58,    59,    65,    66,    76,
      82,    45,     4,     6,     7,    19,    33,    65,    84,    79,
       3,    84,    82,    82,    82,    45,    48,    45,    82,    84,
      82,    82,    69,    83,    82,    82,    71,    82,    82,    18,
      22,    37,    38,    39,    40,    41,    42,    43,    44,    52,
      55,    56,    57,    58,    59,    60,    61,    68,    26,    69,
      84,    28,    36,    55,    55,    68,    80,    78,    81,    14,
      45,    55,    29,    10,    82,    82,    71,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    84,    84,    60,    71,    84,
      82,    82,    84,    70,    72,    82,    82,    82,    81,    71,
      85,    55,    68,    82,    12,    30,    13,    11,    70,    70,
      72,    82,    84,    82,    82,    82,    26,    60,    10,    10,
      84,    82,    82,    11,    11
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    73,    74,    75,    75,    76,    76,    77,    77,    78,
      78,    78,    78,    78,    78,    78,    78,    79,    79,    80,
      80,    81,    81,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    83,    83,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    85,    85
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     4,     3,     0,     3,     3,
       5,     7,     5,     2,     4,     6,     8,     0,     2,     1,
       5,     0,     3,     1,     1,     1,     1,     1,     2,     3,
       2,     5,     2,     3,     2,     2,     3,     3,     4,     6,
       5,     9,     9,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     2,     1,     1,     1,     1,
       3,     3,     2,     3,     7,     0,     3
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
  case 2: /* program: letdef_list  */
#line 120 "./src/parser.y"
                { std::cout << "AST: " << *(yyvsp[0].letdef_list) << std::endl; }
#line 1368 "./src/parser.cpp"
    break;

  case 3: /* letdef_list: %empty  */
#line 124 "./src/parser.y"
                        { (yyval.letdef_list) = new Block<LetDef>(); }
#line 1374 "./src/parser.cpp"
    break;

  case 4: /* letdef_list: letdef_list letdef  */
#line 125 "./src/parser.y"
                        { (yyvsp[-1].letdef_list)->append((yyvsp[0].let_def)); }
#line 1380 "./src/parser.cpp"
    break;

  case 5: /* letdef: "let" "rec" def def_list  */
#line 129 "./src/parser.y"
                                { (yyvsp[0].def_list)->insert((yyvsp[0].def_list)->begin(), (yyvsp[-1].def)); (yyval.let_def) = new LetDef((yyvsp[0].def_list), LetType::Rec); }
#line 1386 "./src/parser.cpp"
    break;

  case 6: /* letdef: "let" def def_list  */
#line 130 "./src/parser.y"
                                { (yyvsp[0].def_list)->insert((yyvsp[0].def_list)->begin(), (yyvsp[-1].def)); (yyval.let_def) = new LetDef((yyvsp[0].def_list), LetType::NoRec); }
#line 1392 "./src/parser.cpp"
    break;

  case 7: /* def_list: %empty  */
#line 134 "./src/parser.y"
                        { (yyval.def_list) = new Block<Def>(); }
#line 1398 "./src/parser.cpp"
    break;

  case 8: /* def_list: def_list "and" def  */
#line 135 "./src/parser.y"
                        { (yyvsp[-2].def_list)->append((yyvsp[0].def)); }
#line 1404 "./src/parser.cpp"
    break;

  case 9: /* def: T_ID '=' expr  */
#line 139 "./src/parser.y"
                                                            { (yyval.def) = new ConstDef((yyvsp[-2].id), (yyvsp[0].expr)); }
#line 1410 "./src/parser.cpp"
    break;

  case 10: /* def: T_ID ':' type '=' expr  */
#line 140 "./src/parser.y"
                                                            { (yyval.def) = new ConstDef((yyvsp[-4].id), (yyvsp[-2].type), (yyvsp[0].expr)); }
#line 1416 "./src/parser.cpp"
    break;

  case 11: /* def: T_ID par par_list ':' type '=' expr  */
#line 141 "./src/parser.y"
                                                            { (yyvsp[-4].par_list)->insert((yyvsp[-4].par_list)->begin(), (yyvsp[-5].par)); (yyval.def) = new FunctionDef((yyvsp[-6].id), (yyvsp[-4].par_list), (yyvsp[0].expr), (yyvsp[-2].type)); }
#line 1422 "./src/parser.cpp"
    break;

  case 12: /* def: T_ID par par_list '=' expr  */
#line 142 "./src/parser.y"
                                                            { (yyvsp[-2].par_list)->insert((yyvsp[-2].par_list)->begin(), (yyvsp[-3].par)); (yyval.def) = new FunctionDef((yyvsp[-4].id), (yyvsp[-2].par_list), (yyvsp[0].expr)); }
#line 1428 "./src/parser.cpp"
    break;

  case 13: /* def: "mutable" T_ID  */
#line 143 "./src/parser.y"
                                                            { (yyval.def) = new VarDef((yyvsp[0].id)); }
#line 1434 "./src/parser.cpp"
    break;

  case 14: /* def: "mutable" T_ID ':' type  */
#line 144 "./src/parser.y"
                                                            { (yyval.def) = new VarDef((yyvsp[-2].id), (yyvsp[0].type)); }
#line 1440 "./src/parser.cpp"
    break;

  case 15: /* def: "mutable" T_ID '[' expr expr_comma_list ']'  */
#line 145 "./src/parser.y"
                                                            { (yyvsp[-1].expr_comma_list)->insert((yyvsp[-1].expr_comma_list)->begin(), (yyvsp[-2].expr)); (yyval.def) = new ArrayDef((yyvsp[-4].id), (yyvsp[-1].expr_comma_list)); }
#line 1446 "./src/parser.cpp"
    break;

  case 16: /* def: "mutable" T_ID '[' expr expr_comma_list ']' ':' type  */
#line 146 "./src/parser.y"
                                                            { (yyvsp[-3].expr_comma_list)->insert((yyvsp[-3].expr_comma_list)->begin(), (yyvsp[-4].expr)); (yyval.def) = new ArrayDef((yyvsp[-6].id), (yyvsp[-3].expr_comma_list), (yyvsp[0].type)); }
#line 1452 "./src/parser.cpp"
    break;

  case 17: /* par_list: %empty  */
#line 150 "./src/parser.y"
                    { (yyval.par_list) = new Block<Par>(); }
#line 1458 "./src/parser.cpp"
    break;

  case 18: /* par_list: par_list par  */
#line 151 "./src/parser.y"
                    { (yyvsp[-1].par_list)->append((yyvsp[0].par)); }
#line 1464 "./src/parser.cpp"
    break;

  case 19: /* par: T_ID  */
#line 155 "./src/parser.y"
                            { (yyval.par) = new Par((yyvsp[0].id)); }
#line 1470 "./src/parser.cpp"
    break;

  case 20: /* par: '(' T_ID ':' type ')'  */
#line 156 "./src/parser.y"
                            { (yyval.par) = new Par((yyvsp[-3].id), (yyvsp[-1].type)); }
#line 1476 "./src/parser.cpp"
    break;

  case 21: /* expr_comma_list: %empty  */
#line 160 "./src/parser.y"
                                { (yyval.expr_comma_list) = new Block<Expr>(); }
#line 1482 "./src/parser.cpp"
    break;

  case 22: /* expr_comma_list: expr_comma_list ',' expr  */
#line 161 "./src/parser.y"
                                { (yyvsp[-2].expr_comma_list)->append((yyvsp[0].expr)); }
#line 1488 "./src/parser.cpp"
    break;

  case 23: /* expr: T_CONST_INT  */
#line 165 "./src/parser.y"
                                                            { (yyval.expr) = new Int((yyvsp[0].number)); }
#line 1494 "./src/parser.cpp"
    break;

  case 24: /* expr: T_CONST_CHAR  */
#line 166 "./src/parser.y"
                                                            { (yyval.expr) = new Char((yyvsp[0].const_char)); }
#line 1500 "./src/parser.cpp"
    break;

  case 25: /* expr: T_STRING_LITERAL  */
#line 167 "./src/parser.y"
                                                            { (yyval.expr) = new String((yyvsp[0].string_literal)); }
#line 1506 "./src/parser.cpp"
    break;

  case 26: /* expr: "true"  */
#line 168 "./src/parser.y"
                                                            { (yyval.expr) = new Bool(true); }
#line 1512 "./src/parser.cpp"
    break;

  case 27: /* expr: "false"  */
#line 169 "./src/parser.y"
                                                            { (yyval.expr) = new Bool(false); }
#line 1518 "./src/parser.cpp"
    break;

  case 28: /* expr: '(' ')'  */
#line 170 "./src/parser.y"
                                                            { (yyval.expr) = new Unit(); }
#line 1524 "./src/parser.cpp"
    break;

  case 29: /* expr: '(' expr ')'  */
#line 171 "./src/parser.y"
                                                            { (yyval.expr) = (yyvsp[-1].expr); }
#line 1530 "./src/parser.cpp"
    break;

  case 30: /* expr: T_ID expr_list  */
#line 172 "./src/parser.y"
                                                            { (yyval.expr) = new FunctionCall((yyvsp[-1].id), (yyvsp[0].expr_list)); }
#line 1536 "./src/parser.cpp"
    break;

  case 31: /* expr: T_ID '[' expr expr_comma_list ']'  */
#line 173 "./src/parser.y"
                                                            { (yyvsp[-1].expr_comma_list)->insert((yyvsp[-1].expr_comma_list)->begin(), (yyvsp[-2].expr)); (yyval.expr) = new ArrayIndex((yyvsp[-4].id), (yyvsp[-1].expr_comma_list)); }
#line 1542 "./src/parser.cpp"
    break;

  case 32: /* expr: "dim" T_ID  */
#line 174 "./src/parser.y"
                                                            { (yyval.expr) = new Dim((yyvsp[0].id)); }
#line 1548 "./src/parser.cpp"
    break;

  case 33: /* expr: "dim" T_CONST_INT T_ID  */
#line 175 "./src/parser.y"
                                                            { (yyval.expr) = new Dim((yyvsp[0].id), (yyvsp[-1].number)); }
#line 1554 "./src/parser.cpp"
    break;

  case 34: /* expr: "new" type  */
#line 176 "./src/parser.y"
                                                            { (yyval.expr) = new New((yyvsp[0].type)); }
#line 1560 "./src/parser.cpp"
    break;

  case 35: /* expr: "delete" expr  */
#line 177 "./src/parser.y"
                                                            { (yyval.expr) = new Delete((yyvsp[0].expr)); }
#line 1566 "./src/parser.cpp"
    break;

  case 36: /* expr: letdef "in" expr  */
#line 178 "./src/parser.y"
                                                            { (yyval.expr) = new LetIn((yyvsp[-2].let_def), (yyvsp[0].expr)); }
#line 1572 "./src/parser.cpp"
    break;

  case 37: /* expr: "begin" expr "end"  */
#line 179 "./src/parser.y"
                                                            { (yyval.expr) = (yyvsp[-1].expr); }
#line 1578 "./src/parser.cpp"
    break;

  case 38: /* expr: "if" expr "then" expr  */
#line 180 "./src/parser.y"
                                                            { (yyval.expr) = new If((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1584 "./src/parser.cpp"
    break;

  case 39: /* expr: "if" expr "then" expr "else" expr  */
#line 181 "./src/parser.y"
                                                            { (yyval.expr) = new If((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1590 "./src/parser.cpp"
    break;

  case 40: /* expr: "while" expr "do" expr "done"  */
#line 182 "./src/parser.y"
                                                            { (yyval.expr) = new While((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 1596 "./src/parser.cpp"
    break;

  case 41: /* expr: "for" T_ID '=' expr "to" expr "do" expr "done"  */
#line 183 "./src/parser.y"
                                                            { (yyval.expr) = new ForTo((yyvsp[-7].id), (yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 1602 "./src/parser.cpp"
    break;

  case 42: /* expr: "for" T_ID '=' expr "downto" expr "do" expr "done"  */
#line 184 "./src/parser.y"
                                                            { (yyval.expr) = new ForDownTo((yyvsp[-7].id), (yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 1608 "./src/parser.cpp"
    break;

  case 43: /* expr: '+' expr  */
#line 185 "./src/parser.y"
                                                            { (yyval.expr) = new UnOp((yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1614 "./src/parser.cpp"
    break;

  case 44: /* expr: '-' expr  */
#line 186 "./src/parser.y"
                                                            { (yyval.expr) = new UnOp((yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1620 "./src/parser.cpp"
    break;

  case 45: /* expr: '!' expr  */
#line 187 "./src/parser.y"
                                                            { (yyval.expr) = new UnOp((yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1626 "./src/parser.cpp"
    break;

  case 46: /* expr: "not" expr  */
#line 188 "./src/parser.y"
                                                            { (yyval.expr) = new UnOp((yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1632 "./src/parser.cpp"
    break;

  case 47: /* expr: expr '+' expr  */
#line 189 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1638 "./src/parser.cpp"
    break;

  case 48: /* expr: expr '-' expr  */
#line 190 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1644 "./src/parser.cpp"
    break;

  case 49: /* expr: expr '*' expr  */
#line 191 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1650 "./src/parser.cpp"
    break;

  case 50: /* expr: expr '/' expr  */
#line 192 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1656 "./src/parser.cpp"
    break;

  case 51: /* expr: expr '=' expr  */
#line 193 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1662 "./src/parser.cpp"
    break;

  case 52: /* expr: expr "<>" expr  */
#line 194 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1668 "./src/parser.cpp"
    break;

  case 53: /* expr: expr '<' expr  */
#line 195 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1674 "./src/parser.cpp"
    break;

  case 54: /* expr: expr '>' expr  */
#line 196 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1680 "./src/parser.cpp"
    break;

  case 55: /* expr: expr "<=" expr  */
#line 197 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1686 "./src/parser.cpp"
    break;

  case 56: /* expr: expr ">=" expr  */
#line 198 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1692 "./src/parser.cpp"
    break;

  case 57: /* expr: expr "==" expr  */
#line 199 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1698 "./src/parser.cpp"
    break;

  case 58: /* expr: expr "!=" expr  */
#line 200 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1704 "./src/parser.cpp"
    break;

  case 59: /* expr: expr "&&" expr  */
#line 201 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1710 "./src/parser.cpp"
    break;

  case 60: /* expr: expr "||" expr  */
#line 202 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1716 "./src/parser.cpp"
    break;

  case 61: /* expr: expr ';' expr  */
#line 203 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1722 "./src/parser.cpp"
    break;

  case 62: /* expr: expr ":=" expr  */
#line 204 "./src/parser.y"
                                                            { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].op)); }
#line 1728 "./src/parser.cpp"
    break;

  case 64: /* expr_list: %empty  */
#line 209 "./src/parser.y"
                                    { (yyval.expr_list) = new Block<Expr>(); }
#line 1734 "./src/parser.cpp"
    break;

  case 65: /* expr_list: expr_list expr  */
#line 210 "./src/parser.y"
                                    { (yyvsp[-1].expr_list)->append((yyvsp[0].expr)); }
#line 1740 "./src/parser.cpp"
    break;

  case 66: /* type: "unit"  */
#line 213 "./src/parser.y"
                                                    { (yyval.type) = new Type(TypeTag::Unit); }
#line 1746 "./src/parser.cpp"
    break;

  case 67: /* type: "int"  */
#line 214 "./src/parser.y"
                                                    { (yyval.type) = new Type(TypeTag::Int); }
#line 1752 "./src/parser.cpp"
    break;

  case 68: /* type: "char"  */
#line 215 "./src/parser.y"
                                                    { (yyval.type) = new Type(TypeTag::Char); }
#line 1758 "./src/parser.cpp"
    break;

  case 69: /* type: "bool"  */
#line 216 "./src/parser.y"
                                                    { (yyval.type) = new Type(TypeTag::Bool); }
#line 1764 "./src/parser.cpp"
    break;

  case 70: /* type: '(' type ')'  */
#line 217 "./src/parser.y"
                                                    { (yyval.type) = (yyvsp[-1].type); }
#line 1770 "./src/parser.cpp"
    break;

  case 71: /* type: type "->" type  */
#line 218 "./src/parser.y"
                                                    { (yyval.type) = new FunctionType((yyvsp[-2].type), (yyvsp[0].type)); }
#line 1776 "./src/parser.cpp"
    break;

  case 72: /* type: type "ref"  */
#line 219 "./src/parser.y"
                                                    { (yyval.type) = new RefType((yyvsp[-1].type)); }
#line 1782 "./src/parser.cpp"
    break;

  case 73: /* type: "array" "of" type  */
#line 220 "./src/parser.y"
                                                    { (yyval.type) = new ArrayType((yyvsp[0].type)); }
#line 1788 "./src/parser.cpp"
    break;

  case 74: /* type: "array" '[' '*' asterisk_list ']' "of" type  */
#line 221 "./src/parser.y"
                                                    { (yyvsp[-3].dimension_count)++; (yyval.type) = new ArrayType((yyvsp[0].type), (yyvsp[-3].dimension_count)); }
#line 1794 "./src/parser.cpp"
    break;

  case 75: /* asterisk_list: %empty  */
#line 227 "./src/parser.y"
                            { (yyval.dimension_count) = 0; }
#line 1800 "./src/parser.cpp"
    break;

  case 76: /* asterisk_list: asterisk_list ',' '*'  */
#line 228 "./src/parser.y"
                            { (yyvsp[-2].dimension_count)++; }
#line 1806 "./src/parser.cpp"
    break;


#line 1810 "./src/parser.cpp"

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

#line 231 "./src/parser.y"


int main(){
    int result = yyparse();
    if(result == 0) 
        printf("Success.\n");
    return result;
}

void yyerror(const char* msg){
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}