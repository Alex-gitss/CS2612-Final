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
}

// Terminals
%token <n> TM_NAT
%token <i> TM_IDENT
%token <none> TM_LEFT_BRACE TM_RIGHT_BRACE
// 添加终结符
%token <none> TM_LEFT_BRACKET TM_RIGHT_BRACKET
%token <none> TM_LEFT_PAREN TM_RIGHT_PAREN
%token <none> TM_SEMICOL
%token <none> TM_COMMA
%token <none> TM_MALLOC TM_RI TM_RC TM_WI TM_WC
%token <none> TM_VAR TM_IF TM_THEN TM_ELSE TM_WHILE TM_DO TM_CHAR
%token <none> TM_ASGNOP
%token <none> TM_OR
%token <none> TM_AND
%token <none> TM_NOT
%token <none> TM_LT TM_LE TM_GT TM_GE TM_EQ TM_NE
%token <none> TM_PLUS TM_MINUS
%token <none> TM_MUL TM_DIV TM_MOD
// 字符常量
%token <single_char> TM_SINGLE_CHAR    
// 字符串常量
%token <i> TM_STRING  

// Nonterminals
%type <c> NT_WHOLE
%type <c> NT_CMD
%type <e> NT_EXPR_2
%type <e> NT_EXPR
// 指针级数
%type <n> NT_PTR_LEVEL
// 初始化列表
%type <init_list> NT_INIT_LIST
// 表达式列表
%type <e_list> NT_EXPR_LIST

// 初始化字符列表
%type <init_list> NT_INIT_CHAR_LIST
// 字符列表
%type <e_list> NT_CHAR_LIST

// 变量声明
%type <var_decl> NT_VAR_DECL
// 单语句多变量声明列表
%type <var_list> NT_VAR_LIST
// 多维数组索引
%type <sizes> NT_MULTI_ARR_SIZES


// Priority
%left TM_PLUS TM_MINUS
%left TM_MUL TM_DIV TM_MOD
%left TM_LT TM_LE TM_GT TM_GE TM_EQ TM_NE
%left TM_AND TM_OR
%nonassoc TM_LEFT_PAREN TM_RIGHT_PAREN
%nonassoc TM_LEFT_BRACE TM_RIGHT_BRACE
%right TM_SEMICOL TM_COMMA
%right TM_NOT
%left TM_LEFT_BRACKET


%%

NT_WHOLE:
  NT_CMD
  {
    $$ = ($1);
    root = $$;
  }
;

// 用于解析指针层级
NT_PTR_LEVEL:
  // 最初是1
  TM_MUL
  {
    $$ = 1;
  }
  // 每多一级, 递增1
  | TM_MUL NT_PTR_LEVEL
  {
    $$ = $2 + 1;
  }
;

// 调用create_init_list函数, 解析初始化列表
NT_INIT_LIST:
    TM_LEFT_BRACE NT_EXPR_LIST TM_RIGHT_BRACE
    {
        $$ = create_init_list($2);
    }
;

// 解析表达式列表
NT_EXPR_LIST:
// 空列表, 返回NULL
    {
        $$ = NULL;
    }
// 单个表达式情形, 调用create_expr_list创建列表
| NT_EXPR
    {
        $$ = create_expr_list($1);
    }
// 多个表达式情形, 调用append_to_expr_list向其中添加新表达式
| NT_EXPR_LIST TM_COMMA NT_EXPR
    {
        $$ = append_to_expr_list($1, $3);
    }
// 本身就是初始化列表, 直接调用create_expr_list函数即可
| NT_INIT_LIST
    {
        $$ = create_expr_list(new_expr(T_INIT_LIST, $1));
    }
// 表达式列表后跟随初始化列表, 向其中添加即可
| NT_EXPR_LIST TM_COMMA NT_INIT_LIST
    {
        $$ = append_to_expr_list($1, new_expr(T_INIT_LIST, $3));
    }
;

// 解析初始字符列表, 复用create_init_list函数
NT_INIT_CHAR_LIST:
    TM_LEFT_BRACE NT_CHAR_LIST TM_RIGHT_BRACE
    {
        $$ = create_init_list($2);
    }
;

// 解析字符列表
NT_CHAR_LIST:
// 单个字符情形
TM_SINGLE_CHAR
{
    $$ = create_expr_list(TChar($1));
}
// 字符串情形
| NT_CHAR_LIST TM_COMMA TM_SINGLE_CHAR
{
    $$ = append_to_expr_list($1, TChar($3));
}
;

