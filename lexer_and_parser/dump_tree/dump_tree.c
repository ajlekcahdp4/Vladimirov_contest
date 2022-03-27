#include <stdio.h>
#include <stdlib.h>
#include "dump_tree.h"

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


struct node_t {
  struct node_t *left, *right;
  struct lexem_t data;
};





void DtStart (FILE* dotfile)
{
    fprintf (dotfile, "digraph G {\n");
    fprintf (dotfile, "rankdir = LR\n");
}

void DtSetNode (FILE* dotfile, struct node_t *node)
{
    fprintf (dotfile, "Node%p [style=filled, fillcolor = \"palegreen\" ,label=\"", node);
    switch (node->data.kind)
    {
        case OP:
            switch (node->data.lex.op)
            {
                case ADD:
                    fprintf (dotfile, "+");
                    break;
                case SUB:
                    fprintf (dotfile, "-");
                    break;
                case MUL:
                    fprintf (dotfile, "*");
                    break;
                case DIV:
                    fprintf (dotfile, "/");
                    break;
                default:
                    printf ("ERROR\n");
                    break;
            }
            break;
        case NUM:
            fprintf (dotfile, "%d", node->data.lex.num);
            break;
        case BRACE:
        default:
            printf ("ERROR\n");
            break;
    }
    fprintf (dotfile, "\"];\n");
}

void DtSetNodes (FILE *dotfile, struct node_t *top)
{
    DtSetNode (dotfile, top);
    if (top->left)
        DtSetNodes (dotfile, top->left);
    if (top->right)
        DtSetNodes (dotfile, top->right);
}

void DtSetDependencies (FILE *dotfile, struct node_t *top)
{
    if (top->left)
    {
        fprintf (dotfile, "Node%p->Node%p\n", top, top->left);
        DtSetDependencies (dotfile, top->left);
    }
    if (top->right)
    {
        fprintf (dotfile, "Node%p->Node%p\n", top, top->right);
        DtSetDependencies (dotfile, top->right);
    }
    fprintf (dotfile, "\n");
}

void DtEnd (FILE* dotfile)
{
    fprintf (dotfile, "}\n");
} 

