#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lang.h"
#include <stdbool.h>
#include <string.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"

void print_indent(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("|--");
    }
}


struct expr * new_expr_ptr() {
    struct expr * result = (struct expr *) malloc(sizeof(struct expr));
    if (result == NULL) {
        printf("Failure in malloc.\n");
        exit(0);
    }
    return result;
}

struct cmd * new_cmd_ptr() {
    struct cmd * result = (struct cmd *) malloc(sizeof(struct cmd));
    if (result == NULL) {
        printf("Failure in malloc.\n");
        exit(0);
    }
    return result;
}

struct expr * TConst(unsigned int value) {
  struct expr * res = new_expr_ptr();
  res -> t = T_CONST;
  res -> d.CONST.value = value;
  return res;
}

struct expr * TVar(char * name) {
  struct expr * res = new_expr_ptr();
  res -> t = T_VAR;
  res -> d.VAR.name = name;
  return res;
}

struct expr * TBinOp(enum BinOpType op, struct expr * left, struct expr * right) {
  struct expr * res = new_expr_ptr();
  res -> t = T_BINOP;
  res -> d.BINOP.op = op;
  res -> d.BINOP.left = left;
  res -> d.BINOP.right = right;
  return res;
}

struct expr * TUnOp(enum UnOpType op, struct expr * arg) {
  struct expr * res = new_expr_ptr();
  res -> t = T_UNOP;
  res -> d.UNOP.op = op;
  res -> d.UNOP.arg = arg;
  return res;
}

struct expr * TDeref(struct expr * arg) {
  struct expr * res = new_expr_ptr();
  res -> t = T_DEREF;
  res -> d.DEREF.arg = arg;
  return res;
}

struct expr * TMalloc(struct expr * arg) {
  struct expr * res = new_expr_ptr();
  res -> t = T_MALLOC;
  res -> d.MALLOC.arg = arg;
  return res;
}

struct expr * TReadInt() {
  struct expr * res = new_expr_ptr();
  res -> t = T_RI;
  return res;
}

struct expr * TReadChar() {
  struct expr * res = new_expr_ptr();
  res -> t = T_RC;
  return res;
}

struct cmd * TDecl(char * name, struct expr * init_expr) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_DECL;
  res -> d.DECL.name = name;
  res -> d.DECL.init_expr = init_expr;
  return res;
}

struct cmd * TAsgn(struct expr * left, struct expr * right) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_ASGN;
  res -> d.ASGN.left = left;
  res -> d.ASGN.right = right;
  return res;
}

struct cmd * TSeq(struct cmd * left, struct cmd * right) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_SEQ;
  res -> d.SEQ.left = left;
  res -> d.SEQ.right = right;
  return res;
}

struct cmd * TIf(struct expr * cond, struct cmd * left, struct cmd * right) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_IF;
  res -> d.IF.cond = cond;
  res -> d.IF.left = left;
  res -> d.IF.right = right;
  return res;
}

struct cmd * TWhile(struct expr * cond, struct cmd * body) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_WHILE;
  res -> d.WHILE.cond = cond;
  res -> d.WHILE.body = body;
  return res;
}

struct cmd * TWriteInt(struct expr * arg) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_WI;
  res -> d.WI.arg = arg;
  return res;
}

struct cmd * TWriteChar(struct expr * arg) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_WC;
  res -> d.WC.arg = arg;
  return res;
}

/*
    Create an expression representing a single array access:
    array_name : The name of the array
    index_expr : The expression representing the index of the array element
    Returns a new expression pointer representing the array access
 */
struct expr * TArray(char * array_name, struct expr * index_expr) {
    struct expr * result = new_expr_ptr();
    result->t = T_ARRAY;
    result->d.ARRAY.array = array_name;
    result->d.ARRAY.index = index_expr;
    return result;
}

/**
    Create an expression representing multi-dimensional array access:

    array_expr : The expression representing the already partially accessed array
    index_expr : The expression representing the current dimension's index
    Returns a new expression pointer representing further access to the multi-dimensional array
 */
struct expr * TMDArray(struct expr * array_expr, struct expr * index_expr) {
    struct expr * result = new_expr_ptr();
    result->t = T_MD_ARRAY;
    result->d.MD_ARRAY.array = array_expr;
    result->d.MD_ARRAY.index = index_expr;
    return result;
}

/*
    Create a new expression list node

    expr_node The expression to add to the list
    Returns a new expression list node containing the provided expression
 */
struct expr_list * create_expr_list(struct expr * expr_node) {
    struct expr_list * new_list = malloc(sizeof(struct expr_list));
    if (!new_list) {
        return NULL;
    }
    new_list->expr = expr_node;
    new_list->next = NULL;
    return new_list;
}

