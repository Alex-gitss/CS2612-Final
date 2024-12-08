#include <stdio.h>
#include "lang.h"
#include "lexer.h"
#include "parser.h"

extern struct cmd * root;
int yyparse();

int main(int argc, char **argv) {
    //yyin = stdin;
    yyin = fopen(argv[1], "rb");
    yyparse();
    fclose(yyin);
    print_cmd(root, 0);
}
