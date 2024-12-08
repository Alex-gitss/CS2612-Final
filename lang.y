%{
	// this part is copied to the beginning of the parser 
	#include <stdio.h>
	#include "lang.h"
	#include "lexer.h"
	void yyerror(char *);
	int yylex(void);
        struct cmd * root;
%}

%union {
unsigned int n;
char * i;
struct expr * e;
struct cmd * c;
void * none;
char * single_char;
struct init_list * init_list;
struct expr_list * expr_list;
struct expr_list * sizes;
struct var_decl var_decl;
struct multi_var_decl * multi_var_decl;
}

// Terminals
%token <n> TM_NAT
%token <i> TM_IDENT
%token <i> TM_STRING
%token <none> TM_LEFT_BRACE TM_RIGHT_BRACE
%token <none> TM_LEFT_BRACKET TM_RIGHT_BRACKET
%token <none> TM_LEFT_PAREN TM_RIGHT_PAREN
%token <none> TM_COMMA
%token <none> TM_SEMICOL
%token <none> TM_MALLOC TM_RI TM_RC TM_WI TM_WC
%token <none> TM_VAR TM_IF TM_THEN TM_ELSE TM_WHILE TM_DO TM_CHAR
%token <none> TM_ASGNOP
%token <none> TM_OR
%token <none> TM_AND
%token <none> TM_NOT
%token <none> TM_LT TM_LE TM_GT TM_GE TM_EQ TM_NE
%token <none> TM_PLUS TM_MINUS
%token <none> TM_MUL TM_DIV TM_MOD
%token <single_char> TM_SINGLE_CHAR

// Nonterminals
%type <c> NT_WHOLE
%type <c> NT_CMD
%type <e> NT_EXPR_2
%type <e> NT_EXPR

// level of pointer type
%type <n> NT_POINTER_LEVEL
// initialization list type
%type <init_list> NT_INIT_LIST
// expression list type
%type <expr_list> NT_EXPR_LIST

// Initialize character list
%type <init_list> NT_INIT_CHAR_LIST
// character lisst
%type <expr_list> NT_CHAR_LIST

// declaration one of variable
%type <var_decl> NT_VAR_DECL
// declaration of multi variables
%type <multi_var_decl> NT_VAR_LIST
// Multidimensional array index
%type <sizes> NT_MD_ARRAY_SIZES

// Priority
%nonassoc TM_ASGNOP
%left TM_OR
%left TM_AND
%left TM_LT TM_LE TM_GT TM_GE TM_EQ TM_NE
%left TM_PLUS TM_MINUS
%left TM_MUL TM_DIV TM_MOD
%right TM_SEMICOL TM_COMMA TM_NOT
%nonassoc TM_LEFT_PAREN TM_RIGHT_PAREN
%nonassoc TM_LEFT_BRACE TM_RIGHT_BRACE
%left TM_LEFT_BRACKET

%%

NT_WHOLE:
  NT_CMD
  {
    $$ = ($1);
    root = $$;
  }
;

NT_POINTER_LEVEL:
  TM_MUL
  {
    $$ = 1;
  }
  | TM_MUL NT_POINTER_LEVEL
  {
    $$ = $2 + 1;
  }
;

NT_INIT_LIST:
  TM_LEFT_BRACE NT_EXPR_LIST TM_RIGHT_BRACE
  {
    $$ = create_init_list($2);
  }
;


NT_EXPR_LIST:
  // empty list
    {
        $$ = NULL;
    }
  // single expression
| NT_EXPR
    {
        $$ = create_expr_list($1);
    }
  // multi expressions
| NT_EXPR_LIST TM_COMMA NT_EXPR
    {
        $$ = add_expr_list($1, $3);
    }
  // initialization list
| NT_INIT_LIST
    {
        $$ = create_expr_list(new_expr(T_INIT_LIST, $1));
    }
  // initialization list after expression list
| NT_EXPR_LIST TM_COMMA NT_INIT_LIST
    {
        $$ = add_expr_list($1, new_expr(T_INIT_LIST, $3));
    }
;

  // initialization char list
NT_INIT_CHAR_LIST:
    TM_LEFT_BRACE NT_CHAR_LIST TM_RIGHT_BRACE
    {
        $$ = create_init_list($2);
    }
