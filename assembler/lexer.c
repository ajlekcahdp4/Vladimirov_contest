#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"


#define START_SIZE 32
size_t Input (char **buf)
{
    char c = 0;
    size_t i   = 0;
    size_t len = START_SIZE;

    *buf = calloc (len, sizeof(char));
    assert (*buf);
    c = getchar ();
    while (c != EOF)
    {
        if (i == len)
        {
            size_t j = len;
            len *= 2;
            *buf = realloc (*buf, len * sizeof(char));
            while (j < len)
            {
                if (*buf[j] != '\0')
                    *buf[j] = '\0';
            }
        }
        (*buf)[i] = c;
        i += 1;
        c = getchar ();
    }
    return i;
}
#undef START_SIZE

struct lex_array_t *lex_resize (struct lex_array_t *lex)
{
    lex->capacity = 2 * lex->capacity;
    lex->lexarr = realloc (lex->lexarr, lex->capacity * sizeof (struct lexem_t));
    assert (lex->lexarr);
    return lex;
}

int number_input (const char *buf, int *i)
{
    int *val = NULL;
    if (isdigit (buf[*i]))
        val = calloc (1, sizeof (int));
    while (isdigit (buf[*i]))
    {
        *val = *val * 10 + buf[*i] - '0';
        *i += 1;
    }
    if (val == NULL || !isspace (buf[*i]))
    {
        fprintf (stderr, "ERROR\n");
        exit(0);
    }
    return *val;
}


int lex_insert (struct lex_array_t *lex, const char *buf, int i, int ip)
{
    while (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n')
        i += 1;
    if (buf[i] == 0)
        return i;
    if (strncmp (buf + i, "MOVI", 4) == 0)
    {
        lex->lexarr[ip].kind = CMD;
        lex->lexarr[ip].lex.CMD = MOVI;
        lex->size += 1;
        i += 4;
        if (!isspace(buf[i]))
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
    }
    else if (strncmp (buf + i, "ADD", 3) == 0)
    {
        lex->lexarr[ip].kind = CMD;
        lex->lexarr[ip].lex.CMD = ADD;
        lex->size += 1;
        i += 3;
        if (!isspace(buf[i]))
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
    }
    else if (strncmp (buf + i, "SUB", 3) == 0)
    {
        lex->lexarr[ip].kind = CMD;
        lex->lexarr[ip].lex.CMD = SUB;
        lex->size += 1;
        i += 3;
        if (!isspace(buf[i]))
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
    }
    else if (strncmp (buf + i, "MUL", 3) == 0)
    {
        lex->lexarr[ip].kind = CMD;
        lex->lexarr[ip].lex.CMD = MUL;
        lex->size += 1;
        i += 3;
        if (!isspace(buf[i]))
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
    }
    else if (strncmp (buf + i, "DIV", 3) == 0)
    {
        lex->lexarr[ip].kind = CMD;
        lex->lexarr[ip].lex.CMD = DIV;
        lex->size += 1;
        i += 3;
        if (!isspace(buf[i]))
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
    }
    else if (strncmp (buf + i, "IN", 2) == 0)
    {
        lex->lexarr[ip].kind = CMD;
        lex->lexarr[ip].lex.CMD = IN;
        lex->size += 1;
        i += 2;
        if (!isspace(buf[i]))
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
    }    
    else if (strncmp (buf + i, "OUT", 3) == 0)
    {
        lex->lexarr[ip].kind = CMD;
        lex->lexarr[ip].lex.CMD = OUT;
        lex->size += 1;
        i += 3;
        if (!isspace(buf[i]))
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
    }
    else if (buf[i] == 'A')
    {
        lex->lexarr[ip].kind = REG;
        lex->lexarr[ip].lex.REG = A;
        lex->size += 1;
        if (!isspace(buf[i]))
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
    }
    else if (buf[i] == 'B')
    {
        lex->lexarr[ip].kind = REG;
        lex->lexarr[ip].lex.REG = B;
        lex->size += 1;
        i += 1;
        if (!isspace(buf[i]))
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
    }
    else if (buf[i] == 'C')
    {
        lex->lexarr[ip].kind = REG;
        lex->lexarr[ip].lex.REG = C;
        lex->size += 1;
        i += 1;
        if (!isspace(buf[i]))
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
    }
    else if (buf[i] == 'D')
    {
        lex->lexarr[ip].kind = REG;
        lex->lexarr[ip].lex.REG = D;
        lex->size += 1;
        i += 1;
        if (!isspace(buf[i]))
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
    }
    else
    {
        lex->lexarr[ip].kind = VAL;
        lex->lexarr[ip].lex.val = number_input (buf, &i);
        lex->size += 1;
    }
    return i;
} 




struct lex_array_t *lex_string (const char *buf)
{
    int ip = 0;
    int size = 0;
    struct lex_array_t *lex = calloc (1, sizeof (struct lex_array_t));
    lex->lexarr = calloc (16, sizeof (struct lexem_t));
    lex->capacity = 16;
    assert (lex);
    assert (lex->lexarr);
    lex->capacity = 16;

    for (int i = 0; buf[i] != '\0' && buf[i] != EOF && buf[i] != '\n'; )
    {
        if (lex->size == lex->capacity)
            lex_resize (lex);
        i = lex_insert (lex, buf, i, ip);
    }
    lex->size = size;
    return lex;
}