/*
    Create a new initialization list node

    expression_list : The expression list to add to the initialization list
    Returns a new initialization list node containing the provided expression list
 */
struct init_list * create_init_list(struct expr_list * expression_list) {
    struct init_list * new_list = malloc(sizeof(struct init_list));
    if (!new_list) {
        return NULL;
    }
    new_list->exprs = expression_list;
    return new_list;
}

/*
    Append an expression to the end of an expression list

    list : The list to append the expression to
    expr_node : The expression to append
    Returns the updated expression list
 */
struct expr_list * add_expr_list(struct expr_list * list, struct expr * expr_node) {
    struct expr_list * current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    struct expr_list * new_node = create_expr_list(expr_node);
    if (!new_node) {
        return list;
    }
    current->next = new_node;
    return list;
}

/*
    Create an array declaration command

    array_name : The name of the array
    array_size : The size of the array
    init_expression : The initialization expression list for the array
    Returns a new command pointer representing the array declaration
 */
struct cmd * TArrayDecl(char * array_name, struct expr * array_size, struct init_list * init_expression) {
    struct cmd * result = new_cmd_ptr();
    result->t = T_ARRAY_DECL;
    result->d.ARRAY_DECL.name = array_name;
    result->d.ARRAY_DECL.size = array_size;   
    result->d.ARRAY_DECL.init_expr = init_expression;
    return result;
}

/*
    Create a string declaration command (initialized with double-quoted string)

    string_name : The name of the string variable
    string_size : The size of the string
    init_expression : The expression initializing the string (double-quoted string)
    Returns a new command pointer representing the string declaration
 */
struct cmd * TStringDeclString(char * string_name, struct expr * string_size, struct expr * init_expression) {
    struct cmd * result = new_cmd_ptr();
    result->t = T_STRING_DECL_WITH_STRING;
    result->d.STRING_DECL_WITH_STRING.name = string_name;
    result->d.STRING_DECL_WITH_STRING.size = string_size; 
    result->d.STRING_DECL_WITH_STRING.init_expr = init_expression;
    return result;
}

/*
    Create a string declaration command without size specified (initialized with double-quoted string)

    string_name : The name of the string variable
    init_expression : The expression initializing the string (double-quoted string)
    Returns a new command pointer representing the string declaration
 */
struct cmd * TStringDeclStringEmpty(char * string_name, struct expr * init_expression) {
  struct cmd * res = new_cmd_ptr();
  res->t = T_STRING_DECL_WITH_STRING;
  res->d.STRING_DECL_WITH_STRING.name = string_name;
  res->d.STRING_DECL_WITH_STRING.size = -1;
  res->d.STRING_DECL_WITH_STRING.init_expr = init_expression;
  return res;
}

/*
    Create a character array declaration command (initialized with character list)
 
    char_array_name : The name of the character array
    char_array_size : The size of the array
    init_expression : The initialization expression list for the character array
    Returns a new command pointer representing the character array declaration
 */
struct cmd * TStringDeclArray(char * char_array_name, struct expr * char_array_size, struct init_list * init_expression) {
    struct cmd * result = new_cmd_ptr();
    result->t = T_STRING_DECL_WITH_ARRAY;
    result->d.STRING_DECL_WITH_ARRAY.name = char_array_name;
    result->d.STRING_DECL_WITH_ARRAY.size = char_array_size; 
    result->d.STRING_DECL_WITH_ARRAY.init_expr = init_expression;
    return result;
}

/*
    Create a character array declaration command without size speicfied (initialized with character list)

    char_array_name : The name of the character array
    init_expression : The initialization expression list for the character array
    Returns a new command pointer representing the character array declaration
 */
struct cmd * TStringDeclArrayEmpty(char * char_array_name, struct init_list * init_expression) {
  struct cmd * res = new_cmd_ptr();
  res->t = T_STRING_DECL_WITH_ARRAY;
  res->d.STRING_DECL_WITH_ARRAY.name = char_array_name;
  res->d.STRING_DECL_WITH_ARRAY.size = -1;
  res->d.STRING_DECL_WITH_ARRAY.init_expr = init_expression;
  return res;
}

// Function to print information about expression lists
void print_expr_list(struct expr_list *list, int depth) {
    print_indent(depth);
    printf(BLUE "EXPR_LIST\n" RESET);

    struct expr_list * current = list;
    while (current != NULL) {
        print_expr(current->expr, depth + 1);
        if (current->next != NULL) {
            printf(",\n");
        }
        current = current->next;
    }
}

// A helper function to handle new initialization lists
struct expr * new_expr(enum ExprType type, void * data) {
    struct expr * e = new_expr_ptr(); 
    e->t = type;
    switch (type) {
        case T_INIT_LIST:
            e->d.init_list = (struct init_list *)data;
            break;
    }
    return e;
}