;

// char list
NT_CHAR_LIST:
  // single char
  TM_SINGLE_CHAR
{
    $$ = create_expr_list(TChar($1));
}
  // string
| NT_CHAR_LIST TM_COMMA TM_SINGLE_CHAR
{
    $$ = add_expr_list($1, TChar($3));
}
;

// index of multi-dimensional array
NT_MD_ARRAY_SIZES:

  TM_LEFT_BRACKET NT_EXPR TM_RIGHT_BRACKET 
  { 
    $$ = create_expr_list($2); 
  }

| NT_MD_ARRAY_SIZES TM_LEFT_BRACKET NT_EXPR TM_RIGHT_BRACKET 
  {  
    $$ = add_expr_list($1, $3); 
  }
;

// declaration of variables
NT_VAR_DECL:
  // declaration of single variable
  TM_IDENT
  {
    $$ = (struct var_decl){ .name = $1, .type = VAR_SIMPLE, .sizes = NULL, .pointer_level = 0 };
  }
  // declaration and initialization of single variable
| TM_IDENT TM_ASGNOP NT_EXPR
  {
    $$ = (struct var_decl){ .name = $1, .type = VAR_SIMPLE, .init_expr = $3 };
  }
  // declaration of array
| TM_IDENT NT_MD_ARRAY_SIZES
  {
    $$ = (struct var_decl){ .name = $1, .type = VAR_ARRAY, .sizes = $2, .pointer_level = 0 };
  }
  // declaration and initialization of array
| TM_IDENT NT_MD_ARRAY_SIZES TM_ASGNOP NT_INIT_LIST
  {
    $$ = (struct var_decl){ .name = $1, .type = VAR_ARRAY, .sizes = $2, .pointer_level = 0, .init_expr_list = $4 };
  }
  // declaration of pointer 
| NT_POINTER_LEVEL TM_IDENT
  {
    $$ = (struct var_decl){ .name = $2, .type = VAR_POINTER, .sizes = NULL, .pointer_level = $1 };
  }
;

// list of multi variables
NT_VAR_LIST:
  // single variable
  NT_VAR_DECL
  {
    $$ = create_multi_var_decl($1);
  }
  // multi variables
| NT_VAR_LIST TM_COMMA NT_VAR_DECL
  {
    $$ = add_multi_var_decl($1, $3);
  }
;

NT_CMD:
| NT_EXPR TM_ASGNOP NT_EXPR
  {
    $$ = (TAsgn($1,$3));
  }
| NT_CMD TM_SEMICOL NT_CMD
  {
    $$ = (TSeq($1,$3));
  }
| TM_IF NT_EXPR TM_THEN TM_LEFT_BRACE NT_CMD TM_RIGHT_BRACE TM_ELSE TM_LEFT_BRACE NT_CMD TM_RIGHT_BRACE
  {
    $$ = (TIf($2,$5,$9));
  }
| TM_WHILE NT_EXPR TM_DO TM_LEFT_BRACE NT_CMD TM_RIGHT_BRACE
  {
    $$ = (TWhile($2,$5));
  }
| TM_WI TM_LEFT_PAREN NT_EXPR TM_RIGHT_PAREN
  {
    $$ = (TWriteInt($3));
  }
| TM_WC TM_LEFT_PAREN NT_EXPR TM_RIGHT_PAREN
  {
    $$ = (TWriteChar($3));
  }
// Parsing dynamic array initialization, malloc
| TM_VAR NT_POINTER_LEVEL TM_IDENT TM_ASGNOP TM_MALLOC TM_LEFT_PAREN NT_EXPR TM_RIGHT_PAREN
  {
    // $2 is the pointer level
    $$ = TPointerDecl($3, $2, $7); 
  } 
| TM_CHAR TM_IDENT 
  {
    $$ = TCharDecl($2, NULL); // Create a character variable declaration without initialization
  }
  | TM_CHAR TM_IDENT TM_ASGNOP TM_SINGLE_CHAR 
  {
    $$ = TCharDecl($2, TChar($4)); // Create a character variable declaration with initialization
  }
// Parsing string type with specified size
| TM_CHAR TM_IDENT TM_LEFT_BRACKET NT_EXPR TM_RIGHT_BRACKET 
  {
      $$ = TStringDeclString($2, $4, NULL); 
  }
