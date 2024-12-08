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

// 打印缩进, 使语法树美观
void print_indent(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("|--");
    }
}

struct expr * new_expr_ptr() {
  struct expr * res = (struct expr *) malloc(sizeof(struct expr));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

struct cmd * new_cmd_ptr() {
  struct cmd * res = (struct cmd *) malloc(sizeof(struct cmd));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
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

/**
 * 创建一个表示单个数组访问的表达式
 * 
 * @param array 表示数组的变量名
 * @param index 表示访问数组元素的索引表达式
 * @return 返回一个新的表达式指针，表示数组访问
 */
struct expr * TArray(char * array, struct expr * index) {
  struct expr * res = new_expr_ptr();
  res->t = T_ARRAY;
  res->d.ARRAY.array = array;
  res->d.ARRAY.index = index;
  return res;
}

/**
 * 创建一个表示多维数组访问的表达式
 * 
 * @param array 表示已经部分访问的数组表达式
 * @param index 表示当前维度的索引表达式
 * @return 返回一个新的表达式指针，表示多维数组的进一步访问
 */
struct expr *TMultiArray(struct expr *array, struct expr *index) {
    struct expr *res = new_expr_ptr();
    res->t = T_MULTI_ARRAY;
    res->d.multi_array.array = array;
    res->d.multi_array.index = index;
    return res;
}

/**
 * 创建一个表达式列表节点
 * 
 * @param expr 表示要添加到列表中的表达式
 * @return 返回一个新的表达式列表节点，其中包含提供的表达式
 */
struct expr_list *create_expr_list(struct expr *expr) {
    struct expr_list *new_list = malloc(sizeof(struct expr_list));
    if (!new_list) {
        return NULL;
    }
    new_list->expr = expr;
    new_list->next = NULL;
    return new_list;
}


/**
 * 创建一个初始化列表节点
 * 
 * @param expr_list 表示要添加到初始化列表中的表达式列表
 * @return 返回一个新的初始化列表节点，其中包含提供的表达式列表
 */
struct init_list *create_init_list(struct expr_list *expr_list) {
    struct init_list *new_list = malloc(sizeof(struct init_list));
    if (!new_list) {
        // 如果内存分配失败，返回NULL
        return NULL;
    }
    new_list->exprs = expr_list;
    return new_list;
}

/**
 * 将一个表达式附加到表达式列表的末尾
 * 
 * @param list 表示要附加表达式的列表
 * @param expr 表示要附加的表达式
 * @return 返回更新后的表达式列表
 */
struct expr_list *append_to_expr_list(struct expr_list *list, struct expr *expr) {
    struct expr_list *current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    struct expr_list *new_node = create_expr_list(expr);
    if (!new_node) {
        // 如果创建新节点失败，保持列表不变
        return list;
    }
    current->next = new_node;
    return list;
}

/**
 * 创建一个数组声明命令
 * 
 * @param name 表示数组的名称
 * @param size 表示数组的大小
 * @param init_expr 表示数组的初始化表达式列表
 * @return 返回一个新的命令指针，表示数组声明
 */
struct cmd * TArrDecl(char * name, struct expr * size, struct init_list * init_expr) {
  struct cmd * res = new_cmd_ptr();
  res->t = T_ARR_DECL;
  res->d.ARR_DECL.name = name;
  res->d.ARR_DECL.size = size;   
  res->d.ARR_DECL.init_expr = init_expr;
  return res;
}

/**
 * 创建一个字符串声明命令（使用双引号包围的字符串初始化）
 * 
 * @param name 表示字符串变量的名称
 * @param size 表示字符串的大小
 * @param init_expr 表示字符串初始化的表达式(双引号包围字符串)
 * @return 返回一个新的命令指针，表示字符串声明
 */
struct cmd * TStringDecl_String(char * name, struct expr * size, struct expr * init_expr) {
  struct cmd * res = new_cmd_ptr();
  res->t = T_STRING_DECL_STRING;
  res->d.STRING_DECL_STRING.name = name;
  res->d.STRING_DECL_STRING.size = size; 
  res->d.STRING_DECL_STRING.init_expr = init_expr;
  return res;
}

// 解析字符串类型，不人为指定大小，通过初始化列表确定大小
struct cmd * TStringDecl_String2(char * name, struct expr * init_expr) {
  struct cmd * res = new_cmd_ptr();
  res->t = T_STRING_DECL_STRING;
  res->d.STRING_DECL_STRING.name = name;
  res->d.STRING_DECL_STRING.size = -1;
  res->d.STRING_DECL_STRING.init_expr = init_expr;
  return res;
}

/**
 * 创建一个字符数组声明命令（使用字符列表初始化）
 * 
 * @param name 表示字符数组的名称
 * @param size 表示数组的大小
 * @param init_expr 表示字符数组初始化的字符列表
 * @return 返回一个新的命令指针，表示字符数组声明
 */
struct cmd * TStringDecl_Array(char * name, struct expr * size, struct init_list * init_expr) {
  struct cmd * res = new_cmd_ptr();
  res->t = T_STRING_DECL_ARRAY;
  res->d.STRING_DECL_ARRAY.name = name;
  res->d.STRING_DECL_ARRAY.size = size; 
  res->d.STRING_DECL_ARRAY.init_expr = init_expr;
  return res;
}

struct cmd * TStringDecl_Array2(char * name, struct init_list * init_expr) {
  struct cmd * res = new_cmd_ptr();
  res->t = T_STRING_DECL_ARRAY;
  res->d.STRING_DECL_ARRAY.name = name;
  res->d.STRING_DECL_ARRAY.size = -1;
  res->d.STRING_DECL_ARRAY.init_expr = init_expr;
  return res;
}

// 用于打印表达式列表相关信息
void print_expr_list(struct expr_list *list, int depth) {
    print_indent(depth);
    printf(BLUE "EXPR_LIST\n" RESET);

    struct expr_list *current = list;
    while (current != NULL) {
        print_expr(current->expr, depth + 1);
        if (current->next != NULL) {
            printf(",\n");
        }
        current = current->next;
    }
}
// void print_expr_list(struct expr_list *list, int depth) {
//     print_indent(depth);
//     printf("EXPR_LIST\n");

//     struct expr_list *current = list;
//     while (current != NULL) {
//         print_expr(current->expr, depth + 1);
//         if (current->next != NULL) {
//             printf(",\n");
//         }
//         current = current->next;
//     }

//     print_indent(depth);
//     printf("\n");
// }


// 一个辅助函数, 用于处理新的初始化列表
struct expr *new_expr(enum ExprType type, void *data) {
    struct expr *e = new_expr_ptr(); 
    e->t = type;
    switch (type) {
        case T_INIT_LIST:
            e->d.init_list = (struct init_list *)data;
            break;
    }
    return e;
}

// 用于打印初始化列表相关信息
void print_init_list(struct init_list *list, int depth) {
    struct expr_list *current = list->exprs;
    if (current == NULL) {
        print_indent(depth);
        printf("Empty List");
    }
    while (current != NULL) {
        print_expr(current->expr, depth);
        current = current->next;
    }
}
// void print_init_list(struct init_list *list, int depth) {
//     struct expr_list *current = list->exprs;
//     if (current == NULL)
//     {
//       print_indent(depth );
//       printf("Empty List");
//     }
//     while (current != NULL) {
//         print_expr(current->expr, depth);
//         current = current->next;
//     }

//     print_indent(depth);
//     printf("\n");
// }


// 用于打印字符列表相关信息
int print_char_list(struct init_list *list, int depth) {
    int list_size = 0;
    print_indent(depth);
    printf("CHAR_LIST\n");

    if (list == NULL) {
        print_indent(depth + 1);
        printf("NULL\n");
        return list_size;
    }

    struct expr_list *current = list->exprs;
    while (current != NULL) {
        print_indent(depth + 1);
        printf("CHAR('%c')\n", current->expr->d.CHAR.c[1]);
        current = current->next;
        list_size += 1;
    }

    return list_size;
}
// int print_char_list(struct init_list *list, int depth) {
//     int list_size = 0;
//     print_indent(depth);
//     printf(BLUE "CHAR_LIST\n" RESET);

//     if (list == NULL) {
//         print_indent(depth + 1);
//         printf("NULL\n");
//         return list_size;
//     }

//     struct expr_list *current = list->exprs;
//     while (current != NULL) {
//         print_indent(depth + 1);
//         printf("CHAR('%c')\n", current->expr->d.CHAR.c[1]);
//         current = current->next;
//         list_size += 1;
//     }

//     print_indent(depth);
//     printf("\n");
//     return list_size;
// }




/**
 * 创建一个指针声明命令。
 * 
 * @param name 指针变量的名称。
 * @param ptr_level 指针的级别(一级或多级)
 * @param size 如果是动态分配的指针，则表示分配的大小；如果为静态或未分配，则为NULL。
 * @return 返回一个新的命令指针，表示指针的声明。
 */
struct cmd * TPtrDecl(char * name, int ptr_level, struct expr * size) {
  struct cmd * res = new_cmd_ptr();
  res->t = T_PTR_DECL;
  res->d.PTR_DECL.name = name;
  res->d.PTR_DECL.ptr_level = ptr_level;
  if(size != NULL)
    res->d.PTR_DECL.size = TMalloc(size);
  else
    res->d.PTR_DECL.size = NULL;
  return res;
}

/**
 * 创建一个单字符常量表达式。
 * 
 * @param c 表示字符常量。
 * @return 返回一个新的表达式指针，表示字符常量。
 */
struct expr * TChar(char *c) {
    struct expr * res = new_expr_ptr();
    res->t = T_CHAR;
    res->d.CHAR.c = c;
    return res;
}

/**
 * 创建一个字符串常量表达式。
 * 
 * @param str 表示字符串常量。
 * @return 返回一个新的表达式指针，表示字符串常量。
 */
struct expr * TString(char *str) {
    struct expr * res = new_expr_ptr();
    res->t = T_STRING;
    res->d.STRING.str = str;  
    return res;
}

// 实现TCharDecl函数
struct cmd * TCharDecl(char *name, struct expr *init_expr) {
    struct cmd *res = new_cmd_ptr();
    res->t = T_CHAR_DECL;
    res->d.CHAR_DECL.name = name;
    res->d.CHAR_DECL.init_expr = init_expr;
    return res;
}



/**
 * 创建一个单语句多变量声明命令。
 * 
 * @param vars 指向变量声明列表的指针，列表中的每个元素都是一个变量声明。
 * @return 返回一个新的命令指针，表示多变量的声明。
 */
struct cmd * TMultiVarDecl(struct var_decl_list *vars) {
    struct cmd *res = new_cmd_ptr();
    res->t = T_MULTI_VAR_DECL; 
    res->d.MULTI_VAR_DECL.vars = vars;
    return res;
}


/**
 * 创建一个新的变量声明列表节点。
 * 
 * @param var 变量声明的结构体。
 * @return 返回一个新的变量声明列表节点。
 */
struct var_decl_list *create_var_decl_list(struct var_decl var) {
    struct var_decl_list *new_node = malloc(sizeof(struct var_decl_list));
    if (new_node == NULL) {
        printf("Failure in malloc.\n");
        exit(0);
    }
    new_node->var = var;
    new_node->next = NULL;
    return new_node;
}


/**
 * 将一个新的变量声明添加到现有的变量声明列表中。
 * 
 * @param list 现有的变量声明列表。
 * @param var 新的变量声明。
 * @return 返回更新后的变量声明列表。
 */
struct var_decl_list *append_to_var_decl_list(struct var_decl_list *list, struct var_decl var) {
    if (list == NULL) {
        return create_var_decl_list(var);
    }
    struct var_decl_list *current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = create_var_decl_list(var);
    return list;
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





void print_unop(enum UnOpType op, int depth) {
    print_indent(depth);

    switch (op) {
    case T_UMINUS:
        printf(BLUE "UMINUS\n" RESET);
        break;
    case T_NOT:
        printf(BLUE "NOT\n" RESET);
        break;
    }
}


// 用于打印各种表达式类型
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
    case T_MULTI_ARRAY:
        printf(BLUE "ARRAY\n" RESET);
        print_indent(depth + 1);
        printf(BLUE "Object:\n" RESET);
        print_expr(e->d.multi_array.array, depth + 2);
        print_indent(depth + 1);
        printf(BLUE "Index:\n" RESET);
        print_expr(e->d.multi_array.index, depth + 2);
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

// 用于打印变量声明相关信息
void print_var_decl(struct var_decl *var, int depth) {
    print_indent(depth);

    switch (var->type) {
    // 普通变量情形, 打印变量名以及初始值
    case VAR_SIMPLE:
        printf(BLUE "Object:\n" RESET);
        print_indent(depth + 1);
        printf(BLUE "VAR(%s)\n" RESET, var->name);
        print_indent(depth);
        printf(BLUE "Init Expr:\n" RESET);
        if (var->init_expr != NULL) {
            print_expr(var->init_expr, depth + 1);
        }
        else{
            print_indent(depth + 1);
            printf("None\n");
        }
        break;
    // 数组变量情形, 打印数组名, 索引以及初始化列表
    case VAR_ARRAY:
        printf(BLUE "Object:\n" RESET);
        print_indent(depth + 1);
        printf(BLUE "ARRAY(%s" RESET, var->name);
        struct expr_list *dimension = var->sizes;
        while (dimension != NULL) {
            if (dimension->expr) {
                printf(BLUE "[" RESET);
                printf(BLUE "CONST(%d)" RESET, dimension->expr->d.CONST.value);
                // print_expr(dimension->expr, 0);
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
        }
        else
        {
            print_indent(depth + 1);
            printf("None\n");
        }
        break;
    // 指针情形, 打印指针名, 层级以及初始化值
    case VAR_POINTER:
        printf(BLUE "Object:\n" RESET);
        print_indent(depth + 1);
        printf(BLUE "PTR(%s, level: %d)\n" RESET, var->name, var->ptr_level);
        print_indent(depth);
        printf(BLUE "Init Expr:\n" RESET);
        if (var->init_expr != NULL) {
            print_expr(var->init_expr, depth + 1);
        }
        else{
            print_indent(depth + 1);
            printf("None\n");
        }
        break;
    }
}

// 打印指令相关信息
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
        printf(")\n");
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
        printf(")\n");
        printf("\n");
        break;
    case T_WI:
        printf(RED "WRITE_INT(\n" RESET);
        print_expr(c->d.WI.arg, depth + 1);
        print_indent(depth);
        printf(")\n");
        printf("\n");
        break;
    case T_WC:
        printf(RED "WRITE_CHAR(\n" RESET);
        print_expr(c->d.WC.arg, depth + 1);
        print_indent(depth);
        printf(")\n");
        printf("\n");
        break;
    case T_ARR_DECL:
        printf(RED "ARR_DECL(%s)\n" RESET, c->d.ARR_DECL.name);
        if (c->d.ARR_DECL.size != NULL) {
            print_indent(depth + 1);
            printf(BLUE "Size:\n" RESET);
            print_expr(c->d.ARR_DECL.size, depth + 2);
        }
        if (c->d.ARR_DECL.init_expr != NULL) {
            print_indent(depth + 1);
            printf(BLUE "Init Expr:\n" RESET);
            print_init_list(c->d.ARR_DECL.init_expr, depth + 2);
        }
        printf("\n");
        break;
    case T_PTR_DECL:
        printf(RED "PTR_DECL(%s, level: %d)\n" RESET, c->d.PTR_DECL.name, c->d.PTR_DECL.ptr_level);
        if (c->d.PTR_DECL.size != NULL) {
            print_indent(depth + 1);
            printf(BLUE "Size Expr:\n" RESET);
            print_expr(c->d.PTR_DECL.size, depth + 2);
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
    case T_STRING_DECL_STRING:
        printf(RED "STRING_DECL(%s)\n" RESET, c->d.STRING_DECL_STRING.name);
        if (c->d.STRING_DECL_STRING.init_expr != NULL) {
            unsigned int malloc_size;
            if (c->d.STRING_DECL_STRING.size != -1){
                malloc_size = c->d.STRING_DECL_STRING.size->d.CONST.value;
            }
            else{
                malloc_size = strlen(c->d.STRING_DECL_STRING.init_expr->d.STRING.str) - 2;
            }
            // unsigned int malloc_size = c->d.STRING_DECL_STRING.size->d.CONST.value;
            unsigned int init_size = strlen(c->d.STRING_DECL_STRING.init_expr->d.STRING.str) - 2;
            print_indent(depth + 1);
            printf(BLUE "Malloc Size:\n" RESET);
            print_indent(depth + 2);
            printf("%d\n", malloc_size);
            print_indent(depth + 1);
            printf(BLUE "Init String:\n" RESET);
            print_expr(c->d.STRING_DECL_STRING.init_expr, depth + 2);
            if(malloc_size < init_size)
                printf("Error: Array initialization exceeds declared size.\n");
            else
                printf("Legal init size\n");
        }
        else{
            unsigned int malloc_size = c->d.STRING_DECL_STRING.size->d.CONST.value;
            print_indent(depth + 1);
            printf(BLUE "Malloc Size:\n" RESET);
            print_indent(depth + 2);
            printf("%d\n", malloc_size);
        }
        printf("\n");
        break;
    case T_STRING_DECL_ARRAY:
        printf(RED "STRING_DECL(%s)\n" RESET, c->d.STRING_DECL_ARRAY.name);
        if (c->d.STRING_DECL_ARRAY.init_expr != NULL) {
            int malloc_size;
            if (c->d.STRING_DECL_ARRAY.size != -1){
                malloc_size = c->d.STRING_DECL_ARRAY.size->d.CONST.value;
            }
            else{
                // 识别c->d.STRING_DECL_ARRAY.init_expr中单引号的数量
                // char *str = c->d.STRING_DECL_ARRAY.init_expr->exprs->expr->d.CHAR.c;
                struct expr_list *current = c->d.STRING_DECL_ARRAY.init_expr->exprs;
                int count = 0;
                while (current){
                    // printf("%s\n", current->expr->d.CHAR.c);
                    count++;
                    current = current->next;
                }
                
                malloc_size = count;
            }
            // int malloc_size = c->d.STRING_DECL_ARRAY.size->d.CONST.value;
            print_indent(depth + 1);
            printf(BLUE "Malloc Size:\n" RESET);
            print_indent(depth + 2);
            printf("%d\n", malloc_size);
            print_indent(depth + 1);
            printf(BLUE "Init String:\n" RESET);
            int list_size = print_char_list(c->d.STRING_DECL_ARRAY.init_expr, depth + 2);
            if(malloc_size < list_size)
                printf("Error: Array initialization exceeds declared size.\n");
            else
                printf("Legal init size\n");
        }
        printf("\n");
        break;
    case T_MULTI_VAR_DECL:
        printf(RED "DECLARATION\n" RESET);
        struct var_decl_list *current = c->d.MULTI_VAR_DECL.vars;
        while (current != NULL) {
            print_var_decl(&current->var, depth + 1);
            current = current->next;
        }
        printf("\n");
        break;
    }
}


unsigned int build_nat(char * c, int len) {
  int s = 0, i = 0;
  for (i = 0; i < len; ++i) {
    if (s > 429496729) {
      printf("We cannot handle natural numbers greater than 4294967295.\n");
      exit(0);
    }
    if (s == 429496729 && c[i] > '5') {
      printf("We cannot handle natural numbers greater than 4294967295.\n");
      exit(0);
    }
    s = s * 10 + (c[i] - '0');
  }
  return s;
}

char * new_str(char * str, int len) {
  char * res = (char *) malloc(sizeof(char) * (len + 1));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  strcpy(res, str);
  return res;
}

