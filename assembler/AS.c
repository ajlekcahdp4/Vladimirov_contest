#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lexer.h"
#include "parser.h"





int main ()
{
    char *buf = NULL;
    Input (&buf);
    struct lex_array_t *lex = lex_string (buf);
    free (buf);
    Translate (lex);
    

    free(lex->lexarr);
    free(lex);

    return 0;
}

