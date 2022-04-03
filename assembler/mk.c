#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>



enum reg_t {  A = 0, B, C, D };

enum opcode_t { MOVI = 0, ADD = 8, SUB = 9, MUL = 10, DIV = 11, IN, OUT };

enum lexem_kind { CMD, REG, VAL };

struct lexem_t
{
    union
    {
        enum opcode_t CMD;
        enum reg_t REG;
        int val;
    } lex;
    enum lexem_kind kind;
};

struct lex_array_t
{
    struct lexem_t *lexarr;
    size_t capacity;
    size_t size;
};
//==================================================================================
//=====================================lexer========================================
//==================================================================================

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
    unsigned char Opc =  (data >> 2) & 0xF;
    switch (Opc)
    {
    case 0:
        return IN;
    case 1:
        return OUT;
    default:
        fprintf (stderr, "ERROR\n");
        exit(0);
    }
    fprintf (stderr, "ERROR: Unknown INOUT %X\n", Opc);
    exit (0);
}

int get_reg_s (struct lex_array_t *lex, enum reg_t reg, size_t *ip)
{
    switch (reg)
    {
    case A:
        lex->lexarr[*ip].kind = REG;
        lex->lexarr[*ip].lex.REG = A;
        return 0;
    case B:
        lex->lexarr[*ip].kind = REG;
        lex->lexarr[*ip].lex.REG = B;
        return 0;
    case C:
        lex->lexarr[*ip].kind = REG;
        lex->lexarr[*ip].lex.REG = C;
        return 0;
    case D:
        lex->lexarr[*ip].kind = REG;
        lex->lexarr[*ip].lex.REG = D;
        return 0;
    }
    fprintf (stderr, "ERROR: Unknown reg: %X\n", reg);
    exit (0);
}

int *get_arith_s (struct lex_array_t *lex, enum opcode_t Opc, size_t *ip)
{
    lex->lexarr[*ip].kind = CMD;
    switch (Opc)
    {
    case ADD:
        lex->lexarr[*ip].lex.CMD = ADD;
        return 0;
    case SUB:
        lex->lexarr[*ip].lex.CMD = SUB;
        return 0;
    case MUL:
        lex->lexarr[*ip].lex.CMD = MUL;
        return 0;
    case DIV:
        lex->lexarr[*ip].lex.CMD = DIV;
        return 0;
    case IN:
        lex->lexarr[*ip].lex.CMD = IN;
        return 0;
    case OUT:
        lex->lexarr[*ip].lex.CMD = OUT;
        return 0;
    default:
        fprintf (stderr, "ERROR\n");
        exit(0);
    }
    fprintf (stderr, "ERROR: Unknown arith %X\n", Opc);
    exit (0);
}



enum opcode_t arith_opcode (unsigned data)
{
    return data >> 4;
}



int decode_arith (struct lex_array_t *lex, unsigned data, size_t *ip)
{
    enum opcode_t Aop = arith_opcode (data);
    enum reg_t arg0 = decode_arg0 (data);
    enum reg_t arg1 = decode_arg1 (data);

    get_arith_s (lex, Aop, ip);
    *ip += 1;
    get_reg_s (lex, arg1, ip);
    *ip += 1;
    get_reg_s (lex, arg0, ip);
    *ip += 1;
    return 0;
}



int decode (unsigned data, struct lex_array_t *lex, size_t *ip)
{
    if (is_movi (data))
    {
        lex->lexarr[*ip].kind = CMD;
        lex->lexarr[*ip].lex.CMD = MOVI;
        lex->lexarr[*ip + 1].kind = VAL;
        lex->lexarr[*ip + 1].lex.val = get_imm (data);
        *ip += 2;
        lex->size += 2;
        return 0;
    }
    else if (is_in_out (data))
    {
        enum opcode_t Opc = get_inout (data);
        enum reg_t arg0 = decode_arg0 (data);
        lex->lexarr[*ip].kind = CMD;
        get_arith_s (lex, Opc, ip);
        *ip += 1;
        get_reg_s (lex, arg0, ip);
        *ip += 1;
        lex->size += 2;
        return 0;
    }
    else
    {
        decode_arith (lex, data, ip);
        lex->size += 3;
        return 0;
    }
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
                    fprintf (stderr, "ERROR: unknown command in print\n");
                    exit(0);
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
                    fprintf (stderr, "ERROR: unknown register in print\n");
                    exit(0);
                    break;
            }
            break;
        case VAL:
            printf ("%d ", lex->lexarr[i].lex.val);
            break;
        default:
            printf ("ERROR: unknown lexem   type in print\n");
            exit(0);
            break;
        }
    }
    printf ("\n\n");

}

