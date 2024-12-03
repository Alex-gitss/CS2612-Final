/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "lang.y"

	// this part is copied to the beginning of the parser 
	#include <stdio.h>
	#include "lang.h"
	#include "lexer.h"
	void yyerror(char *);
	int yylex(void);
        struct cmd * root;

/* Line 371 of yacc.c  */
#line 78 "parser.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
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
/* Line 387 of yacc.c  */
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


/* Line 387 of yacc.c  */
#line 183 "parser.c"
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 211 "parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  39
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   382

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNRULES -- Number of states.  */
#define YYNSTATES  138

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    14,    15,    17,    21,
      23,    27,    31,    33,    37,    41,    46,    48,    52,    55,
      60,    63,    65,    69,    73,    77,    88,    95,   100,   105,
     114,   117,   122,   128,   136,   144,   147,   149,   153,   155,
     157,   159,   163,   167,   172,   175,   178,   181,   186,   188,
     192,   196,   200,   204,   208,   212,   216,   220,   224,   228,
     232,   236
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    52,    -1,    37,    -1,    37,    44,    -1,
       5,    46,     6,    -1,    -1,    54,    -1,    46,    12,    54,
      -1,    45,    -1,    46,    12,    45,    -1,     5,    48,     6,
      -1,    40,    -1,    48,    12,    40,    -1,     7,    54,     8,
      -1,    49,     7,    54,     8,    -1,     4,    -1,     4,    25,
      54,    -1,     4,    49,    -1,     4,    49,    25,    45,    -1,
      44,     4,    -1,    50,    -1,    51,    12,    50,    -1,    54,
      25,    54,    -1,    52,    11,    52,    -1,    19,    54,    20,
       5,    52,     6,    21,     5,    52,     6,    -1,    22,    54,
      23,     5,    52,     6,    -1,    16,     9,    54,    10,    -1,
      17,     9,    54,    10,    -1,    18,    44,     4,    25,    13,
       9,    54,    10,    -1,    24,     4,    -1,    24,     4,    25,
      40,    -1,    24,     4,     7,    54,     8,    -1,    24,     4,
       7,    54,     8,    25,    41,    -1,    24,     4,     7,    54,
       8,    25,    47,    -1,    18,    51,    -1,     3,    -1,     9,
      54,    10,    -1,     4,    -1,    40,    -1,    41,    -1,    14,
       9,    10,    -1,    15,     9,    10,    -1,    13,     9,    54,
      10,    -1,    28,    53,    -1,    36,    53,    -1,    37,    53,
      -1,    53,     7,    54,     8,    -1,    53,    -1,    54,    37,
      54,    -1,    54,    35,    54,    -1,    54,    36,    54,    -1,
      54,    38,    54,    -1,    54,    39,    54,    -1,    54,    29,
      54,    -1,    54,    31,    54,    -1,    54,    30,    54,    -1,
      54,    32,    54,    -1,    54,    33,    54,    -1,    54,    34,
      54,    -1,    54,    27,    54,    -1,    54,    26,    54,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    94,    94,   104,   109,   117,   126,   130,   135,   140,
     145,   153,   162,   167,   176,   181,   190,   195,   200,   205,
     210,   219,   224,   232,   236,   240,   244,   248,   252,   257,
     262,   266,   271,   276,   281,   286,   294,   298,   302,   307,
     312,   316,   320,   324,   328,   332,   336,   341,   348,   352,
     356,   360,   364,   368,   372,   376,   380,   384,   388,   392,
     396,   400
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TM_NAT", "TM_IDENT", "TM_LEFT_BRACE",
  "TM_RIGHT_BRACE", "TM_LEFT_BRACKET", "TM_RIGHT_BRACKET", "TM_LEFT_PAREN",
  "TM_RIGHT_PAREN", "TM_SEMICOL", "TM_COMMA", "TM_MALLOC", "TM_RI",
  "TM_RC", "TM_WI", "TM_WC", "TM_VAR", "TM_IF", "TM_THEN", "TM_ELSE",
  "TM_WHILE", "TM_DO", "TM_CHAR", "TM_ASGNOP", "TM_OR", "TM_AND", "TM_NOT",
  "TM_LT", "TM_LE", "TM_GT", "TM_GE", "TM_EQ", "TM_NE", "TM_PLUS",
  "TM_MINUS", "TM_MUL", "TM_DIV", "TM_MOD", "TM_SINGLE_CHAR", "TM_STRING",
  "$accept", "NT_WHOLE", "NT_PTR_LEVEL", "NT_INIT_LIST", "NT_EXPR_LIST",
  "NT_INIT_CHAR_LIST", "NT_CHAR_LIST", "NT_MULTI_ARR_SIZES", "NT_VAR_DECL",
  "NT_VAR_LIST", "NT_CMD", "NT_EXPR_2", "NT_EXPR", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    46,    46,    46,    46,
      46,    47,    48,    48,    49,    49,    50,    50,    50,    50,
      50,    51,    51,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     3,     0,     1,     3,     1,
       3,     3,     1,     3,     3,     4,     1,     3,     2,     4,
       2,     1,     3,     3,     3,    10,     6,     4,     4,     8,
       2,     4,     5,     7,     7,     2,     1,     3,     1,     1,
       1,     3,     3,     4,     2,     2,     2,     4,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    36,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    39,    40,     0,     2,
      48,     0,     0,     0,     0,     0,     0,     0,    16,     3,
       0,    21,    35,     0,     0,    30,    44,    45,    46,     1,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,     0,    41,    42,
       0,     0,     0,     0,    18,     4,    20,     0,     0,     0,
       0,     0,    24,     0,    23,    61,    60,    54,    56,    55,
      57,    58,    59,    50,    51,    49,    52,    53,    43,    27,
      28,     0,    17,     0,     0,     0,     0,    22,     0,     0,
       0,    31,    47,    14,     0,     6,    19,     0,    20,     0,
       0,    32,    15,     9,     0,     7,     0,     0,    26,     0,
       5,     0,     0,     0,     0,    33,    34,    10,     8,    29,
       0,    12,     0,     0,    11,     0,    25,    13
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    18,    30,   106,   114,   126,   132,    64,    31,    32,
      19,    20,    21
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -101
static const yytype_int16 yypact[] =
{
      60,  -101,  -101,   108,    -5,     5,     9,    25,    27,    -2,
     108,   108,    12,   108,   108,   108,  -101,  -101,    57,    47,
      58,   306,   190,   108,    56,    61,   108,   108,     2,    31,
      66,  -101,    68,   274,   291,     3,    58,    58,    58,  -101,
      60,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,  -101,   204,  -101,  -101,
     222,   236,   108,   108,     4,  -101,    62,    -2,    67,    76,
     108,    43,    47,   124,   320,  -101,  -101,     6,     6,     6,
       6,     6,     6,   334,   334,   348,   348,   348,  -101,  -101,
    -101,   138,   320,   108,    80,    73,    85,  -101,    60,    60,
     158,  -101,  -101,  -101,   172,   101,  -101,    82,  -101,    11,
      19,    69,  -101,  -101,     0,   320,   108,    71,  -101,    -4,
    -101,   101,   254,    90,    59,  -101,  -101,  -101,   320,  -101,
      60,  -101,     7,    20,  -101,    63,  -101,  -101
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -101,  -101,   -14,  -100,  -101,  -101,  -101,  -101,    40,  -101,
     -37,    41,    -3
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      22,   124,    28,    72,    23,   113,   120,    33,    34,    62,
      70,    93,   121,   134,    24,    65,    35,   117,    25,   135,
      57,   127,    40,    60,    61,   118,   136,    63,    71,    94,
      40,    40,    43,    44,    26,    29,    27,   125,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    96,    36,    37,    38,    39,    40,    91,
      92,   109,   110,     1,     2,    41,    58,   100,    29,     3,
      66,    59,    98,     4,     5,     6,     7,     8,     9,    10,
      67,    99,    11,   101,    12,   105,   107,    95,    13,   108,
     104,   116,   123,   133,   119,   130,    14,    15,     0,   131,
      16,    17,   115,   137,     1,     2,   105,    97,     0,     0,
       3,     1,     2,   122,     4,     5,     6,     3,   128,     0,
       0,     4,     5,     6,     0,     0,     0,     0,     0,    13,
       0,     0,   102,     0,     0,     0,    13,    14,    15,     0,
       0,    16,    17,     0,    14,    15,   103,     0,    16,    17,
      43,    44,     0,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    43,    44,   111,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,     0,     0,
     112,     0,     0,     0,    43,    44,     0,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    43,    44,
      56,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,     0,     0,    88,     0,    43,    44,     0,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      43,    44,    89,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,     0,     0,    90,     0,    43,    44,
       0,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    43,    44,   129,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,     0,     0,     0,     0,
      43,    44,     0,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    68,     0,     0,     0,     0,     0,
      43,    44,     0,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    69,     0,     0,    43,    44,     0,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    42,    43,    44,     0,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    43,    44,     0,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      43,    44,     0,    45,    46,    47,    48,    49,    50,     0,
       0,    53,    54,    55,    43,    44,     0,    45,    46,    47,
      48,    49,    50
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-101)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       3,     5,     4,    40,     9,   105,     6,    10,    11,     7,
       7,     7,    12,     6,     9,    29,     4,     6,     9,    12,
      23,   121,    11,    26,    27,     6,     6,    25,    25,    25,
      11,    11,    26,    27,     9,    37,     9,    41,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    67,    13,    14,    15,     0,    11,    62,
      63,    98,    99,     3,     4,     7,    10,    70,    37,     9,
       4,    10,     5,    13,    14,    15,    16,    17,    18,    19,
      12,     5,    22,    40,    24,     5,    13,    25,    28,     4,
      93,     9,    21,   130,    25,     5,    36,    37,    -1,    40,
      40,    41,   105,    40,     3,     4,     5,    67,    -1,    -1,
       9,     3,     4,   116,    13,    14,    15,     9,   121,    -1,
      -1,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,     8,    -1,    -1,    -1,    28,    36,    37,    -1,
      -1,    40,    41,    -1,    36,    37,     8,    -1,    40,    41,
      26,    27,    -1,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    26,    27,     8,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
       8,    -1,    -1,    -1,    26,    27,    -1,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    26,    27,
      10,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    10,    -1,    26,    27,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      26,    27,    10,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    10,    -1,    26,    27,
      -1,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    26,    27,    10,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      26,    27,    -1,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    20,    -1,    -1,    -1,    -1,    -1,
      26,    27,    -1,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    23,    -1,    -1,    26,    27,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    25,    26,    27,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    26,    27,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      26,    27,    -1,    29,    30,    31,    32,    33,    34,    -1,
      -1,    37,    38,    39,    26,    27,    -1,    29,    30,    31,
      32,    33,    34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     9,    13,    14,    15,    16,    17,    18,
      19,    22,    24,    28,    36,    37,    40,    41,    43,    52,
      53,    54,    54,     9,     9,     9,     9,     9,     4,    37,
      44,    50,    51,    54,    54,     4,    53,    53,    53,     0,
      11,     7,    25,    26,    27,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    10,    54,    10,    10,
      54,    54,     7,    25,    49,    44,     4,    12,    20,    23,
       7,    25,    52,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    10,    10,
      10,    54,    54,     7,    25,    25,    44,    50,     5,     5,
      54,    40,     8,     8,    54,     5,    45,    13,     4,    52,
      52,     8,     8,    45,    46,    54,     9,     6,     6,    25,
       6,    12,    54,    21,     5,    41,    47,    45,    54,    10,
       5,    40,    48,    52,     6,    12,     6,    40
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 95 "lang.y"
    {
    (yyval.c) = ((yyvsp[(1) - (1)].c));
    root = (yyval.c);
  }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 105 "lang.y"
    {
    (yyval.n) = 1;
  }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 110 "lang.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n) + 1;
  }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 118 "lang.y"
    {
        (yyval.init_list) = create_init_list((yyvsp[(2) - (3)].e_list));
    }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 126 "lang.y"
    {
        (yyval.e_list) = NULL;
    }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 131 "lang.y"
    {
        (yyval.e_list) = create_expr_list((yyvsp[(1) - (1)].e));
    }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 136 "lang.y"
    {
        (yyval.e_list) = append_to_expr_list((yyvsp[(1) - (3)].e_list), (yyvsp[(3) - (3)].e));
    }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 141 "lang.y"
    {
        (yyval.e_list) = create_expr_list(new_expr(T_INIT_LIST, (yyvsp[(1) - (1)].init_list)));
    }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 146 "lang.y"
    {
        (yyval.e_list) = append_to_expr_list((yyvsp[(1) - (3)].e_list), new_expr(T_INIT_LIST, (yyvsp[(3) - (3)].init_list)));
    }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 154 "lang.y"
    {
        (yyval.init_list) = create_init_list((yyvsp[(2) - (3)].e_list));
    }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 163 "lang.y"
    {
    (yyval.e_list) = create_expr_list(TChar((yyvsp[(1) - (1)].single_char)));
}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 168 "lang.y"
    {
    (yyval.e_list) = append_to_expr_list((yyvsp[(1) - (3)].e_list), TChar((yyvsp[(3) - (3)].single_char)));
}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 177 "lang.y"
    { 
    (yyval.sizes) = create_expr_list((yyvsp[(2) - (3)].e)); 
  }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 182 "lang.y"
    {  
    (yyval.sizes) = append_to_expr_list((yyvsp[(1) - (4)].sizes), (yyvsp[(3) - (4)].e)); 
  }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 191 "lang.y"
    {
    (yyval.var_decl) = (struct var_decl){ .name = (yyvsp[(1) - (1)].i), .type = VAR_SIMPLE, .sizes = NULL, .ptr_level = 0 };
  }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 196 "lang.y"
    {
    (yyval.var_decl) = (struct var_decl){ .name = (yyvsp[(1) - (3)].i), .type = VAR_SIMPLE, .init_expr = (yyvsp[(3) - (3)].e) };
  }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 201 "lang.y"
    {
    (yyval.var_decl) = (struct var_decl){ .name = (yyvsp[(1) - (2)].i), .type = VAR_ARRAY, .sizes = (yyvsp[(2) - (2)].sizes), .ptr_level = 0 };
  }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 206 "lang.y"
    {
    (yyval.var_decl) = (struct var_decl){ .name = (yyvsp[(1) - (4)].i), .type = VAR_ARRAY, .sizes = (yyvsp[(2) - (4)].sizes), .ptr_level = 0, .init_expr_list = (yyvsp[(4) - (4)].init_list) };
  }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 211 "lang.y"
    {
    (yyval.var_decl) = (struct var_decl){ .name = (yyvsp[(2) - (2)].i), .type = VAR_POINTER, .sizes = NULL, .ptr_level = (yyvsp[(1) - (2)].n) };
  }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 220 "lang.y"
    {
    (yyval.var_list) = create_var_decl_list((yyvsp[(1) - (1)].var_decl));
  }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 225 "lang.y"
    {
    (yyval.var_list) = append_to_var_decl_list((yyvsp[(1) - (3)].var_list), (yyvsp[(3) - (3)].var_decl));
  }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 233 "lang.y"
    {
    (yyval.c) = (TAsgn((yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 237 "lang.y"
    {
    (yyval.c) = (TSeq((yyvsp[(1) - (3)].c),(yyvsp[(3) - (3)].c)));
  }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 241 "lang.y"
    {
    (yyval.c) = (TIf((yyvsp[(2) - (10)].e),(yyvsp[(5) - (10)].c),(yyvsp[(9) - (10)].c)));
  }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 245 "lang.y"
    {
    (yyval.c) = (TWhile((yyvsp[(2) - (6)].e),(yyvsp[(5) - (6)].c)));
  }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 249 "lang.y"
    {
    (yyval.c) = (TWriteInt((yyvsp[(3) - (4)].e)));
  }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 253 "lang.y"
    {
    (yyval.c) = (TWriteChar((yyvsp[(3) - (4)].e)));
  }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 258 "lang.y"
    {
    // $2 是指针级别
    (yyval.c) = TPtrDecl((yyvsp[(3) - (8)].i), (yyvsp[(2) - (8)].n), (yyvsp[(7) - (8)].e)); 
  }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 263 "lang.y"
    {
    (yyval.c) = TCharDecl((yyvsp[(2) - (2)].i), NULL); // 创建一个不带初始化的字符变量声明
  }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 267 "lang.y"
    {
    (yyval.c) = TCharDecl((yyvsp[(2) - (4)].i), TChar((yyvsp[(4) - (4)].single_char))); // 创建一个带有初始化的字符变量声明
  }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 272 "lang.y"
    {
      (yyval.c) = TStringDecl_String((yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].e), NULL); 
  }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 277 "lang.y"
    {
      (yyval.c) = TStringDecl_String((yyvsp[(2) - (7)].i), (yyvsp[(4) - (7)].e), TString((yyvsp[(7) - (7)].i))); 
  }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 282 "lang.y"
    {
      (yyval.c) = TStringDecl_Array((yyvsp[(2) - (7)].i), (yyvsp[(4) - (7)].e), (yyvsp[(7) - (7)].init_list)); 
  }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 287 "lang.y"
    {
    (yyval.c) = TMultiVarDecl((yyvsp[(2) - (2)].var_list));
  }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 295 "lang.y"
    {
    (yyval.e) = (TConst((yyvsp[(1) - (1)].n)));
  }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 299 "lang.y"
    {
    (yyval.e) = ((yyvsp[(2) - (3)].e));
  }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 303 "lang.y"
    {
    (yyval.e) = (TVar((yyvsp[(1) - (1)].i)));
  }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 308 "lang.y"
    {
      (yyval.e) = TChar((yyvsp[(1) - (1)].single_char));
  }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 313 "lang.y"
    {
      (yyval.e) = TString((yyvsp[(1) - (1)].i));
  }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 317 "lang.y"
    {
    (yyval.e) = (TReadInt());
  }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 321 "lang.y"
    {
    (yyval.e) = (TReadChar());
  }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 325 "lang.y"
    {
    (yyval.e) = (TMalloc((yyvsp[(3) - (4)].e)));
  }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 329 "lang.y"
    {
    (yyval.e) = (TUnOp(T_NOT,(yyvsp[(2) - (2)].e)));
  }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 333 "lang.y"
    {
    (yyval.e) = (TUnOp(T_UMINUS,(yyvsp[(2) - (2)].e)));
  }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 337 "lang.y"
    {
    (yyval.e) = (TDeref((yyvsp[(2) - (2)].e)));
  }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 342 "lang.y"
    {
    (yyval.e) = (TMultiArray((yyvsp[(1) - (4)].e), (yyvsp[(3) - (4)].e))); // 多维数组访问
  }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 349 "lang.y"
    {
    (yyval.e) = ((yyvsp[(1) - (1)].e));
  }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 353 "lang.y"
    {
    (yyval.e) = (TBinOp(T_MUL,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 357 "lang.y"
    {
    (yyval.e) = (TBinOp(T_PLUS,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 361 "lang.y"
    {
    (yyval.e) = (TBinOp(T_MINUS,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 365 "lang.y"
    {
    (yyval.e) = (TBinOp(T_DIV,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 369 "lang.y"
    {
    (yyval.e) = (TBinOp(T_MOD,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 373 "lang.y"
    {
    (yyval.e) = (TBinOp(T_LT,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 377 "lang.y"
    {
    (yyval.e) = (TBinOp(T_GT,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 381 "lang.y"
    {
    (yyval.e) = (TBinOp(T_LE,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 385 "lang.y"
    {
    (yyval.e) = (TBinOp(T_GE,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 389 "lang.y"
    {
    (yyval.e) = (TBinOp(T_EQ,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 393 "lang.y"
    {
    (yyval.e) = (TBinOp(T_NE,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 397 "lang.y"
    {
    (yyval.e) = (TBinOp(T_AND,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 401 "lang.y"
    {
    (yyval.e) = (TBinOp(T_OR,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  }
    break;


/* Line 1792 of yacc.c  */
#line 2048 "parser.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 407 "lang.y"


void yyerror(char* s)
{
    fprintf(stderr , "%s\n",s);
}