// Function to print information about initialization lists
void print_init_list(struct init_list *list, int depth) {
    struct expr_list * current = list->exprs;
    if (current == NULL) {
        print_indent(depth);
        printf("Empty List");
    }
    while (current != NULL) {
        print_expr(current->expr, depth);
        current = current->next;
    }
}

// Function to print information about character lists
int print_char_list(struct init_list *list, int depth) {
    int size = 0;
    print_indent(depth);
    printf(BLUE "CHAR_LIST\n" RESET);

    if (list == NULL) {
        print_indent(depth + 1);
        printf("NULL\n");
        return size;
    }

    struct expr_list * current = list->exprs;
    while (current != NULL) {
        print_indent(depth + 1);
        printf(BLUE "CHAR('%c')\n" RESET, current->expr->d.CHAR.c[1]);
        current = current->next;
        size += 1;
    }

    return size;
}

/* 
    Create a pointer declaration command.

    name : The name of the pointer variable.
    pointer_level : The level of the pointer (single or multi-level).
    size : If it is a dynamically allocated pointer, this indicates the size allocated; if static or unallocated, set to NULL.
    Returns a new command pointer representing the pointer declaration.
 */
struct cmd * TPointerDecl(char * name, int pointer_level, struct expr * size) {
    struct cmd * result = new_cmd_ptr();
    result->t = T_POINTER_DECL;
    result->d.POINTER_DECL.name = name;
    result->d.POINTER_DECL.pointer_level = pointer_level;
    if (size != NULL) {
        result->d.POINTER_DECL.size = TMalloc(size);
    } else {
        result->d.POINTER_DECL.size = NULL;
    }
    return result;
}

/* 
    Create a single character constant expression.

    char_const : Represents the character constant.
    Returns a new expression pointer representing the character constant.
 */
struct expr * TChar(char * char_const) {
    struct expr * result = new_expr_ptr();
    result->t = T_CHAR;
    result->d.CHAR.c = char_const;
    return result;
}

/* 
    Create a string constant expression.
 
    str_const : Represents the string constant.
    Returns a new expression pointer representing the string constant.
 */
struct expr * TString(char * str_const) {
    struct expr * result = new_expr_ptr();
    result->t = T_STRING;
    result->d.STRING.str = str_const;  
    return result;
}

// Implement TCharDecl function
struct cmd * TCharDecl(char * char_name, struct expr * init_expression) {
    struct cmd * result = new_cmd_ptr();
    result->t = T_CHAR_DECL;
    result->d.CHAR_DECL.name = char_name;
    result->d.CHAR_DECL.init_expr = init_expression;
    return result;
}

/* 
    Create a single-statement multi-variable declaration command.
 
    variable_list : Pointer to the variable declaration list, each element in the list is a variable declaration.
    Returns a new command pointer representing the multi-variable declaration.
 */
struct cmd * TMultiVarDecl(struct multi_var_decl * variable_list) {
    struct cmd * result = new_cmd_ptr();
    result->t = T_MULTI_VAR_DECL; 
    result->d.MULTI_VAR_DECL.vars = variable_list;
    return result;
}

/* 
    Create a new variable declaration list node.
 
    var_decl The variable declaration structure.
    Returns a new variable declaration list node.
 */
struct multi_var_decl * create_multi_var_decl(struct var_decl var_decl) {
    struct multi_var_decl * new_node = malloc(sizeof(struct multi_var_decl));
    if (new_node == NULL) {
        printf("Failure in malloc.\n");
        exit(0);
    }
    new_node->var = var_decl;
    new_node->next = NULL;
    return new_node;
}

/* 
    Append a new variable declaration to an existing variable declaration list.
  
    multi_var_decl_list : The existing variable declaration list.
    var_decl : The new variable declaration.
    Returns the updated variable declaration list.
 */
struct multi_var_decl * add_multi_var_decl(struct multi_var_decl * multi_var_decl_list, struct var_decl var_decl) {
    if (multi_var_decl_list == NULL) {
        return create_multi_var_decl(var_decl);
    }
    struct multi_var_decl * current = multi_var_decl_list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = create_multi_var_decl(var_decl);
    return multi_var_decl_list;
}

