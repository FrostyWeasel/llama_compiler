%{
#include <cstdlib>
#include <string>
#include "constructor.hpp"
#include "pattern.hpp"
#include "clause.hpp"
#include "int_pattern.hpp"
#include "float_pattern.hpp"
#include "bool_pattern.hpp"
#include "id_pattern.hpp"
#include "match.hpp"
#include "definition.hpp"
#include "type_def.hpp"
#include "t_def.hpp"
#include "includes.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#define T_EOF           0

char get_ascii(const char* hex){
    char res = 0;

    for(int i = 0; i < 2; i++){
        char ch = *hex++;
        char tmp = 0;

        if (ch >= '0' && ch <= '9')
            tmp = ch - '0';
        if (ch >= 'A' && ch <= 'F')
            tmp = ch - 'A' + 10;
        if (ch >= 'a' && ch <= 'f')
            tmp = ch - 'a' + 10;

        res = tmp + res * i * 16;
    }
    return res;
}

std::string* fixEscape(char* original){
	std::string* fixed = new std::string();
	for (int i=1; original[i] != '\0'; ++i) {
		char c = original[i];
		if (c != '\\') fixed->push_back(c);
		else {
			c = original[++i];
			switch(c) {
				case 'n':
					fixed->push_back('\n');
					break;
				case 't':
					fixed->push_back('\t');
					break;
				case 'r':
					fixed->push_back('\r');
					break;
				case '0':
					fixed->push_back('\0');
					break;
				case '\\':
					fixed->push_back('\\');
					break;
				case '\'':
					fixed->push_back('\'');
					break;
				case '\"':
					fixed->push_back('\"');
					break;
				case 'x':
					++i;
					fixed->push_back(get_ascii(original+i));
					++i;
					break;
				default:
					break;
			}
		}
	}
	fixed->pop_back();
	return fixed;
}

char get_char(const char* char_read){
    if(char_read[1] != '\\') return char_read[1];

    switch(char_read[2]){
        case 'n':
            return '\n';
            break;
        case 't':
            return '\t';
            break;
        case 'r':
            return '\r';
            break;
        case '0':
            return '\0';
            break;
        case '\\':
            return '\\';
            break;
        case '\'':
            return '\'';
            break;
        case '\"':
            return '\"';
            break;
        case 'x':
            return get_ascii(char_read + 3);
            break;
        default:
            return -1;
            break;
    }

}
%}

L [a-zA-Z]
L_lower [a-z]
L_upper [A-Z]
D [0-9]
W [ \t\n\r]

%option 8bit
%option noyywrap
%option yylineno

/* %x STRING_LITERAL */
%x MULTILINE_COMMENT

%%

    int comment_nesting = 0;

"and"		{ return T_AND; }
"array"		{ return T_ARRAY; }
"begin"		{ return T_BEGIN; }
"bool"		{ return T_BOOL; }
"char"		{ return T_CHAR; }
"delete"	{ return T_DELETE; }
"dim"		{ return T_DIM; }
"do"		{ return T_DO; }
"done"		{ return T_DONE; }
"downto"	{ return T_DOWNTO; }
"else"		{ return T_ELSE; }
"end"		{ return T_END; }
"false"		{ return T_FALSE; }
"for"		{ return T_FOR; }
"if"		{ return T_IF; }
"in"		{ return T_IN; }
"int"		{ return T_INT; }        
"let"		{ return T_LET; }
"match"		{ return T_MATCH; }
"mutable"	{ return T_MUTABLE; }
"new"		{ return T_NEW; }
"not"		{ return T_NOT; }
"of"		{ return T_OF; }
"rec"		{ return T_REC; }
"ref"		{ return T_REF; }
"then"		{ return T_THEN; }
"to"		{ return T_TO; }
"true"		{ return T_TRUE; }
"type"		{ return T_TYPE; }
"unit"		{ return T_UNIT; }
"while"		{ return T_WHILE; }
"with"		{ return T_WITH; }

"mod"		{ yylval.op = OpType::Modulo; return T_MOD; }

[\|\(\)\[\]\,\:]		{ return yytext[0]; }

