#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "mk.h"


int is_movi (unsigned data)
{
    return !((data >> 7) & 0x1);
}
int is_in_out (unsigned data)
{
    if (is_movi (data))
        return 0;
    return (data >> 6) & 0x1;
}

unsigned get_imm (unsigned data)
{
    return data & ((1 << 8) - 1);
}

enum reg_t decode_arg0 (unsigned data)
{
    return data & 0x3;
}

enum reg_t decode_arg1 (unsigned data)
{
    return decode_arg0 (data >> 2);
}




enum opcode_t get_inout (unsigned data)
{
    enum opcode_t Opc =  (data >> 2) & 0xF;
    switch (Opc)
    {
    case 0:
        return IN;
    case 1: 
        return OUT;
    }
    fprintf (stderr, "ERROR: Unknown INOUT %X\n", Opc);
    exit (0);
}

const char *get_reg_s (enum reg_t reg)
{
    switch (reg)
    {
    case A:
        return "A";
    case B:
        return "B";
    case C:
        return "C";
    case D:
        return "D";
    }
    fprintf (stderr, "ERROR: Unknown reg: %X\n", reg);
    exit (0);
}

const char *get_arith_s (enum opcode_t Opc)
{
    switch (Opc)
    {
    case ADD:
        return "ADD";
    case SUB:
        return "SUB";
    case MUL:
        return "MUL";
    case DIV:
        return "DIV";
    case IN:
        return "IN";
    case OUT:
        return "OUT";
    }
    fprintf (stderr, "ERROR: Unknown arith %X\n", Opc);
    exit (0);
}

int decode_in_out (unsigned data, char *Mnemonic)
{
    enum opcode_t Opc = get_inout (data);
    enum reg_t arg0 = decode_arg0 (data);

    sprintf (Mnemonic, "%s %s", get_arith_s (Opc), get_reg_s (arg0));
    return 0;
}


enum opcode_t arith_opcode (unsigned data)
{
    return data >> 4;
}



int decode_arith (unsigned data, char *Mnemonic)
{
    enum opcode_t Aop = arith_opcode (data);
    enum reg_t arg0 = decode_arg0 (data);
    enum reg_t arg1 = decode_arg1 (data);
    sprintf (Mnemonic, "%s %s, %s", get_arith_s(Aop), get_reg_s(arg1), get_reg_s (arg0));
    return 0;
}



int decode (unsigned data, char *Mnemonic)
{
    if (is_movi (data))
    {
        sprintf (Mnemonic, "%s %d", "MOVI", get_imm (data));
        return 0;
    }
    if (is_in_out (data))
    {
        return decode_in_out (data, Mnemonic);
    }
    return decode_arith (data, Mnemonic);
}

#define MAXLEN 10000

int main ()
{
    int res = 0;
    unsigned data = 0;
    char Mnemonic[64] = {0};
    char OUT[MAXLEN] = {0};
    char *pr = OUT;

    for ( ; ; )
    {
        res = scanf (" %x", &data);
        if (res != 1)
            break;
        decode (data, Mnemonic);
        printf ("%s\n", Mnemonic);
        memcpy (pr, Mnemonic, strlen (Mnemonic) * sizeof (char));
        pr += strlen (Mnemonic) * sizeof (char);
    }

    return 0;
}