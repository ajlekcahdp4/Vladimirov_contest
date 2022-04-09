#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable.h"
#include "../dump/dump.h"

struct node_t {
    struct node_t *next;
    unsigned ip1;
    unsigned ip2;
};

struct Hashtable_elem {
    struct node_t *next;
    unsigned capacity;
};

struct Hashtable {
    struct Hashtable_elem **lists_ar;
    struct node_t  *list_head;
    struct node_t  *list_tail;
    unsigned long long size;
    unsigned long long inserts;
    unsigned long long (*HashFunc)(struct buffer*, struct node_t*);
    int (*Cmp) (struct buffer *buf, const struct node_t *node1, const struct node_t *node2);
};

struct node_t *ListInit (void);
size_t ListCount (struct buffer *buf, struct node_t *top, struct node_t *aim_node);
struct node_t *ListInsert (struct node_t *last, struct node_t *new_node);
void DeleteNodeAft (struct Hashtable *HashT, struct node_t* last);
void DeleteList (struct node_t* top);
void ClearStr (char* str);
void ListDump (struct buffer *buf, struct node_t *top);
unsigned long long djb2 (const char* str);
struct Hashtable* HashTableResize (struct Hashtable* HashT, struct buffer *buf);
struct Hashtable* HashTableInsert (struct Hashtable* HashT, struct buffer *buf, unsigned ip1, unsigned ip2);

//==================================================================================
//=================================STRUCT_FUNCTIONS=================================
//==================================================================================
#define MAX_STR_LEN 32

int NodesCmp(struct buffer *buf, const struct node_t * const node1, const struct node_t *node2)
{
    assert (node1);
    assert (node2);
    assert (buf);

    int res = 0;
    unsigned ip11 = node1->ip1;
    unsigned ip12 = node1->ip2;
    unsigned ip21 = node2->ip1;
    unsigned ip22 = node2->ip2;
    //--------------------------------------------------------------------------
    char *temp_str_1 = calloc (MAX_STR_LEN, sizeof(char));
    char *temp_str_2 = calloc (MAX_STR_LEN, sizeof(char));
    assert (temp_str_1);
    assert (temp_str_2);

    strcat (temp_str_1, buf->str_array[ip11]);
    strcat (temp_str_1, buf->str_array[ip12]);

    strcat (temp_str_2, buf->str_array[ip21]);
    strcat (temp_str_2, buf->str_array[ip22]);

    res = strcmp (temp_str_1, temp_str_2);
    free (temp_str_1);
    free (temp_str_2);
    //--------------------------------------------------------------------------

    //printf ("1'st print node1 = %p, node1->ip1 = %u, node1->ip2 = %u\n", node1, node1->ip1, node1->ip2);
    //printf ("2'nd print node1 = %p, node1->ip1 = %u, node1->ip2 = %u\n", node1, node1->ip1, node1->ip2);
    return res;
}
//==================================================================================

unsigned long long HashNode (struct buffer *buf, struct node_t *node)
{
    unsigned long long hash = 0;
    char *temp_str = calloc (MAX_STR_LEN, sizeof(char));
    strcat (temp_str, buf->str_array[node->ip1]);
    strcat (temp_str, buf->str_array[node->ip2]);

    hash = djb2 (temp_str);

    free (temp_str);
    return hash;
}

#undef MAX_STR_LEN
//==================================================================================

unsigned long long djb2 (const char* str)
{
    unsigned long long hash = 0;
    unsigned long long c = 0;
    while ((c = (unsigned long long)(*str++)) != 0)
        hash = (hash << 5) + (hash << 16) - hash  + c;
    return hash;
}


//==================================================================================
//===================================LIST_FUNCTIONS=================================
//==================================================================================
struct node_t *ListInit (void)
{
    struct node_t *top = calloc (1, sizeof (struct node_t));
    return top;
}
//==================================================================================
size_t ListCount (struct buffer *buf, struct node_t *top, struct node_t *aim_node)
{
    assert (top);
    assert (aim_node);

    size_t cnt = 0;
    struct node_t *cur = top;
    while (cur)
    {
        if (NodesCmp (buf, cur, aim_node) == 0)
            cnt += 1;
        cur = cur->next;
    }
    return cnt;
}

