#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

enum lexem_kind_t { OP, BRACE, NUM };
enum operation_t { ADD, SUB, MUL, DIV };
enum braces_t { LBRAC, RBRAC };

struct lexem_t {
    enum lexem_kind_t kind;
    union {
        enum operation_t op;
        enum braces_t b;
        int num;
    } lex;
};

struct lex_array_t {
    struct lexem_t *lexems;
    int size;
    int capacity;
};

int number_input (const char *buf)
{
    size_t i = 0;
    int val = 0;
    while (isdigit (buf[i]))
    {
        val = val * 10 + buf[i] - '0';
        i += 1;
    }
    return val;
}

size_t skip_spaces (const char* buf, size_t ip)
{
    while (buf[ip] == ' ' || buf[ip] == '\t' || buf[ip] == '\n' || buf[ip] == '\r')
        ip += 1;
    return ip;
}

size_t Input (char **buf, char *filename)
{
    FILE *f = fopen (filename, "r");

    struct stat stat_buf;
    stat(filename, &stat_buf);
    size_t char_num = stat_buf.st_size;

    *buf = calloc (char_num, sizeof (char));
    fread (*buf, sizeof(char), char_num, f);
    printf ("%s\n", *buf);

    fclose (f);

    return char_num;
}

void End (char *buf, size_t char_num)
{

    free (buf);
}


size_t lex_insert (struct lex_array_t *lex, const char *buf, size_t ip)
{
    ip = skip_spaces (buf, ip);

    if (buf[ip] == '(')
    {
        lex->size += 1;
        lex->lexems[ip].kind  = BRACE;
        lex->lexems[ip].lex.b = LBRAC;
    }
    else if (buf[ip] == ')')
    {
        lex->size += 1;
        lex->lexems[ip].kind  = BRACE;
        lex->lexems[ip].lex.b = RBRAC;
    }
    else if (buf[ip] == '*')
    {
        lex->size += 1;
        lex->lexems[ip].kind   = OP;
        lex->lexems[ip].lex.op = MUL;
    }
    else if (buf[ip] == '/')
    {
        lex->size += 1;
        lex->lexems[ip].kind   = OP;
        lex->lexems[ip].lex.op = DIV;
    }
    else if (buf[ip] == '+')
    {
        lex->size += 1;
        lex->lexems[ip].kind   = OP;
        lex->lexems[ip].lex.op = ADD;
    }
    else if (buf[ip] == '-')
    {
        lex->size += 1;
        lex->lexems[ip].kind   = OP;
        lex->lexems[ip].lex.op = SUB;
    }
    else if (isdigit (buf[ip]))
    {
        lex->size += 1;
        lex->lexems[ip].kind = NUM;
        lex->lexems[ip].lex.num = number_input (buf + ip);
    }
    else
    {
        return 666;
    }
    return ip;
} 

struct lex_array_t *lex_string (const char *buf, size_t char_num)
{
    struct lex_array_t *lex = calloc (1, sizeof (struct lex_array_t));
    lex->lexems   = calloc (16, sizeof (struct lexem_t));
    lex->capacity = 16;

    for (size_t i = 0; i < char_num; i++)
    {
        i = lex_insert (lex, buf, i);
        if (i == -1)
        {
            lex = 0;
            break;
        }
    }
    return lex;
}

int main (int argc, char **argv)
{
    char *buf = 0;
    size_t char_num = Input (&buf, argv[argc - 1]);
    struct lex_array_t *lex = 0;
    lex = lex_string (buf, char_num);
    if (lex == 0)
    {
        printf ("ERROR\n");
        abort();
    }
    
    End (buf, char_num);
    return 0;
}