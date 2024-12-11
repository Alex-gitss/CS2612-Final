#ifndef LANG_H_INCLUDED
#define LANG_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum BinOpType {
  T_PLUS,
  T_MINUS,
  T_MUL,
  T_DIV,
  T_MOD,
  T_LT,
  T_GT,
  T_LE,
  T_GE,
  T_EQ,
  T_NE,
  T_AND,
  T_OR
};

enum UnOpType {
  T_UMINUS,
  T_NOT
};

enum ExprType {
  T_CONST = 0,
  T_VAR,
  T_BINOP,
  T_UNOP,
  T_DEREF,
  T_MALLOC,
  T_RI,
  T_RC,
  T_ARRAY, // array type
  T_MD_ARRAY, // multidimensional array type
  T_INIT_LIST, // initialization list type
  T_CHAR, // char type
  T_STRING // string type
};

enum CmdType {
  T_DECL = 0,
  T_ASGN,
  T_SEQ,
  T_IF,
  T_WHILE,
  T_WI,
  T_WC,
  T_ARRAY_DECL, // declaration of array type
  T_POINTER_DECL, // declaration of pointer type
  T_CHAR_DECL, // declaration of char type
  T_STRING_DECL_WITH_STRING, // declartion of string type using string
  T_STRING_DECL_WITH_ARRAY, // declaration of string type using array
  T_MULTI_VAR_DECL // declaration of multi-variables type
};

struct expr {
  enum ExprType t;
  union {
    struct {unsigned int value; } CONST;
    struct {char * name; } VAR;
    struct {enum BinOpType op; struct expr * left; struct expr * right; } BINOP;
    struct {enum UnOpType op; struct expr * arg; } UNOP;
    struct {struct expr * arg; } DEREF;
    struct {struct expr * arg; } MALLOC;
    struct {void * none; } RI;
    struct {void * none; } RC;
    // array type
    struct { char * array; struct expr * index; } ARRAY;
    // char type
    struct { char * c; } CHAR;   
    // string type
    struct { char * str; } STRING;
    // initialization list type
    struct init_list * init_list; 
    // multi-dimensional array type
    struct {
        struct expr * array;
        struct expr * index;
    } MD_ARRAY;
  } d;
};

// expression list type
struct expr_list {
    // pointer of current expression
    struct expr * expr;
    // pointer of next expression in list
    struct expr_list * next;
};

// initialization list type
struct init_list {
    // pointer of expression link list
    struct expr_list * exprs; 
};

struct var_decl {
    char * name;
    enum { VAR_SIMPLE, VAR_ARRAY, VAR_POINTER, VAR_POINTER_MALLOC} type;
    // size of the array
    struct expr_list * sizes; 
    // levels of pointer
    int pointer_level; 
    // dimensions of multi-dimensional array
    int dimensions; 
    // initialization expression
    struct expr * init_expr; 
    // initialization expression list
    struct init_list * init_expr_list; 
};

// multi-variables declaration
struct multi_var_decl {
    struct var_decl var;
    struct multi_var_decl * next;
};

// multi-variables declaration in single command
struct cmd * TMultiVarDecl(struct multi_var_decl * vars);
// initialize multi-variables list
struct multi_var_decl * create_multi_var_decl(struct var_decl var);
// add new variable to current multi-variables list
struct multi_var_decl *add_multi_var_decl(struct multi_var_decl * list, struct var_decl var);
 
// initialize expression list
struct expr_list * create_expr_list(struct expr * expr);
// initialize initialization list
struct init_list * create_init_list(struct expr_list * expr_list);
// add new expression to current expression list
struct expr_list * add_expr_list(struct expr_list * list, struct expr * expr);

struct cmd {
  enum CmdType t;
  union {
    struct {char * name; struct expr * init_expr; } DECL;
    struct {struct expr * left; struct expr * right; } ASGN;
    struct {struct cmd * left; struct cmd * right; } SEQ;
    struct {struct expr * cond; struct cmd * left; struct cmd * right; } IF;
    struct {struct expr * cond; struct cmd * body; } WHILE;
    struct {struct expr * arg; } WI;
    struct {struct expr * arg; } WC;
    // declaration of array type
    struct { char * name; struct expr * size; struct init_list * init_expr; } ARRAY_DECL; 
    // declaration of pointer type
    struct { char * name; int pointer_level; struct expr * size;} POINTER_DECL; 
    // declaration of char type
    struct { char * name; struct expr * init_expr; } CHAR_DECL; 
    // declaration of string type using string
    struct { char * name; struct expr * size; struct expr * init_expr;} STRING_DECL_WITH_STRING;
    // declaration of string type using char array
    struct { char * name; struct expr * size; struct init_list * init_expr;} STRING_DECL_WITH_ARRAY;
    // declaration of multi-variables
    struct { struct multi_var_decl * vars;} MULTI_VAR_DECL; 
  } d;
};

struct expr * TConst(unsigned int value);
struct expr * TVar(char * name);
struct expr * TBinOp(enum BinOpType op, struct expr * left, struct expr * right);
struct expr * TUnOp(enum UnOpType op, struct expr * arg);
struct expr * TDeref(struct expr * arg);
struct expr * TMalloc(struct expr * arg);
struct expr * TReadInt();
struct expr * TReadChar();
struct cmd * TDecl(char * name, struct expr * init_expr);
struct cmd * TAsgn(struct expr * left, struct expr * right);
struct cmd * TSeq(struct cmd * left, struct cmd * right);
struct cmd * TIf(struct expr * cond, struct cmd * left, struct cmd * right);
struct cmd * TWhile(struct expr * cond, struct cmd * body);
struct cmd * TWriteInt(struct expr * arg);
struct cmd * TWriteChar(struct expr * arg);

// declaration of array type
struct cmd * TArrayDecl(char * name, struct expr * size, struct init_list * init_expr);
// declaration of char type
struct cmd * TCharDecl(char * name, struct expr * init_expr);
// declaration of string type using string with size specified
struct cmd * TStringDeclString(char * name, struct expr * size, struct expr * init_expr);
// declaration of string type using char array with size specified
struct cmd * TStringDeclArray(char * name, struct expr * size, struct init_list * init_expr);
// declaration of string type using string without size specified
struct cmd * TStringDeclStringEmpty(char * name, struct expr * init_expr);
// declaration of string type using char array without size specified
struct cmd * TStringDeclArrayEmpty(char * name, struct init_list * init_expr);

// declaration of pointer type
struct cmd * TPointerDecl(char * name, int pointer_level, struct expr * size);

// implementation of array and multi-dimentional array
struct expr * TArray(char * array, struct expr * index);
struct expr *TMDArray(struct expr *array, struct expr *index);

// implementation of expressions
struct expr *new_expr(enum ExprType type, void *data);

// implementation of char type
struct expr * TChar(char *c);
// implementation of string type
struct expr * TString(char *str);

void print_binop(enum BinOpType op, int depth);
void print_unop(enum UnOpType op, int depth);
void print_expr(struct expr *e, int depth);
void print_cmd(struct cmd * c, int depth);

unsigned int build_nat(char * c, int len);
char * new_str(char * str, int len);

#endif // LANG_H_INCLUDED