//==================================================================================
void ListDump (struct buffer *buf, struct node_t *top)
{
    struct node_t *cur = top->next;

    while (cur)
    {
        printf ("\"%u|%u\"[%llu]->", cur->ip1, cur->ip2, HashNode (buf, cur));
        cur = cur->next;
    }
    printf("\n\n");
}

//==================================================================================
struct node_t *ListInsert (struct node_t *last, struct node_t *new_node)
{
    struct node_t *cur = last;
    if (cur->next == 0)
    {
        cur->next = new_node;
    }
    else
    {
        new_node->next = cur->next;
        cur->next = new_node;
    }
    
    return new_node;
}
//==================================================================================

void DeleteNodeAft (struct Hashtable *HashT, struct node_t* last)
{
    assert (last->next);

    if (HashT->list_tail == last->next)
        HashT->list_tail = last;

    struct node_t* cur = last->next;
    last->next       = cur->next;

    free (cur); 
}

//==================================================================================

void DeleteList (struct node_t* top)
{
    struct node_t* cur_node = top;
    struct node_t* next_node = top;
    while (cur_node->next != 0)
    {
        next_node = cur_node->next;
        free(cur_node);
        cur_node = next_node;
        assert (cur_node);
    }
    free(cur_node);
}

//==================================================================================
//================================HASHTABLE_FUNCTIONS===============================
//==================================================================================

struct Hashtable* HashTableInsert (struct Hashtable* HashT, struct buffer *buf, unsigned ip1, unsigned ip2)
{
    assert (HashT);
    assert (buf);
    if ((float)HashT->inserts / (float)HashT->size >= 0.7)
    {
        HashT = HashTableResize (HashT, buf);
    }

    struct node_t *new_node = calloc (1, sizeof(struct node_t));
    new_node->ip1 = ip1;
    new_node->ip2 = ip2;


    unsigned long long hash = HashT->HashFunc (buf, new_node) % HashT->size;

    if (HashT->lists_ar[hash] == 0)
    {
        HashT->lists_ar[hash] = calloc (1, sizeof(struct Hashtable_elem));
        assert (HashT->lists_ar[hash]);
        
        HashT->lists_ar[hash]->next = ListInsert (HashT->list_tail, new_node);
        HashT->list_tail            = HashT->list_tail->next;
    }
    else
    {
        struct node_t* cur = HashT->lists_ar[hash]->next;
        
        size_t i = 0;
        while (cur->next && i < HashT->lists_ar[hash]->capacity - 1)
        {
            cur = cur->next;
            i++;
        }
        assert (cur);
        if (cur == HashT->list_tail)
        {
            ListInsert (HashT->list_tail, new_node);
            HashT->list_tail = HashT->list_tail->next;

        }
        else
        {
            ListInsert (cur, new_node);
        }
    }

    HashT->lists_ar[hash]->capacity += 1;
    HashT->inserts                  += 1;
    return HashT;
}
//==================================================================================

struct Hashtable* HashTableInit (size_t size, unsigned long long (*HashFunc)(struct buffer*, struct node_t*), \
    int (*Cmp)(struct buffer *buf, const struct node_t *node1, const struct node_t *node2))
{
    assert (size);
    struct Hashtable* HashT = calloc (1, sizeof(struct Hashtable));
    HashT->list_head        = calloc (1, sizeof (struct node_t));
    HashT->lists_ar         = calloc (size, sizeof(struct Hashtable_elem*));
    assert (HashT);
    assert (HashT->lists_ar);
    assert (HashT->list_head);
    HashT->size      = size;
    HashT->HashFunc = HashFunc;
    HashT->Cmp = Cmp;
    HashT->list_tail = HashT->list_head;

    return HashT;
}
//==================================================================================



struct Hashtable* HashTableResize (struct Hashtable* HashT, struct buffer *buf)
{
    for (unsigned long long int i = 0; i < HashT->size; i++)
        if(HashT->lists_ar[i] != 0)
            free (HashT->lists_ar[i]);
    free (HashT->lists_ar);
    
    
    HashT-> size *= 2;
    HashT->lists_ar = calloc (HashT->size, sizeof (struct node_t*));