void print_binop(enum BinOpType op, int depth) {
    // print_indent(depth);

    switch (op) {
    case T_PLUS:
        printf(BLUE "PLUS\n" RESET);
        break;
    case T_MINUS:
        printf(BLUE "MINUS\n" RESET);
        break;
    case T_MUL:
        printf(BLUE "MUL\n" RESET);
        break;
    case T_DIV:
        printf(BLUE "DIV\n" RESET);
        break;
    case T_MOD:
        printf(BLUE "MOD\n" RESET);
        break;
    case T_LT:
        printf(BLUE "LT\n" RESET);
        break;
    case T_GT:
        printf(BLUE "GT\n" RESET);
        break;
    case T_LE:
        printf(BLUE "LE\n" RESET);
        break;
    case T_GE:
        printf(BLUE "GE\n" RESET);
        break;
    case T_EQ:
        printf(BLUE "EQ\n" RESET);
        break;
    case T_NE:
        printf(BLUE "NE\n" RESET);
        break;
    case T_AND:
        printf(BLUE "AND\n" RESET);
        break;
    case T_OR:
        printf(BLUE "OR\n" RESET);
        break;
    }
}

// void print_binop(enum BinOpType operation, int depth) {
//     print_indent(depth);

//     switch (operation) {
//     case T_PLUS:
//         printf("PLUS\n");
//         break;
//     case T_MINUS:
//         printf("MINUS\n");
//         break;
//     case T_MUL:
//         printf("MUL\n");
//         break;
//     case T_DIV:
//         printf("DIV\n");
//         break;
//     case T_MOD:
//         printf("MOD\n");
//         break;
//     case T_LT:
//         printf("LT\n");
//         break;
//     case T_GT:
//         printf("GT\n");
//         break;
//     case T_LE:
//         printf("LE\n");
//         break;
//     case T_GE:
//         printf("GE\n");
//         break;
//     case T_EQ:
//         printf("EQ\n");
//         break;
//     case T_NE:
//         printf("NE\n");
//         break;
//     case T_AND:
//         printf("AND\n");
//         break;
//     case T_OR:
//         printf("OR\n");
//         break;
//     }
// }

void print_unop(enum UnOpType operation, int depth) {
    print_indent(depth);

    switch (operation) {
    case T_UMINUS:
        printf(BLUE "UMINUS\n" RESET);
        break;
    case T_NOT:
        printf(BLUE "NOT\n" RESET);
        break;
    }
}

void print_expr(struct expr *e, int depth) {
    print_indent(depth);

    switch (e->t) {
    case T_CONST:
        printf(BLUE "CONST(%d)\n" RESET, e->d.CONST.value);
        break;
    case T_VAR:
        printf(BLUE "VAR(%s)\n" RESET, e->d.VAR.name);
        break;
    case T_BINOP:
        print_binop(e->d.BINOP.op, depth);
        print_indent(depth + 1);
        printf(BLUE "Left:\n" RESET);
        print_expr(e->d.BINOP.left, depth + 2);
        print_indent(depth + 1);
        printf(BLUE "Right:\n" RESET);
        print_expr(e->d.BINOP.right, depth + 2);
        break;
    case T_UNOP:
        print_unop(e->d.UNOP.op, depth);
        print_indent(depth + 1);
        printf(BLUE "Arg:\n" RESET);
        print_expr(e->d.UNOP.arg, depth + 2);
        break;
    case T_DEREF:
        printf(BLUE "DEREF\n" RESET);
        print_expr(e->d.DEREF.arg, depth + 1);
        break;
    case T_MALLOC:
        printf(BLUE "MALLOC\n" RESET);
        print_expr(e->d.MALLOC.arg, depth + 1);
        break;
    case T_RI:
        printf(BLUE "READ_INT()\n" RESET);
        break;
    case T_RC:
        printf(BLUE "READ_CHAR()\n" RESET);
        break;
    case T_ARRAY:
        printf(BLUE "ARRAY(%s)\n" RESET, e->d.ARRAY.array);
        print_indent(depth + 1);
        printf(BLUE "Index:\n" RESET);
        print_expr(e->d.ARRAY.index, depth + 2);
        break;
    case T_MD_ARRAY:
        printf(BLUE "ARRAY\n" RESET);
        print_indent(depth + 1);
        printf(BLUE "Object:\n" RESET);
        print_expr(e->d.MD_ARRAY.array, depth + 2);
        print_indent(depth + 1);
        printf(BLUE "Index:\n" RESET);
        print_expr(e->d.MD_ARRAY.index, depth + 2);
        break;
    case T_STRING:
        printf(BLUE "STRING(%s)\n" RESET, e->d.STRING.str);
        break;
    case T_CHAR:
        printf(BLUE "CHAR('%c')\n" RESET, e->d.CHAR.c[1]);
        break;
    case T_INIT_LIST:
        printf(BLUE "INIT_LIST\n" RESET);
        print_init_list(e->d.init_list, depth + 1);
        break;
    }
}
// void print_expr(struct expr *e, int depth) {
//     print_indent(depth);

