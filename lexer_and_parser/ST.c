#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "dump_tree/dump_tree.h"


#define MAXLEN 1024

//======================================================================================
//=========================================LX===========================================
//======================================================================================



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

#if 0
struct node_data_t {
  enum node_kind_t k;
  union {
    enum operation_t op;
    int d;
  } u;
};
#endif



int number_input (const char *buf, int *i);
void print_lex (struct lex_array_t *lex);
int skip_spaces (const char* buf, int ip);
int Input (char **buf);
void End (char *buf, struct lex_array_t *lex);
int lex_insert (struct lex_array_t *lex, const char *buf, int i, int ip);
struct lex_array_t *lex_string (const char *buf);
struct lex_array_t *lex_resize (struct lex_array_t *lex);




//void TreePrint (int size, struct node_t* top, char* str);
//=======================================================================================

enum node_kind_t { NODE_OP, NODE_VAL};


struct node_t {
  struct node_t *left, *right;
  struct lexem_t data;
};

struct node_t *build_syntax_tree(struct lex_array_t lexarr);

int calc_result(struct node_t *top);

void free_syntax_tree(struct node_t * top);

void TreePrint (int size, struct node_t* top, char* str)
{
    char* str_n = 0;
    struct node_t* cur = 0;

    assert(top);
    assert (str);
    
    cur = top;
    printf("%s\n", str);

    if (cur->left != 0)
    {
        str_n = calloc (size*2, sizeof(char));
        assert(str_n);
        memcpy (str_n, str, strlen (str));
        strcat (str_n, ".1");
        TreePrint (size, cur->left, str_n);
        free(str_n);
    }
    if (cur->right != 0)
    {
        str_n = calloc (size*2, sizeof(char));
        assert (str_n);
        memcpy (str_n, str, strlen (str));
        strcat (str_n, ".2");
        TreePrint (size, cur->right, str_n);
        free(str_n);
    }
}


int main ()
{

    char *buf = 0;
    struct lex_array_t *lex = 0;

    Input (&buf);
    
    lex = lex_string (buf);
    if (lex->size > 0)
    {
        print_lex (lex);
        struct node_t *top = build_syntax_tree (*lex);
        tree_dump (top);
        printf ("%d\n", calc_result (top));
        End (buf, lex);
    }
    return 0;
}


#if 0
int main ()
{
    char *buf = 0;
    struct lex_array_t *lex = 0;

    Input (&buf);
    
    lex = lex_string (buf);
    if (lex->size > 0)
    {
        print_lex (lex);
        End (buf, lex);
    }
    return 0;
}
#endif


//======================================================================================

int number_input (const char *buf, int *i)
{
    int val = 0;
    //printf ("number_input, i = %d\n", *i);
    while (isdigit (buf[*i]))
    {
        val = val * 10 + buf[*i] - '0';
        *i += 1;
    }
    //printf ("end input_number, %d\n", *i);
    return val;
}

int skip_spaces (const char* buf, int ip)
{
    while (buf[ip] == ' ' || buf[ip] == '\t' || buf[ip] == '\n' || buf[ip] == '\r')
        ip += 1;
    return ip;
}

int Input (char **buf)
{
    char c = 0;
    int len = 0;
    *buf = calloc (MAXLEN, sizeof (char));
    assert (*buf);

    c = (char)getchar ();
    *buf[len] = c;
    len += 1;
    while (c != '\0' && c != EOF && c != '\n')
    {
        c = (char)getchar();
        (*buf)[len] = c;
        len += 1;
    }

    //printf ("<%s>\n", *buf);
    

    return len;
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
                    break;
            }
            break;
        case NUM:
            printf ("NUMBER:%d ", lex->lexems[i].lex.num);
            break;
        default:
            printf ("ERROR\n");
            break;
        }   
    }
    printf ("\n");

}

int lex_insert (struct lex_array_t *lex, const char *buf, int i, int ip)
{
    while (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n')
        i += 1;
    if (buf[i] == '\0')
        return i;

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
        i -= 1;
    }
    else
    {
        return -1;
    }
    return i + 1;
} 


struct lex_array_t *lex_resize (struct lex_array_t *lex)
{
    lex->capacity = 2 * lex->capacity;
    lex->lexems = realloc (lex->lexems, (size_t)lex->capacity * sizeof (struct lexem_t));
    assert (lex->lexems);
    return lex;
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

    for (int i = 0; buf[i] != '\0' && buf[i] != EOF && buf[i] != '\n'; )
    {
        if (lex->size == lex->capacity)
            lex_resize (lex);
        i = lex_insert (lex, buf, i, ip);
        if (i == -1)
        {
            printf ("ERROR\n");
            size = -2;
            break;
        }
        size += 1;
        ip += 1;
    }
    lex->size = size;
    return lex;
}



//======================================================================================
//=========================================ST===========================================
//======================================================================================

// Grammar:




struct lexer_state {
    int cur;
    struct lex_array_t lexarr;
};



struct node_t *parse_term  (struct lexer_state *pstate);
struct node_t *parse_expr (struct lexer_state *pstate);
struct node_t *parse_factor (struct lexer_state *pstate);

