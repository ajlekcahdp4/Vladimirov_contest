#include "dump.h"
#include "../hashtable/hashtable.h"



struct node {
    char* word;
    struct node *next;
};

struct Hashtable {
    struct node **lists_ar;
    struct node  *list_head;
    struct node  *list_tail;
    unsigned long long size;
    unsigned long long inserts;
    unsigned long long (*hash_func)(const char*);
};


void DtStart (FILE* dotfile)
{
    fprintf (dotfile, "digraph G {\n");
    fprintf (dotfile, "rankdir = LR\n");
}

void DtSetTitle(FILE* dotfile, struct Hashtable* HashT)
{
    fprintf(dotfile ,"TITLE [shape=record, color=\"red\", label = \"DUMP of the hashTable\"];\n\n");
    fprintf (dotfile, "HEAD [shape=record, style=rounded, label =\"HEAD | %p |NEXT\\n %p\"];\n", HashT->list_head, HashT->list_head->next);
    fprintf (dotfile, "size [shape=record, style=rounded, label =\"size | %llu\"];\n", HashT->size);
    fprintf (dotfile, "TAIL [shape=record, style=rounded, label =\"TAIL | %p\"];\n", HashT->list_tail);
    fprintf (dotfile, "inserts [shape=record, style=rounded, label = \"inserts | %llu\"];\n", HashT->inserts);
}

void DtSetNode (FILE* dotfile, struct node *node)
{
    fprintf (dotfile, "Node%p [shape=record, style=filled, fillcolor = \"palegreen\", label=\"adr\\n%p|word\\n%s|next\\n%p\"];\n", node, node, node->word, node->next);
}

void DtSetDependence (FILE* dotfile, struct Hashtable *HashT)
{
    struct node *cur = HashT->list_head->next;
    while (cur != 0)
    {
        fprintf (dotfile, "Node%p -> ", cur);
        cur = cur->next;
    }
    fprintf (dotfile, "Node0 [color=\"invis\"];\n\n");


    cur = HashT->list_head->next;
    fprintf (dotfile, "HEAD ->");
    while (cur != 0)
    {
        fprintf (dotfile, "Node%p -> ", cur);
        cur = cur->next;
    }
    fprintf (dotfile, "0 [color=\"red\"];\n\n");

    fprintf (dotfile, "TAIL->Node%p[color=\"red\"];\n", HashT->list_tail);
    fprintf(dotfile, "size->inserts[color=\"invis\"];\n");
}

void DtEnd (FILE* dotfile)
{
    fprintf (dotfile, "}\n");
} 