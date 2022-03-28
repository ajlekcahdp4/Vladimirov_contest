#include <stdio.h>
#include <stdlib.h>

#include "lexer/lexer.h"
#include "parser/parser.h"

int main ()
{
    char *buf = 0;
    struct lex_array_t *lex = 0;
    struct node_t *top = NULL;

    Input (&buf);
    
    lex = lex_string (buf);
    if (lex->size <= 0)
        return 0;

    top = build_syntax_tree (*lex);
    if (top == NULL)
        return 0;
    
    tree_dump (top);
    
    printf ("%d\n", calc_result (top));
    free_syntax_tree (top);
    End (buf, lex);
    return 0;
}