// 用于解析多维数组索引部分
NT_MULTI_ARR_SIZES:
// 明确说明大小情形
TM_LEFT_BRACKET NT_EXPR TM_RIGHT_BRACKET 
  { 
    $$ = create_expr_list($2); 
  }
// 新维度, 说明了大小
| NT_MULTI_ARR_SIZES TM_LEFT_BRACKET NT_EXPR TM_RIGHT_BRACKET 
  {  
    $$ = append_to_expr_list($1, $3); 
  }
;

// 变量的声明, 包含了单语句多变量, 也包含数组, 指针等等
NT_VAR_DECL:
// 单个变量声明, 无初值
  TM_IDENT
  {
    $$ = (struct var_decl){ .name = $1, .type = VAR_SIMPLE, .sizes = NULL, .ptr_level = 0 };
  }
// 单个变量声明及初始化
| TM_IDENT TM_ASGNOP NT_EXPR
  {
    $$ = (struct var_decl){ .name = $1, .type = VAR_SIMPLE, .init_expr = $3 };
  }
// 数组(一维或多维)声明, 无初值
| TM_IDENT NT_MULTI_ARR_SIZES
  {
    $$ = (struct var_decl){ .name = $1, .type = VAR_ARRAY, .sizes = $2, .ptr_level = 0 };
  }
// 数组(一维或多维)声明, 以及初始化
| TM_IDENT NT_MULTI_ARR_SIZES TM_ASGNOP NT_INIT_LIST
  {
    $$ = (struct var_decl){ .name = $1, .type = VAR_ARRAY, .sizes = $2, .ptr_level = 0, .init_expr_list = $4 };
  }
// 指针类型, 一级或多级指针
| NT_PTR_LEVEL TM_IDENT
  {
    $$ = (struct var_decl){ .name = $2, .type = VAR_POINTER, .sizes = NULL, .ptr_level = $1 };
  }
;

// 解析多变量列表
NT_VAR_LIST:
// 单个变量情形
  NT_VAR_DECL
  {
    $$ = create_var_decl_list($1);
  }
// 多变量, 递归解析
| NT_VAR_LIST TM_COMMA NT_VAR_DECL
  {
    $$ = append_to_var_decl_list($1, $3);
  }
;

// 解析指令类型
NT_CMD:
NT_EXPR TM_ASGNOP NT_EXPR
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
// 解析动态数组初始化, malloc
| TM_VAR NT_PTR_LEVEL TM_IDENT TM_ASGNOP TM_MALLOC TM_LEFT_PAREN NT_EXPR TM_RIGHT_PAREN
  {
    // $2 是指针级别
    $$ = TPtrDecl($3, $2, $7); 
  } 
| TM_CHAR TM_IDENT 
  {
    $$ = TCharDecl($2, NULL); // 创建一个不带初始化的字符变量声明
  }
  | TM_CHAR TM_IDENT TM_ASGNOP TM_SINGLE_CHAR 
  {
    $$ = TCharDecl($2, TChar($4)); // 创建一个带有初始化的字符变量声明
  }
// 解析字符串类型, 规定了大小
| TM_CHAR TM_IDENT TM_LEFT_BRACKET NT_EXPR TM_RIGHT_BRACKET 
  {
      $$ = TStringDecl_String($2, $4, NULL); 
  }
// 解析字符串类型, 规定了大小, 并以双引号包围字符串初始化
| TM_CHAR TM_IDENT TM_LEFT_BRACKET NT_EXPR TM_RIGHT_BRACKET TM_ASGNOP TM_STRING
  {
      $$ = TStringDecl_String($2, $4, TString($7)); 
  }
// 解析字符串类型, 规定了大小, 并以字符列表初始化
| TM_CHAR TM_IDENT TM_LEFT_BRACKET NT_EXPR TM_RIGHT_BRACKET TM_ASGNOP NT_INIT_CHAR_LIST
  {
      $$ = TStringDecl_Array($2, $4, $7); 
  }
// 变量的声明, 单/多变量, 进一步在NT_VAR_LIST中解析
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
// 单字符情形
| TM_SINGLE_CHAR
  {
      $$ = TChar($1);
  }
// 字符串情形
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
// 多维数组情形
| NT_EXPR_2 TM_LEFT_BRACKET NT_EXPR TM_RIGHT_BRACKET
  {
    $$ = (TMultiArray($1, $3)); // 多维数组访问
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
