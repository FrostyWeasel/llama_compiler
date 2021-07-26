/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_HPP_INCLUDED
# define YY_YY_SRC_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_AND = 258,                   /* "and"  */
    T_ARRAY = 259,                 /* "array"  */
    T_BEGIN = 260,                 /* "begin"  */
    T_BOOL = 261,                  /* "bool"  */
    T_CHAR = 262,                  /* "char"  */
    T_DELETE = 263,                /* "delete"  */
    T_DIM = 264,                   /* "dim"  */
    T_DO = 265,                    /* "do"  */
    T_DONE = 266,                  /* "done"  */
    T_DOWNTO = 267,                /* "downto"  */
    T_ELSE = 268,                  /* "else"  */
    T_END = 269,                   /* "end"  */
    T_FALSE = 270,                 /* "false"  */
    T_FOR = 271,                   /* "for"  */
    T_IF = 272,                    /* "if"  */
    T_IN = 273,                    /* "in"  */
    T_INT = 274,                   /* "int"  */
    T_LET = 275,                   /* "let"  */
    T_MATCH = 276,                 /* "match"  */
    T_MOD = 277,                   /* "mod"  */
    T_MUTABLE = 278,               /* "mutable"  */
    T_NEW = 279,                   /* "new"  */
    T_NOT = 280,                   /* "not"  */
    T_OF = 281,                    /* "of"  */
    T_REC = 282,                   /* "rec"  */
    T_REF = 283,                   /* "ref"  */
    T_THEN = 284,                  /* "then"  */
    T_TO = 285,                    /* "to"  */
    T_TRUE = 286,                  /* "true"  */
    T_TYPE = 287,                  /* "type"  */
    T_UNIT = 288,                  /* "unit"  */
    T_WHILE = 289,                 /* "while"  */
    T_WITH = 290,                  /* "with"  */
    T_TYPE_ARROW_OP = 291,         /* "->"  */
    T_AND_OP = 292,                /* "&&"  */
    T_OR_OP = 293,                 /* "||"  */
    T_NOT_EQ_OP = 294,             /* "<>"  */
    T_LESS_THAN_OR_EQ_OP = 295,    /* "<="  */
    T_GREATER_THAN_OR_EQ_OP = 296, /* ">="  */
    T_NAT_EQ_OP = 297,             /* "=="  */
    T_NAT_NOT_EQ_OP = 298,         /* "!="  */
    T_ASSIGNMENT_OP = 299,         /* ":="  */
    T_ID = 300,                    /* T_ID  */
    T_CONSTRUCTOR_ID = 301,        /* T_CONSTRUCTOR_ID  */
    T_CONST_CHAR = 302,            /* T_CONST_CHAR  */
    T_CONST_INT = 303,             /* T_CONST_INT  */
    T_STRING_LITERAL = 304,        /* T_STRING_LITERAL  */
    IF_THEN = 305,                 /* IF_THEN  */
    IF_THEN_ELSE = 306,            /* IF_THEN_ELSE  */
    UNOP = 308                     /* UNOP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 83 "./src/parser.y"

    LetDef* let_def;
    Def* def;
    Par* par;
    Expr* expr;
    TypeVariable* type;
    Block<Expr>* func_expr_list;
    Block<Expr>* expr_comma_list;
    Block<Par>* par_list;
    Block<Def>* def_list;
    Block<LetDef>* letdef_list;
    OpType op;

    std::string* id;
    std::string* string_literal;
    char const_char;
    int number;
    unsigned int dimension_count;

#line 136 "./src/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_HPP_INCLUDED  */
