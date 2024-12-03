/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TM_NAT = 258,
     TM_IDENT = 259,
     TM_LEFT_BRACE = 260,
     TM_RIGHT_BRACE = 261,
     TM_LEFT_BRACKET = 262,
     TM_RIGHT_BRACKET = 263,
     TM_LEFT_PAREN = 264,
     TM_RIGHT_PAREN = 265,
     TM_SEMICOL = 266,
     TM_COMMA = 267,
     TM_MALLOC = 268,
     TM_RI = 269,
     TM_RC = 270,
     TM_WI = 271,
     TM_WC = 272,
     TM_VAR = 273,
     TM_IF = 274,
     TM_THEN = 275,
     TM_ELSE = 276,
     TM_WHILE = 277,
     TM_DO = 278,
     TM_CHAR = 279,
     TM_ASGNOP = 280,
     TM_OR = 281,
     TM_AND = 282,
     TM_NOT = 283,
     TM_LT = 284,
     TM_LE = 285,
     TM_GT = 286,
     TM_GE = 287,
     TM_EQ = 288,
     TM_NE = 289,
     TM_PLUS = 290,
     TM_MINUS = 291,
     TM_MUL = 292,
     TM_DIV = 293,
     TM_MOD = 294,
     TM_SINGLE_CHAR = 295,
     TM_STRING = 296
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 11 "lang.y"

unsigned int n;
char * i;
struct expr * e;
struct cmd * c;
void * none;
// 初始化列表字段
struct init_list *init_list; 
// 表达式列表字段
struct expr_list *e_list; 
// 单个字符字段
char *single_char;
// 多变量声明列表字段
struct var_decl_list *var_list;
// 变量声明字段
struct var_decl var_decl;
// 多维数组索引字段
struct expr_list *sizes; 


/* Line 2058 of yacc.c  */
#line 119 "parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_H_INCLUDED  */
