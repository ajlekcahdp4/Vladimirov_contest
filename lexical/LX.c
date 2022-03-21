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

int number_input (const char *buf, int *i);
void print_lex (struct lex_array_t *lex);
int skip_spaces (const char* buf, int ip);
int Input (char **buf, char *filename);
void End (char *buf, struct lex_array_t *lex);
int lex_insert (struct lex_array_t *lex, const char *buf, int i, int ip);
struct lex_array_t *lex_string (const char *buf);

int number_input (const char *buf, int *i)
{
    int val = 0;
    while (isdigit (buf[*i]))
    {
        val = val * 10 + buf[*i] - '0';
        *i += 1;
    }
    return val;
}

int skip_spaces (const char* buf, int ip)
{
    while (buf[ip] == ' ' || buf[ip] == '\t' || buf[ip] == '\n' || buf[ip] == '\r')
        ip += 1;
    return ip;
}

int Input (char **buf, char *filename)
{
    int char_num = 0;
    FILE *f = fopen (filename, "r");
    assert (f);

    struct stat stat_buf;
    stat(filename, &stat_buf);
    char_num = (int)stat_buf.st_size;

    *buf = calloc ((size_t)(char_num + 1), sizeof (char));
    fread (*buf, sizeof(char), (size_t)char_num, f);
    printf ("%s\n", *buf);

    fclose (f);

    return char_num;
}

void End (char *buf, struct lex_array_t *lex)
{
    free (lex->lexems);
    free (lex);
    free (buf);
}


void print_lex (struct lex_array_t *lex)
{
    for (int i = 0; i < lex->size; i++)
    {
        switch (lex->lexems[i].kind )
        {
        case BRACE:
            switch (lex->lexems[i].lex.b)
            {
                case LBRAC:
                    printf ("LBRAC ");
                    break;
                case RBRAC:
                    printf ("RBRAC ");
                    break;
                default:
                    printf ("ERROR\n");
                    abort ();
                    break;
            }
            break;
        case OP:
            switch (lex->lexems[i].lex.op)
            {
                case ADD:
                    printf ("PLUS ");
                    break;
                case SUB:
                    printf ("MINUS ");
                    break;
                case MUL:
                    printf ("MUL ");
                    break;
                case DIV:
                    printf ("DIV ");
                    break;
                default:
                    printf ("ERROR\n");
                    abort ();
                    break;
            }
            break;
        case NUM:
            printf ("NUMBER:%d ", lex->lexems[i].lex.num);
            break;
        default:
            printf ("ERROR\n");
            abort ();
            break;
        }   
    }
    printf ("\n");

}

int lex_insert (struct lex_array_t *lex, const char *buf, int i, int ip)
{
    i = skip_spaces (buf, i);

    if (buf[i] == '(')
    {
        lex->size += 1;
        lex->lexems[ip].kind  = BRACE;
        lex->lexems[ip].lex.b = LBRAC;
    }
    else if (buf[i] == ')')
    {
        lex->size += 1;
        lex->lexems[ip].kind  = BRACE;
        lex->lexems[ip].lex.b = RBRAC;
    }
    else if (buf[i] == '*')
    {
        lex->size += 1;
        lex->lexems[ip].kind   = OP;
        lex->lexems[ip].lex.op = MUL;
    }
    else if (buf[i] == '/')
    {
        lex->size += 1;
        lex->lexems[ip].kind   = OP;
        lex->lexems[ip].lex.op = DIV;
    }
    else if (buf[i] == '+')
    {
        lex->size += 1;
        lex->lexems[ip].kind   = OP;
        lex->lexems[ip].lex.op = ADD;
    }
    else if (buf[i] == '-')
    {
        lex->size += 1;
        lex->lexems[ip].kind   = OP;
        lex->lexems[ip].lex.op = SUB;
    }
    else if (isdigit (buf[i]))
    {
        lex->size += 1;
        lex->lexems[ip].kind = NUM;
        lex->lexems[ip].lex.num = number_input (buf, &i);
    }
    else
    {
        return -1;
    }
    return i;
} 

struct lex_array_t *lex_string (const char *buf)
{
    int ip = 0;
    int size = 0;
    struct lex_array_t *lex = calloc (1, sizeof (struct lex_array_t));
    lex->lexems   = calloc (16, sizeof (struct lexem_t));
    lex->capacity = 16;
    size = 0;
    ip = 0;

    for (int i = 0; buf[i] != '\0' && buf[i] != EOF; i++)
    {
        i = lex_insert (lex, buf, i, ip);
        if (i == -1)
        {
            printf ("ERROR\n");
            abort ();
        }
        size += 1;
        ip += 1;
    }
    lex->size = size;
    return lex;
}

int main (int argc, char **argv)
{
    char *buf = 0;
    struct lex_array_t *lex = 0;

    Input (&buf, argv[argc - 1]);
    
    lex = lex_string (buf);

    print_lex (lex);
    
    End (buf, lex);
    return 0;
}