#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "parser.h"

void Parse (struct lex_array_t *lex, unsigned char *bin, size_t *lex_ip, size_t *bin_ip)
{
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
        sprintf (bin + *bin_ip, "%x ", lex->lexarr[*lex_ip].lex.val & 0x7F);
        *bin_ip += 2;
        *lex_ip += 2;
        break;
    }
    case ADD:
    {
        enum reg_t r1;
        enum reg_t r2;
        if (lex->lexarr[*lex_ip + 1].kind != REG || lex->lexarr[*lex_ip + 2].kind != REG)
        {
            fprintf (stderr, "ERROR\n");
            exit(0);
        }
        r1 = (unsigned char)lex->lexarr[*lex_ip + 1].lex.REG;
        r2 = (unsigned char)lex->lexarr[*lex_ip + 2].lex.REG;

        sprintf (bin + *bin_ip, "%x ", 0x80 | r1 << 2 | r2);
        *bin_ip += 2;
        *lex_ip += 3;
        break;
    }
    case SUB:
    {
        enum reg_t r1;
        enum reg_t r2;
        if (lex->lexarr[*lex_ip + 1].kind != REG || lex->lexarr[*lex_ip + 2].kind != REG)
        {
            fprintf (stderr, "ERROR\n");
            exit(0);
        }
        r1 = (unsigned char)lex->lexarr[*lex_ip + 1].lex.REG;
        r2 = (unsigned char)lex->lexarr[*lex_ip + 2].lex.REG;

        sprintf (bin + *bin_ip, "%x ", 0x90 | r1 << 2 | r2);
        *bin_ip += 2;
        *lex_ip += 3;
        break;
    }
    case MUL:
    {
        enum reg_t r1;
        enum reg_t r2;
        if (lex->lexarr[*lex_ip + 1].kind != REG || lex->lexarr[*lex_ip + 2].kind != REG)
        {
            fprintf (stderr, "ERROR\n");
            exit(0);
        }
        r1 = (unsigned char)lex->lexarr[*lex_ip + 1].lex.REG;
        r2 = (unsigned char)lex->lexarr[*lex_ip + 2].lex.REG;

        sprintf (bin + *bin_ip, "%x ", 0xA0 | r1 << 2 | r2);
        *bin_ip += 2;
        *lex_ip += 3;
        break;
    }
    case DIV:
    {
        enum reg_t r1;
        enum reg_t r2;
        if (lex->lexarr[*lex_ip + 1].kind != REG || lex->lexarr[*lex_ip + 2].kind != REG)
        {
            fprintf (stderr, "ERROR\n");
            exit(0);
        }
        r1 = (unsigned char)lex->lexarr[*lex_ip + 1].lex.REG;
        r2 = (unsigned char)lex->lexarr[*lex_ip + 2].lex.REG;

        sprintf (bin + *bin_ip, "%x ", 0xB0 | r1 << 2 | r2);
        *bin_ip += 2;
        *lex_ip += 3;
        break;
    }
    case IN:
    {
        enum reg_t r;
        if (lex->lexarr[*lex_ip + 1].kind != REG)
        {
            fprintf (stderr, "ERROR\n");
            exit(0);
        }
        r = (unsigned char)lex->lexarr[*lex_ip + 1].lex.REG;

        sprintf (bin + *bin_ip, "%x ", 0xC0 | r);
        *bin_ip += 2;
        *lex_ip += 2;
        break;
    }
    case OUT:
    {
        enum reg_t r;
        if (lex->lexarr[*lex_ip + 1].kind != REG)
        {
            fprintf (stderr, "ERROR\n");
            exit(0);
        }
        r = (unsigned char)lex->lexarr[*lex_ip + 1].lex.REG;

        sprintf (bin + *bin_ip, "%x ", 0xC4 | r);
        *bin_ip += 2;
        *lex_ip += 2;
        break;
    }
    }
}

void Translate (struct lex_array_t *lex)
{
    size_t lex_ip = 0;
    size_t bin_ip = 0;
    unsigned char *bin = calloc (lex->size, sizeof (unsigned char));

    for (; lex_ip < lex->capacity; )
    {
        Parse (lex, bin, &lex_ip, &bin_ip);
    }
}