#define MAXLEN 1000
struct lex_array_t *Lexer (char *filename)
{
    int res = 0;
    unsigned data = 0;
    size_t buf_ip = 0;
    struct stat bufF;
    int len = 0;
    struct lex_array_t *lex = NULL;
    unsigned char *buf = NULL;
    FILE *file = fopen (filename, "r");
    assert (file);

    
    stat(filename, &bufF);
    len = bufF.st_size;
    buf = calloc (len + 1, sizeof (unsigned char));
    assert (buf);
    fread (buf, sizeof (unsigned char), len, file);
    fclose(file);

    lex = calloc (1, sizeof (struct lex_array_t));
    assert (lex);
    lex->lexarr = calloc (MAXLEN, sizeof (struct lexem_t));
    assert (lex->lexarr);



    
    for ( size_t ip = 0; ; )
    {
        res = sscanf (buf + buf_ip, " %x", &data);
        buf_ip += 5;
        if (res != 1)
            break;
        decode (data, lex, &ip);
    }
    free (buf);
    return lex;
}
#undef MAXLEN
//==================================================================================
//=====================================processor====================================
//==================================================================================


void RunCmd (struct lex_array_t *lex, size_t *ip, unsigned char *regs)
{
    switch (lex->lexarr[*ip].lex.CMD)
    {
    case MOVI:
        {
            regs[D] = (unsigned char)lex->lexarr[*ip + 1].lex.val;
            *ip += 2;
            break;
        }
    case ADD:
        {
            regs[lex->lexarr[*ip + 1].lex.REG] = (unsigned char)(regs[lex->lexarr[*ip + 1].lex.REG] + regs[lex->lexarr[*ip + 2].lex.REG]);
            *ip += 3;
            break;
        }
    case SUB:
        {
            regs[lex->lexarr[*ip + 1].lex.REG] = (unsigned char)(regs[lex->lexarr[*ip + 1].lex.REG] - regs[lex->lexarr[*ip + 2].lex.REG]);
            *ip += 3;
            break;
        }
    case MUL:
        {
            regs[lex->lexarr[*ip + 1].lex.REG] = (unsigned char)(regs[lex->lexarr[*ip + 1].lex.REG] * regs[lex->lexarr[*ip + 2].lex.REG]);
            *ip += 3;
            break;
        }
    case DIV:
        {
            regs[lex->lexarr[*ip + 1].lex.REG] = (unsigned char)(regs[lex->lexarr[*ip + 1].lex.REG] / regs[lex->lexarr[*ip + 2].lex.REG]);
            *ip += 3;
            break;
        }
    case IN:
        {
            int val = 0;
            scanf ("%d", &val);
            regs [lex->lexarr[*ip + 1].lex.REG] = val;
            *ip += 2;
            break;
        }
    case OUT:
        {
            printf ("%d\n", regs[lex->lexarr[*ip + 1].lex.val]);
            *ip += 2;
            break;
        }
    default:
        fprintf (stderr, "ERROR: unknow cmd type %d\n", lex->lexarr[*ip].lex.CMD);
        exit(0);
    }
}




void Processor (struct lex_array_t *lex)
{
    unsigned char *regs = calloc (4, sizeof(unsigned char));
    for (size_t ip = 0; ip < lex->size; )
    {
        RunCmd (lex, &ip, regs);
    }
    free (lex->lexarr);
    free (lex);
}


//==================================================================================
//=====================================main=========================================
//==================================================================================




int main (int argc, char **argv)
{
    struct lex_array_t *lex = Lexer (argv[argc - 1]);

    Processor (lex);
    return 0;
}