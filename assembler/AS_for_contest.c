#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

//=====================================================================================
//======================================lexer.h=======================================
//=====================================================================================
enum reg_t {  A = 0, B, C, D, RLAST };

enum opcode_t { MOVI = 0, ADD = 8, SUB = 9, MUL = 10, DIV = 11, IN, OUT };

enum lexem_kind { CMD, REG, VAL };

struct lexem_t 
{
    union 
    {
        enum opcode_t CMD;
        enum reg_t REG;
        int val;
    }lex;
    enum lexem_kind kind;
};

struct lex_array_t 
{
    struct lexem_t *lexarr;
    size_t capacity;
    size_t size;
};

//=====================================================================================
//======================================lexer.c========================================
//=====================================================================================

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
            #if 1
            while (j < len)
            {
                if ((*buf)[j] != '\0')
                    (*buf)[j] = '\0';
                j++;
            }
            #endif
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

int *number_input (const char *buf, size_t *i)
{
    int *val = NULL;
    if (isdigit (buf[*i]))
        val = calloc (1, sizeof (int));
    while (isdigit (buf[*i]))
    {
        *val = *val * 10 + buf[*i] - '0';
        *i += 1;
    }
    if (val == NULL)
    {
        fprintf (stderr, "ERROR\n");
        exit(0);
    }
    return val;
}



void print_lex (struct lex_array_t *lex)
{
    printf("\n\nLEXEMS:\n");
    for (size_t i = 0; i < lex->size; i++)
    {
        switch (lex->lexarr[i].kind )
        {
        case CMD:
            switch (lex->lexarr[i].lex.CMD)
            {
                case MOVI:
                    printf ("MOVI ");
                    break;
                case ADD:
                    printf ("ADD ");
                    break;
                case SUB:
                    printf ("SUB ");
                    break;
                case MUL:
                    printf ("MUL ");
                    break;
                case DIV:
                    printf ("DIV ");
                    break;
                case IN:
                    printf ("IN ");
                    break;
                case OUT:
                    printf ("OUT ");
                    break;
                default:
                    printf ("ERROR\n");
                    break;
            }
            break;
        case REG:
            switch (lex->lexarr[i].lex.REG)
            {
                case A:
                    printf ("A ");
                    break;
                case B:
                    printf ("B ");
                    break;
                case C:
                    printf ("C ");
                    break;
                case D:
                    printf ("D ");
                    break;
                default:
                    printf ("ERROR\n");
                    break;
            }
            break;
        case VAL:
            printf ("%d ", lex->lexarr[i].lex.val);
            break;
        default:
            printf ("ERROR\n");
            break;
        }   
    }
    printf ("\n\n");

}

size_t lex_insert (struct lex_array_t *lex, const char *buf, size_t old_i, size_t ip)
{
    size_t i = old_i;
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
        i += 1;
        if (!isspace(buf[i]) && buf[i] != ',' && buf[i] != '\0' && buf[i] != '\n')
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
        if (buf[i] == ',')
            i += 1;
    }
    else if (buf[i] == 'B')
    {
        lex->lexarr[ip].kind = REG;
        lex->lexarr[ip].lex.REG = B;
        lex->size += 1;
        i += 1;
        if (!isspace(buf[i]) && buf[i] != ',' && buf[i] != '\0' && buf[i] != '\n')
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
        if (buf[i] == ',')
            i += 1;
    }
    else if (buf[i] == 'C')
    {
        lex->lexarr[ip].kind = REG;
        lex->lexarr[ip].lex.REG = C;
        lex->size += 1;
        i += 1;
        if (!isspace(buf[i]) && buf[i] != ',' && buf[i] != '\0' && buf[i] != '\n')
        {
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
        if (buf[i] == ',')
            i += 1;
    }
    else if (buf[i] == 'D')
    {
        lex->lexarr[ip].kind = REG;
        lex->lexarr[ip].lex.REG = D;
        lex->size += 1;
        i += 1;
        if (!isspace(buf[i]) && buf[i] != ',' && buf[i] != '\0' && buf[i] != '\n')
        {
            printf ("\n<%d>\n", buf[i]);
            fprintf(stderr, "ERROR\n");
            exit(0);
        }
        if (buf[i] == ',')
            i += 1;
    }
    else
    {
        int *val = NULL;
        lex->lexarr[ip].kind = VAL;
        val = number_input (buf, &i);
        lex->lexarr[ip].lex.val = *val;
        free (val);
        lex->size += 1;
    }
    return i;
} 




struct lex_array_t *lex_string (const char *buf)
{
    int ip = 0;
    struct lex_array_t *lex = calloc (1, sizeof (struct lex_array_t));
    lex->lexarr = calloc (16, sizeof (struct lexem_t));
    assert (lex);
    assert (lex->lexarr);
    lex->capacity = 16;

    for (size_t i = 0; buf[i] != '\0' && buf[i] != EOF; ip++ )
    {
        if (lex->size == lex->capacity)
            lex_resize (lex);
        i = lex_insert (lex, buf, i, ip);
    }
    return lex;
}

//=====================================================================================
//======================================parser.c=======================================
//=====================================================================================


