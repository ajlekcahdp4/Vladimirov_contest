#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "parser.h"

int Parse (struct lex_array_t *lex, unsigned char *bin, size_t *lex_ip, size_t *bin_ip)
{
    if (*lex_ip >= lex->size - 1)
        return 0;
    if (lex->lexarr[*lex_ip].kind != CMD)
    {
        fprintf (stderr, "ERROR: not a command\n");
        exit(0);
    }
    switch (lex->lexarr[*lex_ip].lex.CMD)
    {
    case MOVI:
    {
        if (lex->lexarr[*lex_ip + 1].kind != VAL)
        {
            printf ("%lu\n", *lex_ip);
            fprintf (stderr, "ERROR: no value after MOVI command\n");
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
            fprintf (stderr, "ERROR: no registers after command\n");
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
            fprintf (stderr, "ERROR: no registers after command\n");
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
            fprintf (stderr, "ERROR: no registers after command\n");
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
            fprintf (stderr, "ERROR: no registers after command\n");
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
            fprintf (stderr, "ERROR: no register after command\n");
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
            fprintf (stderr, "ERROR: no register after command\n");
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

    for (; lex_ip < lex->size - 1 ; )
    {
        Parse (lex, bin, &lex_ip, &bin_ip);
    }
    for (size_t i = 0; i < bin_ip; i++)
    {
        printf ("0x%x ", bin[i]);
    }
    free (bin);
}