    struct node_t *last = HashT->list_tail;
    unsigned long long old_inserts = HashT->inserts;
    struct node_t* cur = HashT->list_head;
    //+++++++++++++++++++++++++++++++++++++++++
    while (cur->next != last)
    {
        HashT->inserts = 0;
        HashTableInsert (HashT, buf, cur->next->ip1, cur->next->ip2);
        DeleteNodeAft (HashT, cur);
    }
    HashT->inserts = 0;
    HashTableInsert (HashT, buf, cur->next->ip1, cur->next->ip2);
    DeleteNodeAft (HashT, cur);
    //+++++++++++++++++++++++++++++++++++++++++
    HashT->inserts = old_inserts;
    
    return HashT;
}

//==================================================================================

size_t NumberOfFour (struct buffer *buf, struct Hashtable *HashT)
{
    size_t numb_of_four     = 0;
    size_t cnt              = 0;
    size_t bucket_capacity  = 0;
    size_t hasht_size       = 0;
    struct node_t *top      = NULL;
    struct node_t *last     = NULL;
    struct node_t *cmp_node = NULL;
    struct node_t *cur      = NULL;
    struct node_t *runner   = NULL;
    struct Hashtable_elem *cur_bucket = NULL;
    
    hasht_size = HashT->size;   
    for (size_t i = 0; i < hasht_size; i++)
    {   
        cur_bucket = HashT->lists_ar[i];
        if (cur_bucket)
        {
            top = ListInit ();
            assert (top);
            last = top;

            cur = cur_bucket->next;
            
            cmp_node = calloc (1, sizeof (struct node_t));
            cmp_node->ip1 = cur->ip1;
            cmp_node->ip2 = cur->ip2;

            bucket_capacity = cur_bucket->capacity;
            for (size_t j = 0; j < bucket_capacity; j++)
            {
                if (ListCount (buf, top, cmp_node) == 0)
                {
                    last = ListInsert (last, cmp_node);
                    cnt  = 0;
                    runner = cur;
                    for (size_t k = 0; runner && k < bucket_capacity; k++)
                    {
                        if (HashT->Cmp (buf, runner, cmp_node) == 0)
                            cnt += 1;
                        runner = runner->next;
                    }
                    if (cnt > 1)
                        numb_of_four += (cnt * (cnt - 1)) / 2;
                }
                cur = cur->next;
                if (cur)
                {
                    cmp_node->next = calloc (1, sizeof (struct node_t));
                    cmp_node->next->ip1 = cur->ip1;
                    cmp_node->next->ip2 = cur->ip2;
                    cmp_node = cmp_node->next;
                }

            }
            DeleteList (top);
        }
    }

    return numb_of_four;
}


//==================================================================================
#ifdef DUMP_INCLUDED

void HashTDump (struct Hashtable *HashT, struct buffer *buf, char *name)
{
    FILE *dotfile  = fopen ("dump.dot", "w");

    DtStart (dotfile);
    DtSetTitle (dotfile, HashT);
    struct node_t *cur = HashT->list_head->next;
    DtSetBuf (dotfile, HashT);
    while (cur != 0)
    {
        DtSetNodes (dotfile, buf, cur, HashT);
        cur = cur->next;
    }
    fprintf (dotfile, "\n\n\n");

    DtSetDependence (dotfile, HashT);

    DtEnd (dotfile);
    fclose (dotfile);
    
    char *command = calloc (100, sizeof(char));
    memcpy (command, "dot dump.dot -T png -o ", 23 * sizeof(char));
    strcat (command, name);
    system (command);
    //system ("rm dump.dot");
    free (command);
}

#endif
//==================================================================================
struct Hashtable *FillHashtable (struct Hashtable *HashT, struct buffer *buf)
{
    for (unsigned first = 0; first < buf->size; first++)
    {
        for (unsigned second = 0; second < buf->size; second++)
        {
            if (first != second)
                HashTableInsert (HashT, buf, first, second);
        }
    }
    
    return HashT;
}




//==================================================================================
void ClearStr (char* str)
{
    size_t i = 0;
    while (str[i] != '\0')
    {
        str[i] = '\0';
        i++;
    }
}
//==================================================================================
void DeleteHastable (struct Hashtable* HashT)
{
    DeleteList (HashT->list_head);
    for (unsigned long long int i = 0; i < HashT->size; i++)
        if(HashT->lists_ar[i] != 0)
            free (HashT->lists_ar[i]);
    free (HashT->lists_ar);
    free (HashT);
}
