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
  // 这个T_VAR做了修改, 支持1, 2, ... 多个变量, 作为一个整体
  T_VAR,
  T_BINOP,
  T_UNOP,
  T_DEREF,
  T_MALLOC,
  T_RI,
  T_RC,
  // 数组类型
  T_ARRAY,
  // 字符常量类型
  T_CHAR,    
  // 字符串常量
  T_STRING,  
  // 初始化列表类型
  T_INIT_LIST, 
  // 多维数组类型类型
  T_MULTI_ARRAY
};

enum CmdType {
  T_DECL = 0,
  T_ASGN,
  T_SEQ,
  T_IF,
  T_WHILE,
  T_WI,
  T_WC,
  // 数组声明指令
  T_ARR_DECL,
  // 指针声明指令
  T_PTR_DECL,
  // 字符变量声明
  T_CHAR_DECL,  
  // 用双引号包围的字符串初始化字符串指令
  T_STRING_DECL_STRING,
  // 用字符数组初始化字符串指令
  T_STRING_DECL_ARRAY,
  // 单语句多变量声明指令
  T_MULTI_VAR_DECL
};

// 表达式列表类型
struct expr_list {
    // 当前表达式的指针
    struct expr *expr;
    // 表达式列表的下一个结点指针
    struct expr_list *next;
};

// 初始化列表类型
struct init_list {
    // 指向表达式链表的指针
    struct expr_list *exprs; 
};

// 为了实现单语句多变量声明, 辅助用的数据结构
struct var_decl {
    char *name;
    enum { VAR_SIMPLE, VAR_ARRAY, VAR_POINTER } type;
    // 用于数组的大小
    struct expr_list *sizes; 
    //用于指针的层数
    int ptr_level; 
    // 用于存储多维数组的维度数量
    int dimensions; 
    // 初始化表达式
    struct expr *init_expr; 
    // 初始化表达式列表
    struct init_list *init_expr_list; 
};

// 将多个var_decl类型作为结点连接为链表, 形成单语句多变量声明列表
struct var_decl_list {
    struct var_decl var;
    struct var_decl_list *next;
};

// 用于单语句多变量声明的解析
struct cmd * TMultiVarDecl(struct var_decl_list *vars);
// 用于初始化一个多变量列表
struct var_decl_list *create_var_decl_list(struct var_decl var);
// 用于向多变量列表中添加新的变量
struct var_decl_list *append_to_var_decl_list(struct var_decl_list *list, struct var_decl var);



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
    // 数组类型字段
    struct { char * array; struct expr * index; } ARRAY;
    // 字符常量字段
    struct { char *c; } CHAR;   
    // 字符串常量字段
    struct { char *str; } STRING;
    // 初始化列表字段 
    struct init_list *init_list; 
    // 多维数组字段
    struct {
        struct expr *array;
        struct expr *index;
    } multi_array;
  } d;
};

struct cmd {
  enum CmdType t;
  union {
    // 该DECL指令做了修改, 支持1, 2, ... 多个变量的声明
    struct {char * name; struct expr * init_expr; } DECL; 
    struct {struct expr * left; struct expr * right; } ASGN;
    struct {struct cmd * left; struct cmd * right; } SEQ;
    struct {struct expr * cond; struct cmd * left; struct cmd * right; } IF;
    struct {struct expr * cond; struct cmd * body; } WHILE;
    struct {struct expr * arg; } WI;
    struct {struct expr * arg; } WC;
    // 用于声明数组
    struct { char * name; struct expr * size; struct init_list * init_expr; } ARR_DECL; 
    // 用于声明指针类型
    struct { char * name; int ptr_level; struct expr * size;} PTR_DECL; 
    // 字符变量声明
    struct { char * name; struct expr * init_expr; } CHAR_DECL; 
    // 用于以双引号包围的字符串初始化字符串指令
    struct { char * name; struct expr * size; struct expr * init_expr;} STRING_DECL_STRING;
    // 用于以字符数组初始化字符串指令
    struct { char * name; struct expr * size; struct init_list * init_expr;} STRING_DECL_ARRAY;
    // 用于多变量声明指令
    struct { struct var_decl_list * vars;} MULTI_VAR_DECL; 
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
// 拓展了函数功能, 可以声明多个变量
struct cmd * TDecl(char * name, struct expr * init_expr);
struct cmd * TAsgn(struct expr * left, struct expr * right);
struct cmd * TSeq(struct cmd * left, struct cmd * right);
struct cmd * TIf(struct expr * cond, struct cmd * left, struct cmd * right);
struct cmd * TWhile(struct expr * cond, struct cmd * body);
struct cmd * TWriteInt(struct expr * arg);
struct cmd * TWriteChar(struct expr * arg);
// 用于构造数组
struct cmd * TArrDecl(char * name, struct expr * size, struct init_list * init_expr);
// 用于字符声明
struct cmd * TCharDecl(char * name, struct expr * init_expr);
// 用于构造字符串, 分别以引号包围的字符串和字符列表初始化
struct cmd * TStringDecl_String(char * name, struct expr * size, struct expr * init_expr);
struct cmd * TStringDecl_Array(char * name, struct expr * size, struct init_list * init_expr);
// 用于初始化表达式列表和声明初始化列表, 以及向表达式中添加新的表达式
struct expr_list *create_expr_list(struct expr *expr);
struct init_list *create_init_list(struct expr_list *expr_list);
struct expr_list *append_to_expr_list(struct expr_list *list, struct expr *expr);

// 用于构造指针
struct cmd * TPtrDecl(char * name, int ptr_level, struct expr * size);

// 用于构造数组和多维数组
struct expr * TArray(char * array, struct expr * index);
struct expr *TMultiArray(struct expr *array, struct expr *index);

// 用于构造新的表达式
struct expr *new_expr(enum ExprType type, void *data);

// 用于构造单个字符
// char *是因为输入为"'a'"
struct expr * TChar(char *c);
// 用于构造字符串
struct expr * TString(char *str);


void print_binop(enum BinOpType op, int depth);
void print_unop(enum UnOpType op, int depth);
void print_expr(struct expr * e, int depth);
void print_cmd(struct cmd * c, int depth);

unsigned int build_nat(char * c, int len);
char * new_str(char * str, int len);

#endif // LANG_H_INCLUDED