//     switch (e->t) {
//     case T_CONST:
//         printf("CONST(%d)\n", e->d.CONST.value);
//         break;
//     case T_VAR:
//         printf("VAR(%s)\n", e->d.VAR.name);
//         break;
//     // For binary operations, print the two operands
//     case T_BINOP:
//         print_binop(e->d.BINOP.op, 0); 
//         print_indent(depth + 1);
//         printf("Left:\n");
//         print_expr(e->d.BINOP.left, depth + 2);
//         print_indent(depth + 1);
//         printf("Right:\n");
//         print_expr(e->d.BINOP.right, depth + 2);
//         break;
//     // For unary operations, print only one operand
//     case T_UNOP:
//         print_unop(e->d.UNOP.op, depth + 1); 
//         printf("\n");
//         print_indent(depth + 1);
//         printf("Arg:\n");
//         print_expr(e->d.UNOP.arg, depth + 2);
//         break;
//     case T_DEREF:
//         printf("DEREF\n");
//         print_expr(e->d.DEREF.arg, depth + 1);
//         break;
//     case T_MALLOC:
//         printf("MALLOC\n");
//         print_expr(e->d.MALLOC.arg, depth + 1);
//         break;
//     case T_RI:
//         printf("READ_INT()\n");
//         break;
//     case T_RC:
//         printf("READ_CHAR()\n");
//         break;
//     // Print array name and index
//     case T_ARRAY:
//         printf("ARRAY%s,\n", e->d.ARRAY.array);
//         print_indent(depth + 1);
//         printf("Index:\n");
//         print_expr(e->d.ARRAY.index, depth + 2);
//         break;
//     // Print multi-dimensional array name and indices
//     case T_MD_ARRAY:
//         printf("ARRAY\n");
//         print_indent(depth + 1);
//         printf("Object:\n");
//         print_expr(e->d.MD_ARRAY.array, depth + 2);
//         print_indent(depth + 1);
//         printf("Index:\n");
//         print_expr(e->d.MD_ARRAY.index, depth + 2);
//         break;
//     // Print string
//     case T_STRING:
//         printf("STRING(%s)\n", e->d.STRING.str);
//         break;
//     // Print single character
//     case T_CHAR:
//         printf("CHAR('%c')\n", e->d.CHAR.c[1]);
//         break;
//     // Print initialization list
//     case T_INIT_LIST:
//         printf("INIT_LIST\n");
//         print_init_list(e->d.init_list, depth + 1); 
//         break;
//     }
// }

// Function to print information related to variable declarations
void print_var_decl(struct var_decl *var, int depth) {
    print_indent(depth);

    switch (var->type) {
    // For simple variables, print the variable name and initial value
    case VAR_SIMPLE:
        printf(BLUE "Object:\n" RESET);
        print_indent(depth + 1);
        printf(BLUE "VAR(%s)\n" RESET, var->name);
        print_indent(depth);
        printf(BLUE "Init Expr:\n" RESET);
        if (var->init_expr != NULL) {
            print_expr(var->init_expr, depth + 1);
        } else {
            print_indent(depth + 1);
            printf("None\n");
        }
        break;
    // For array variables, print the array name, index, and initialization list
    case VAR_ARRAY:
        printf(BLUE "Object:\n" RESET);
        print_indent(depth + 1);
        printf(BLUE "ARRAY(%s" RESET, var->name);
        struct expr_list *dimension = var->sizes;
        while (dimension != NULL) {
            if (dimension->expr) {
                printf(BLUE "[" RESET);
                printf(BLUE "CONST(%d)" RESET, dimension->expr->d.CONST.value);
                printf(BLUE "]" RESET);
            } else {
                printf("[]");
            }
            dimension = dimension->next;
        }
        printf(BLUE ")\n" RESET);
        print_indent(depth);
        printf(BLUE "Init List:\n" RESET);
        if (var->init_expr_list != NULL) {
            print_init_list(var->init_expr_list, depth + 1);
        } else {
            print_indent(depth + 1);
            printf("None\n");
        }
        break;
    // For pointer variables, print the pointer name, level, and initialization value
    case VAR_POINTER:
        printf(BLUE "Object:\n" RESET);
        print_indent(depth + 1);
        printf(BLUE "PTR(%s, level: %d)\n" RESET, var->name, var->pointer_level);
        print_indent(depth);
        printf(BLUE "Init Expr:\n" RESET);
        if (var->init_expr != NULL) {
            print_expr(var->init_expr, depth + 1);
        } else {
            print_indent(depth + 1);
            printf("None\n");
        }
        break;
    }
}