// Parsing string type with specified size and initialized with a string enclosed in double quotes
| TM_CHAR TM_IDENT TM_LEFT_BRACKET NT_EXPR TM_RIGHT_BRACKET TM_ASGNOP TM_STRING
  {
      $$ = TStringDeclString($2, $4, TString($7)); 
  }
// Parsing string type with specified size and initialized with a character list
| TM_CHAR TM_IDENT TM_LEFT_BRACKET NT_EXPR TM_RIGHT_BRACKET TM_ASGNOP NT_INIT_CHAR_LIST
  {
      $$ = TStringDeclArray($2, $4, $7); 
  }
// Variable declaration, single/multiple variables, further parsed in NT_VAR_LIST
| TM_VAR NT_VAR_LIST
  {
    $$ = TMultiVarDecl($2);
  }
;


NT_EXPR_2:
  TM_NAT
  {
    $$ = (TConst($1));
  }
| TM_LEFT_PAREN NT_EXPR TM_RIGHT_PAREN
  {
    $$ = ($2);
  }
| TM_IDENT
  {
    $$ = (TVar($1));
  }
// single char
| TM_SINGLE_CHAR
  {
      $$ = TChar($1);
  }
// string
| TM_STRING
  {
      $$ = TString($1);
  }
| TM_RI TM_LEFT_PAREN TM_RIGHT_PAREN
  {
    $$ = (TReadInt());
  }
| TM_RC TM_LEFT_PAREN TM_RIGHT_PAREN
  {
    $$ = (TReadChar());
  }
| TM_MALLOC TM_LEFT_PAREN NT_EXPR TM_RIGHT_PAREN
  {
    $$ = (TMalloc($3));
  }
| TM_NOT NT_EXPR_2
  {
    $$ = (TUnOp(T_NOT,$2));
  }
| TM_MINUS NT_EXPR_2
  {
    $$ = (TUnOp(T_UMINUS,$2));
  }
| TM_MUL NT_EXPR_2
  {
    $$ = (TDeref($2));
  }
// Multidimensional array case
| NT_EXPR_2 TM_LEFT_BRACKET NT_EXPR TM_RIGHT_BRACKET
  {
    $$ = (TMDArray($1, $3)); // Multidimensional array visit
  }
;

NT_EXPR:
  NT_EXPR_2
  {
    $$ = ($1);
  }
| NT_EXPR TM_MUL NT_EXPR
  {
    $$ = (TBinOp(T_MUL,$1,$3));
  }
| NT_EXPR TM_PLUS NT_EXPR
  {
    $$ = (TBinOp(T_PLUS,$1,$3));
  }
| NT_EXPR TM_MINUS NT_EXPR
  {
    $$ = (TBinOp(T_MINUS,$1,$3));
  }
| NT_EXPR TM_DIV NT_EXPR
  {
    $$ = (TBinOp(T_DIV,$1,$3));
  }
| NT_EXPR TM_MOD NT_EXPR
  {
    $$ = (TBinOp(T_MOD,$1,$3));
  }
| NT_EXPR TM_LT NT_EXPR
  {
    $$ = (TBinOp(T_LT,$1,$3));
  }
| NT_EXPR TM_GT NT_EXPR
  {
    $$ = (TBinOp(T_GT,$1,$3));
  }
| NT_EXPR TM_LE NT_EXPR
  {
    $$ = (TBinOp(T_LE,$1,$3));
  }
| NT_EXPR TM_GE NT_EXPR
  {
    $$ = (TBinOp(T_GE,$1,$3));
  }
| NT_EXPR TM_EQ NT_EXPR
  {
    $$ = (TBinOp(T_EQ,$1,$3));
  }
| NT_EXPR TM_NE NT_EXPR
  {
    $$ = (TBinOp(T_NE,$1,$3));
  }
| NT_EXPR TM_AND NT_EXPR
  {
    $$ = (TBinOp(T_AND,$1,$3));
  }
| NT_EXPR TM_OR NT_EXPR
  {
    $$ = (TBinOp(T_OR,$1,$3));
  }
;


%%

void yyerror(char* s)
{
    fprintf(stderr , "%s\n",s);
}