"+"     { yylval.op = OpType::Plus; return yytext[0]; }
"-"     { yylval.op = OpType::Minus; return yytext[0]; }
"*"     { yylval.op = OpType::Times; return yytext[0]; }
"/"     { yylval.op = OpType::Divide; return yytext[0]; }
"="     { yylval.op = OpType::Equals; return yytext[0]; }
"<"     { yylval.op = OpType::LessThan; return yytext[0]; }
">"     { yylval.op = OpType::GreaterThan; return yytext[0]; }
"!"     { yylval.op = OpType::Dereference; return yytext[0]; }
";"     { yylval.op = OpType::Concat; return yytext[0]; }

"+."    { yylval.op = OpType::PlusFloat; return T_PLUS_FLOAT; }
"-."    { yylval.op = OpType::MinusFloat; return T_MINUS_FLOAT; }
"*."    { yylval.op = OpType::TimesFloat; return T_TIMES_FLOAT; }
"/."    { yylval.op = OpType::DivideFloat; return T_DIVIDE_FLOAT; }
"**"    { yylval.op = OpType::ExponentiateFloat; return T_EXPONENTIATE_FLOAT; }

"->"		{ return T_TYPE_ARROW_OP; }
"&&"		{ yylval.op = OpType::And; return T_AND_OP; }
"||"		{ yylval.op = OpType::Or; return T_OR_OP; }
"<>"		{ yylval.op = OpType::NotEquals; return T_NOT_EQ_OP; }
"<="		{ yylval.op = OpType::LessOrEqualThan; return T_LESS_THAN_OR_EQ_OP; }
">="		{ yylval.op = OpType::GreaterOrEqualThan; return T_GREATER_THAN_OR_EQ_OP; }
"=="		{ yylval.op = OpType::NatEquals; return T_NAT_EQ_OP; }
"!="		{ yylval.op = OpType::NatNotEquals; return T_NAT_NOT_EQ_OP; }
":="		{ yylval.op = OpType::Assign; return T_ASSIGNMENT_OP; }

{L_lower}({L}|{D}|_)*       { std::string* id = new std::string(yytext); yylval.id = id; return T_ID; }
{L_upper}({L}|{D}|_)*       { std::string* id = new std::string(yytext); yylval.id = id; return T_CONSTRUCTOR_ID; }

{D}+{L}+    { fprintf(stderr, "Invalid suffix of integer number\n"); exit(1); }
{D}+        { yylval.number = atoi(yytext); return T_CONST_INT; }

{D}+\.{D}+([eE][\+\-]?{D}+)?{L}+    { fprintf(stderr, "Invalid suffix of floating point number\n"); exit(1);  }
{D}+\.{D}+([eE][\+\-]?{D}+)?        { yylval.float_value = atof(yytext); return T_CONST_FLOAT; }

\'([^\'\"\\]|\\n|\\t|\\r|\\0|\\\\|\\\'|\\\"|\\x({D}|[A-Fa-f])({D}|[A-Fa-f]))\' { yylval.const_char = get_char(yytext); return T_CONST_CHAR; }

\"([^\n\r\"]|\\\")*\" { std::string* str = fixEscape(yytext) ; yylval.string_literal = str; return T_STRING_LITERAL; }

{W}+        { /* nothing */ }   /*White space*/

--.*\n      { /* nothing */ }   /*One line comment*/

"(*"                        { BEGIN(MULTILINE_COMMENT); }
<MULTILINE_COMMENT>"(*"     { ++comment_nesting; }
<MULTILINE_COMMENT>"*)"     { if (comment_nesting != 0) --comment_nesting; else BEGIN(INITIAL); }
<MULTILINE_COMMENT>"*"      { /* nothing */ }
<MULTILINE_COMMENT>"("      { /* nothing */ } 
<MULTILINE_COMMENT>[^\(\*]+ { /* nothing */ }
<MULTILINE_COMMENT><<EOF>>  { fprintf(stderr, "EOF reached with open comment\n"); exit(1);}

.       { fprintf(stderr, "Illegal character: \"%c\" (ASCII: %d) at line %d\n", yytext[0], yytext[0], yylineno); exit(1); }