// Function to print command-related information
void print_cmd(struct cmd *c, int depth) {
    print_indent(depth);

    switch (c->t) {
    case T_DECL:
        printf(RED "DECL(%s)\n" RESET, c->d.DECL.name);
        if (c->d.DECL.init_expr != NULL) {
            print_indent(depth + 1);
            printf(BLUE "Init Expr:\n" RESET);
            print_expr(c->d.DECL.init_expr, depth + 2);
        }
        printf("\n");
        break;
    case T_ASGN:
        printf(RED "ASGN\n" RESET);
        print_indent(depth + 1);
        printf(BLUE "Left:\n" RESET);
        print_expr(c->d.ASGN.left, depth + 2);
        print_indent(depth + 1);
        printf(BLUE "Right:\n" RESET);
        print_expr(c->d.ASGN.right, depth + 2);
        printf("\n");
        break;
    case T_SEQ:
        print_cmd(c->d.SEQ.left, depth);
        print_cmd(c->d.SEQ.right, depth);
        printf("\n");
        break;
    case T_IF:
        printf(RED "IF(\n" RESET);
        print_indent(depth + 1);
        printf(BLUE "Condition:\n" RESET);
        print_expr(c->d.IF.cond, depth + 2);
        print_indent(depth + 1);
        printf(BLUE "True Branch:\n" RESET);
        print_cmd(c->d.IF.left, depth + 2);
        print_indent(depth + 1);
        printf(BLUE "False Branch:\n" RESET);
        print_cmd(c->d.IF.right, depth + 2);
        print_indent(depth);
        printf(RED ")\n" RESET);
        printf("\n");
        break;
    case T_WHILE:
        printf(RED "WHILE(\n" RESET);
        print_indent(depth + 1);
        printf(BLUE "Condition:\n" RESET);
        print_expr(c->d.WHILE.cond, depth + 2);
        print_indent(depth + 1);
        printf(BLUE "Body:\n" RESET);
        print_cmd(c->d.WHILE.body, depth + 2);
        print_indent(depth);
        printf(RED ")\n" RESET);
        printf("\n");
        break;
    case T_WI:
        printf(RED "WRITE_INT(\n" RESET);
        print_expr(c->d.WI.arg, depth + 1);
        print_indent(depth);
        printf(RED ")\n" RESET);
        printf("\n");
        break;
    case T_WC:
        printf(RED "WRITE_CHAR(\n" RESET);
        print_expr(c->d.WC.arg, depth + 1);
        print_indent(depth);
        printf(RED ")\n" RESET);
        printf("\n");
        break;
    case T_ARRAY_DECL:
        printf(RED "ARR_DECL(%s)\n" RESET, c->d.ARRAY_DECL.name);
        if (c->d.ARRAY_DECL.size != NULL) {
            print_indent(depth + 1);
            printf(BLUE "Size:\n" RESET);
            print_expr(c->d.ARRAY_DECL.size, depth + 2);
        }
        if (c->d.ARRAY_DECL.init_expr != NULL) {
            print_indent(depth + 1);
            printf(BLUE "Init Expr:\n" RESET);
            print_init_list(c->d.ARRAY_DECL.init_expr, depth + 2);
        }
        printf("\n");
        break;
    case T_POINTER_DECL:
        printf(RED "PTR_DECL(%s, level: %d)\n" RESET, c->d.POINTER_DECL.name, c->d.POINTER_DECL.pointer_level);
        if (c->d.POINTER_DECL.size != NULL) {
            print_indent(depth + 1);
            printf(BLUE "Size Expr:\n" RESET);
            print_expr(c->d.POINTER_DECL.size, depth + 2);
        }
        printf("\n");
        break;
    case T_CHAR_DECL:
        printf(RED "CHAR_DECL(%s)\n" RESET, c->d.CHAR_DECL.name);
        if (c->d.CHAR_DECL.init_expr != NULL) {
            print_indent(depth + 1);
            printf(BLUE "Init Char:\n" RESET);
            print_expr(c->d.CHAR_DECL.init_expr, depth + 2);
        }
        printf("\n");
        break;
    case T_STRING_DECL_WITH_STRING:
        printf(RED "STRING_DECL(%s)\n" RESET, c->d.STRING_DECL_WITH_STRING.name);
        if (c->d.STRING_DECL_WITH_STRING.init_expr != NULL) {
            unsigned int malloc_size;
            if (c->d.STRING_DECL_WITH_STRING.size != -1){
                malloc_size = c->d.STRING_DECL_WITH_STRING.size->d.CONST.value;
            }
            else{
                malloc_size = strlen(c->d.STRING_DECL_WITH_STRING.init_expr->d.STRING.str) - 2;
            }
            // unsigned int malloc_size = c->d.STRING_DECL_WITH_STRING.size->d.CONST.value;
            unsigned int init_size = strlen(c->d.STRING_DECL_WITH_STRING.init_expr->d.STRING.str) - 2;
            print_indent(depth + 1);
            printf(BLUE "Malloc Size:\n" RESET);
            print_indent(depth + 2);
            printf("%d\n", malloc_size);
            print_indent(depth + 1);
            printf(BLUE "Init String:\n" RESET);
            print_expr(c->d.STRING_DECL_WITH_STRING.init_expr, depth + 2);
            if(malloc_size < init_size)
                printf("Error: Array initialization exceeds declared size.\n");
            else
                printf("Legal init size\n");
        }
        printf("\n");
        break;
    case T_STRING_DECL_WITH_ARRAY:
        printf(RED "STRING_DECL(%s)\n" RESET, c->d.STRING_DECL_WITH_ARRAY.name);
        if (c->d.STRING_DECL_WITH_ARRAY.init_expr != NULL) {
            int malloc_size;
            if (c->d.STRING_DECL_WITH_ARRAY.size != -1){
                malloc_size = c->d.STRING_DECL_WITH_ARRAY.size->d.CONST.value;
            }
            else{
                struct expr_list *current = c->d.STRING_DECL_WITH_ARRAY.init_expr->exprs;
                int count = 0;
                while (current){
                    // printf("%s\n", current->expr->d.CHAR.c);
                    count++;
                    current = current->next;
                }
                
                malloc_size = count;
            }
            // int malloc_size = c->d.STRING_DECL_WITH_ARRAY.size->d.CONST.value;
            print_indent(depth + 1);
            printf(BLUE "Malloc Size:\n" RESET);
            print_indent(depth + 2);
            printf("%d\n", malloc_size);
            print_indent(depth + 1);
            printf(BLUE "Init String:\n" RESET);
            int list_size = print_char_list(c->d.STRING_DECL_WITH_ARRAY.init_expr, depth + 2);
            if(malloc_size < list_size)
                printf("Error: Array initialization exceeds declared size.\n");
            else
                printf("Legal init size\n");
        }
        printf("\n");
        break;
    case T_MULTI_VAR_DECL:
        printf(RED "DECLARATION\n" RESET);
        struct multi_var_decl *current = c->d.MULTI_VAR_DECL.vars;
        while (current != NULL) {
            print_var_decl(&current->var, depth + 1);
            current = current->next;
        }
        printf("\n");
        break;
    }
}
// void print_cmd(struct cmd *c, int depth) {
//     print_indent(depth);