struct lexem_t current (struct lexer_state *pstate)
{
    return pstate->lexarr.lexems[pstate->cur];
}


int is_plus_minus (struct lexer_state *pstate)
{
    struct lexem_t cur = current (pstate);
    if (cur.kind != OP)
        return 0;
    if (cur.lex.op != SUB && cur.lex.op != ADD)
        return 0;
    return 1;
}
int is_add  (struct lexer_state *pstate)
{
    struct lexem_t cur = current (pstate);
    if (cur.kind != OP)
        return 0;
    if (cur.lex.op != ADD)
        return 0;
    return 1;
}

int is_mul_div (struct lexer_state *pstate)
{
    struct lexem_t cur = current (pstate);
    if (cur.kind != OP)
        return 0;
    if (cur.lex.op != MUL && cur.lex.op != DIV)
        return 0;
    return 1;
}

int is_mul ( struct lexer_state *pstate)
{
    struct lexem_t cur = current (pstate);
    if (cur.kind != OP)
        return 0;
    if (cur.lex.op != MUL)
        return 0;
    return 1;
}

int is_l_brace ( struct lexer_state *pstate)
{
    struct lexem_t cur = current (pstate);
    if (cur.kind != BRACE)
        return 0;
    if (cur.lex.op != LBRAC)
        return 0;
    return 1;
}

int is_r_brace ( struct lexer_state *pstate)
{
    struct lexem_t cur = current (pstate);
    if (cur.kind != BRACE)
        return 0;
    if (cur.lex.op != RBRAC)
        return 0;
    return 1;
}

int is_number (struct lexer_state *pstate)
{
    struct lexem_t cur = current (pstate);
    if (cur.kind != NUM)
        return 0;
    return 1;
}


// expr ::= term {+, -} expr | term
struct node_t *parse_expr (struct lexer_state *pstate)
{
    struct node_t *lhs = parse_term (pstate);
    if (pstate->cur >= pstate->lexarr.size)
         return lhs;
    if (is_plus_minus (pstate))
    {
        enum operation_t op = SUB;
        if (is_add (pstate))
            op = ADD; 
        pstate->cur += 1;
        struct node_t *rhs = parse_expr (pstate);
        if (rhs == NULL)
            abort();
        struct node_t *expr = calloc (1, sizeof (struct node_t));
        expr->left = lhs;
        expr->right = rhs;
        expr->data.kind = NODE_OP;
        expr->data.lex.op = op;   
        return expr;
    }
    return lhs;
}
    
// term ::= factor {*, /} term | factor
struct node_t *parse_term  (struct lexer_state *pstate)
{
    struct node_t *lhs = parse_factor (pstate);
    if (pstate->cur >= pstate->lexarr.size)
        return lhs;
    if (is_mul_div (pstate))
    {
        enum operation_t op = DIV;
        if (is_mul (pstate))
            op = MUL; 
        pstate->cur += 1;
        struct node_t *rhs = parse_term (pstate);
        if (rhs == NULL)
            abort();
        struct node_t *term = calloc (1, sizeof (struct node_t));
        term->left = lhs;
        term->right = rhs;
        term->data.kind = NODE_OP;
        term->data.lex.op = op;    
        return term;
    }
    return lhs;
}

// factor ::= ( expr ) | number
struct node_t *parse_factor (struct lexer_state *pstate)
{
    #if 0
    struct node_t *lhs = parse_factor (pstate);
    #endif
    if (is_l_brace (pstate))
    {
        struct node_t *expr = parse_expr (pstate);
        pstate->cur += 1;
        if (!is_r_brace (pstate))
            abort ();
        return expr;
    }
    if (is_number (pstate))
    {
        struct node_t *num = calloc (1, sizeof (struct node_t));
        num->data.kind = NUM;
        num->data.lex.num = current(pstate).lex.num;
        pstate->cur += 1;
        return num;
    }
}

struct node_t *build_syntax_tree(struct lex_array_t lexarr)
{
    int cur = 0;
    struct lexer_state ls = {cur, lexarr};
    return parse_expr (&ls);
}

int calc_result(struct node_t *top) //inorder calculation
{
    struct node_t *cur = top;
    int val_l = 0;
    int val_r = 0;

    if (cur->left)
        val_l = calc_result (cur->left);
    if (cur->right)
        val_r = calc_result (cur->right);
    printf ("val_l = %d\n", val_l);
    printf ("val_r = %d\n", val_r);
    if (top->data.lex.op == ADD)
        return val_l + val_r;
    else if (top->data.lex.op == SUB)
        return val_l - val_r;
    
}


void tree_dump (struct node_t *top)
{
    FILE *dotfile = fopen ("dump.dot", "w");
    DtStart (dotfile);
    DtSetNodes (dotfile, top);
    DtSetDependencies (dotfile, top);
    DtEnd (dotfile);
    fclose (dotfile);
    system ("dot dump.dot -T png -o dump.png");
}

void free_syntax_tree(struct node_t * top) 
{
  // TODO: your code here
}