int Parse (struct lex_array_t *lex, unsigned char *bin, size_t *lex_ip, size_t *bin_ip)
{
    if (*lex_ip >= lex->size - 1)
        return 0;
    if (lex->lexarr[*lex_ip].kind != CMD)
    {
        fprintf (stderr, "ERROR\n");
        exit(0);
    }
    switch (lex->lexarr[*lex_ip].lex.CMD)
    {
    case MOVI:
    {
        if (lex->lexarr[*lex_ip + 1].kind != VAL)
        {
            fprintf (stderr, "ERROR\n");
            exit(0);
        }
        bin[*bin_ip] = (unsigned char)(lex->lexarr[*lex_ip + 1].lex.val & 0x7F);
        *bin_ip += 1;
        *lex_ip += 2;
        break;
    }
    case ADD:
    {
        unsigned char r1;
        unsigned char r2;
        if (lex->lexarr[*lex_ip + 1].kind != REG || lex->lexarr[*lex_ip + 2].kind != REG)
        {
            fprintf (stderr, "ERROR\n");
            exit(0);
        }
        r1 = (unsigned char)lex->lexarr[*lex_ip + 1].lex.REG;
        r2 = (unsigned char)lex->lexarr[*lex_ip + 2].lex.REG;

        bin[*bin_ip] = (unsigned char)(0x80 | r1 << 2 | r2);
        *bin_ip += 1;
        *lex_ip += 3;
        break;
    }
    case SUB:
    {
        unsigned char r1;
        unsigned char r2;
        if (lex->lexarr[*lex_ip + 1].kind != REG || lex->lexarr[*lex_ip + 2].kind != REG)
        {
            fprintf (stderr, "ERROR\n");
            exit(0);
        }
        r1 = (unsigned char)lex->lexarr[*lex_ip + 1].lex.REG;
        r2 = (unsigned char)lex->lexarr[*lex_ip + 2].lex.REG;

        bin[*bin_ip] = (unsigned char)(0x90 | r1 << 2 | r2);
        *bin_ip += 1;
        *lex_ip += 3;
        break;
    }
    case MUL:
    {
        unsigned char r1;
        unsigned char r2;
        if (lex->lexarr[*lex_ip + 1].kind != REG || lex->lexarr[*lex_ip + 2].kind != REG)
        {
            fprintf (stderr, "ERROR\n");
            exit(0);
        }
        r1 = (unsigned char)lex->lexarr[*lex_ip + 1].lex.REG;
        r2 = (unsigned char)lex->lexarr[*lex_ip + 2].lex.REG;

        bin[*bin_ip] = (unsigned char)(0xA0 | r1 << 2 | r2);
        *bin_ip += 1;
        *lex_ip += 3;
        break;
    }
    case DIV:
    {
        unsigned char r1;
        unsigned char r2;
        if (lex->lexarr[*lex_ip + 1].kind != REG || lex->lexarr[*lex_ip + 2].kind != REG)
        {
            fprintf (stderr, "ERROR\n");
            exit(0);
        }
        r1 = (unsigned char)lex->lexarr[*lex_ip + 1].lex.REG;
        r2 = (unsigned char)lex->lexarr[*lex_ip + 2].lex.REG;

        bin[*bin_ip] = (unsigned char)(0xB0 | r1 << 2 | r2);
        *bin_ip += 1;
        *lex_ip += 3;
        break;
    }
    case IN:
    {
        unsigned char r;
        if (lex->lexarr[*lex_ip + 1].kind != REG)
        {
            fprintf (stderr, "ERROR\n");
            exit(0);
        }
        r = (unsigned char)lex->lexarr[*lex_ip + 1].lex.REG;

        bin[*bin_ip] = (unsigned char)(0xC0 | r);
        *bin_ip += 1;
        *lex_ip += 2;
        break;
    }
    case OUT:
    {
        unsigned char r;
        if (lex->lexarr[*lex_ip + 1].kind != REG)
        {
            fprintf (stderr, "ERROR\n");
            exit(0);
        }
        r = (unsigned char)lex->lexarr[*lex_ip + 1].lex.REG;

        bin[*bin_ip] = (unsigned char)(0xC4 | r);
        *bin_ip += 1;
        *lex_ip += 2;
        break;
    }
    }
    return 0;
}

void Translate (struct lex_array_t *lex)
{
    size_t lex_ip = 0;
    size_t bin_ip = 0;
    unsigned char *bin = calloc (lex->size, sizeof (unsigned char));

    for (; lex_ip < lex->size - 1; )
    {
        Parse (lex, bin, &lex_ip, &bin_ip);
    }
    for (size_t i = 0; i < bin_ip; i++)
    {
        printf ("0x%x ", bin[i]);
    }
    free (bin);
}

//=====================================================================================
//======================================AS.c===========================================
//=====================================================================================
int main ()
{
    char *buf = NULL;
    struct lex_array_t *lex = NULL;
    Input (&buf);
    lex = lex_string (buf);
    free (buf);
    Translate (lex);
    

    free(lex->lexarr);
    free(lex);

    return 0;
}
