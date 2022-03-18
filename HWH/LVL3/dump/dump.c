#include "dump.h"
#include "../hashtable/hashtable.h"



struct node {
    char* word;
    struct node *next;
};

struct Hashtable_elem {
    struct node *next;
    size_t capacity;
};

struct Hashtable {
    struct Hashtable_elem **lists_ar;
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
    fprintf (dotfile, "size [shape=record, style=rounded, label =\"size | %llu\"];\n", HashT->size);
    fprintf (dotfile, "inserts [shape=record, style=rounded, label = \"inserts | %llu\"];\n", HashT->inserts);
}

void DtSetBuf (FILE *dotfile, struct Hashtable* HashT)
{
    fprintf (dotfile, "\n");
    
    fprintf (dotfile, "subgraph clusterbuffer {\n");
    fprintf (dotfile, "node [style=filled, fillcolor=white];\n");
    fprintf (dotfile, "style=filled;\ncolor=lightgrey");

    for (size_t i = 0; i < HashT->size; i++)
    {
        if (HashT->lists_ar[i])
        {
            fprintf (dotfile, "    Buf%lu [shape=record, label=\"[%lu]\"];\n", i, i);
        }
    }
    fprintf (dotfile, "label=\"buffer\";\n}\n\n");

}

void DtSetNodes (FILE* dotfile, struct node *node, struct Hashtable *HashT)
{
    fprintf (dotfile, "Node%p [shape=record, style=filled, fillcolor = \"palegreen\", label=\"adr\\n%p|word\\n%s|Hash = %llu|next\\n%p\"];\n", node, node, node->word,HashT->hash_func (node->word)%HashT->size, node->next);
}

void DtSetDependence (FILE* dotfile, struct Hashtable *HashT)
{
    struct node        *cur       = 0;


    fprintf (dotfile, "\n");
    for (size_t i = 0; i < HashT->size; i++)
    {
        if (HashT->lists_ar[i])
        {
            fprintf (dotfile, "Buf%lu -> Node%p[color=\"red\", constraint=true];\n", i, HashT->lists_ar[i]->next);
        }
    }

    //lists dependencies=======================================================
    for (size_t i = 0; i < HashT->size; i++)
    {
        if (HashT->lists_ar[i])
        {
            cur = HashT->lists_ar[i]->next;
            
            size_t j = 0;
            while (cur->next && j < HashT->lists_ar[i]->capacity - 1)
            {
                fprintf (dotfile, "Node%p->", cur);
                cur = cur->next;
                j++;
            }
            if (cur != HashT->lists_ar[i]->next)
            {
                fprintf (dotfile, "Node%p", cur);
                fprintf(dotfile, "[color=\"red\"];\n");
            }
        }
    }
    fprintf (dotfile, "\n");
}

void DtEnd (FILE* dotfile)
{
    fprintf (dotfile, "}\n");
} 