//     switch (c->t) {
//     // For variable declaration
//     case T_DECL:
//         printf("DECL(%s)\n", c->d.DECL.name);
//         if (c->d.DECL.init_expr != NULL) {
//             print_indent(depth + 1);
//             printf("Init Expr:\n");
//             print_expr(c->d.DECL.init_expr, depth + 2);
//         }
//         break;
//     // For assignment
//     case T_ASGN:
//         printf("ASGN\n");
//         print_indent(depth + 1);
//         printf("Left:\n");
//         print_expr(c->d.ASGN.left, depth + 2);
//         print_indent(depth + 1);
//         printf("Right:\n");
//         print_expr(c->d.ASGN.right, depth + 2);
//         print_indent(depth);
//         printf("\n");
//         break;
//     // For sequential execution, omit printing SEQ() and replace with indentation for better formatting
//     case T_SEQ:
//         print_cmd(c->d.SEQ.left, depth);
//         print_cmd(c->d.SEQ.right, depth);
//         print_indent(depth);
//         break;
//     case T_IF:
//         printf("IF(\n");
//         print_indent(depth + 1);
//         printf("Condition:\n");
//         print_expr(c->d.IF.cond, depth + 2);
//         print_indent(depth + 1);
//         printf("True Branch:\n");
//         print_cmd(c->d.IF.left, depth + 2);
//         print_indent(depth + 1);
//         printf("False Branch:\n");
//         print_cmd(c->d.IF.right, depth + 2);
//         print_indent(depth);
//         printf(")\n");
//         break;
//     case T_WHILE:
//         printf("WHILE(\n");
//         print_indent(depth + 1);
//         printf("Condition:\n");
//         print_expr(c->d.WHILE.cond, depth + 2);
//         print_indent(depth + 1);
//         printf("Body:\n");
//         print_cmd(c->d.WHILE.body, depth + 2);
//         print_indent(depth);
//         printf(")\n");
//         break;
//     case T_WI:
//         printf("WRITE_INT(\n");
//         print_expr(c->d.WI.arg, depth + 1);
//         print_indent(depth);
//         printf(")\n");
//         break;
//     case T_WC:
//         printf("WRITE_CHAR(\n");
//         print_expr(c->d.WC.arg, depth + 1);
//         print_indent(depth);
//         printf(")\n");
//         break;
//     // For array declaration
//     case T_ARRAY_DECL:
//         printf("ARRAY_DECL(%s)\n", c->d.ARRAY_DECL.name);
//         if (c->d.ARRAY_DECL.size != NULL) {
//             print_indent(depth + 1);
//             printf("Size:\n");
//             print_expr(c->d.ARRAY_DECL.size, depth + 2);
//         }
//         if (c->d.ARRAY_DECL.init_expr != NULL) {
//             print_indent(depth + 1);
//             printf("Init Expr:\n");
//             print_init_list(c->d.ARRAY_DECL.init_expr, depth + 2);
//         }
//         break;
//     // For pointer declaration
//     case T_POINTER_DECL:
//         printf("POINTER_DECL(%s, level: %d)\n", c->d.POINTER_DECL.name, c->d.POINTER_DECL.pointer_level);
//         if (c->d.POINTER_DECL.size != NULL) {
//             print_indent(depth + 1);
//             printf("Size Expr:\n");
//             print_expr(c->d.POINTER_DECL.size, depth + 2);
//         }
//         break;
//     // For character type
//     case T_CHAR_DECL:
//         printf("CHAR_DECL(%s)\n", c->d.CHAR_DECL.name);
//         if (c->d.CHAR_DECL.init_expr != NULL) {
//             print_indent(depth + 1);
//             printf("Init Char:\n");
//             print_expr(c->d.CHAR_DECL.init_expr, depth + 2); // Increase indentation
//         }
//         break;
//     // For string declaration (initialized with double-quoted string)
//     case T_STRING_DECL_WITH_STRING:
//         printf("STRING_DECL(%s)\n", c->d.STRING_DECL_WITH_STRING.name);
//         if (c->d.STRING_DECL_WITH_STRING.init_expr != NULL) {
//             unsigned int malloc_size = c->d.STRING_DECL_WITH_STRING.size->d.CONST.value;
//             unsigned int init_size = strlen(c->d.STRING_DECL_WITH_STRING.init_expr->d.STRING.str) - 2;
//             print_indent(depth + 1);
//             printf("Malloc Size:\n");
//             print_indent(depth + 2);
//             printf("%d\n", malloc_size);
//             print_indent(depth + 1);
//             printf("Init String:\n");
//             print_expr(c->d.STRING_DECL_WITH_STRING.init_expr, depth + 2);
//             if (malloc_size < init_size)
//                 printf("Error: Array initialization exceeds declared size.\n");
//             else
//                 printf("Legal init size\n");
//         }
//         break;
//     // For string declaration (initialized with character array)
//     case T_STRING_DECL_WITH_ARRAY:
//         printf("STRING_DECL(%s)\n", c->d.STRING_DECL_WITH_ARRAY.name);
//         if (c->d.STRING_DECL_WITH_ARRAY.init_expr != NULL) {
//             int malloc_size = c->d.STRING_DECL_WITH_ARRAY.size->d.CONST.value;
//             print_indent(depth + 1);
//             printf("Malloc Size:\n");
//             print_indent(depth + 2);
//             printf("%d\n", malloc_size);

//             print_indent(depth + 1);
//             printf("Init String:\n");
//             int list_size = print_char_list(c->d.STRING_DECL_WITH_ARRAY.init_expr, depth + 2);
//             if (malloc_size < list_size)
//                 printf("Error: Array initialization exceeds declared size.\n");
//             else
//                 printf("Legal init size\n");
//         }
//         break;
//     // For single-statement multi-variable declaration
//     case T_MULTI_VAR_DECL:
//         printf("DECLARATION\n");
//         struct multi_var_decl *current = c->d.MULTI_VAR_DECL.vars;
//         while (current != NULL) {
//             print_var_decl(&current->var, depth + 1); 
//             current = current->next;
//         }
//         print_indent(depth);
//         printf("\n");
//         break;
//     default:
//         printf("Default");        
//     }

// }

// Build a natural number from a character array
unsigned int build_nat(char *c, int len) {
    unsigned int sum = 0;
    for (int index = 0; index < len; ++index) {
        if (sum > 429496729) {
            printf("We cannot handle natural numbers greater than 4294967295.\n");
            exit(0);
        }
        if (sum == 429496729 && c[index] > '5') {
            printf("We cannot handle natural numbers greater than 4294967295.\n");
            exit(0);
        }
        sum = sum * 10 + (c[index] - '0');
    }
    return sum;
}

// Allocate a new string
char *new_str(char *str, int len) {
    char *result = (char *) malloc(sizeof(char) * (len + 1));
    if (result == NULL) {
        printf("Failure in malloc.\n");
        exit(0);
    }
    strcpy(result, str);
    return result;
}