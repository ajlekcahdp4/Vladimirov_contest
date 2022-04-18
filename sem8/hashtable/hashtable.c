#include "hashtable.h"
#include <string.h>
#include <assert.h>

struct node
{
    struct node *next;
    struct node *prev;
    int val;
};

struct Hashtable
{
    struct node **lists_ar;
    #if 1
    struct node  *list_head;
    struct node  *list_tail;
    #endif
    unsigned long long size;
    unsigned long long inserts;
    unsigned long long (*hash_f)(int);
};


//==================================================================================

unsigned long long hash (int val)
{
    unsigned long long x = val;
    return x;
}

//==================================================================================

struct Hashtable* HashTableInit (size_t size, unsigned long long (*hash_f)(int))
{
    assert (size);
    struct Hashtable* HashT = calloc (1, sizeof(struct Hashtable));
    HashT->lists_ar = calloc (size, sizeof(struct node_t *));
    assert (HashT);
    assert (HashT->lists_ar);
    HashT->size = size;
    HashT->hash_f = hash_f;

    return HashT;
}
//==================================================================================
struct node *ListInsert (struct node *last, int val)
{
    struct node *cur = last;
    if (cur->next == 0)
    {
        cur->next = calloc (1, sizeof (struct node));
        assert (cur->next);
        cur->val = val;
    }
    else
    {
        struct node *new_node = calloc (1, sizeof (struct node));
        assert (new_node);
        new_node->val = val;
        new_node->next = cur->next;
        cur->next = new_node;
    }
    
    return cur->next;
}
//==================================================================================

void DeleteNodeAft (struct Hashtable *HashT, struct node* last)
{
    assert (last->next);

    if (HashT->list_tail == last->next)
        HashT->list_tail = last;

    struct node* cur = last->next;
    last->next       = cur->next;

    free (cur); 
}

//==================================================================================

void DeleteList (struct node* top)
{
    struct node* cur_node = top;
    struct node* next_node = top;
    while (cur_node->next != 0)
    {
        next_node = cur_node->next;
        free(cur_node);
        cur_node = next_node;
    }
    free(cur_node);
}

//==================================================================================



int HashtableInsert (struct Hashtable* HashT, int m, int val)
{
    assert (HashT);

    int hits = 0;

    #ifdef HASH_T_RESIZE
    if ((float)HashT->inserts / (float)HashT->size >= 0.7)
    {
        HashT = HashTableResize (HashT);
    }
    #endif

    unsigned long long hash = HashT->hash_f (val) % HashT->size;

    if (HashT->lists_ar[hash] == 0)
    {
        struct node *node = calloc (1, sizeof (struct node));
        assert (node);
        node->val = val;
        
        if (HashT->inserts >= m)
        {
            unsigned long long hash2 = HashT->hash_f(HashT->list_tail->val) % HashT->size;
            HashT->lists_ar[hash2] = NULL;
            HashT->list_tail = HashT->list_tail->prev;
            free (HashT->list_tail->next);
            HashT->list_tail->next = NULL;
        } 

        HashT->lists_ar[hash] = node;
        node->next = HashT->list_head;

        if (HashT->inserts == 0)
        {
            HashT->list_head = node;
            HashT->list_tail = node;
        }
        else
        {
            HashT->list_head->prev = node;
            HashT->list_head = node;
        }
    }
    else
    {
        if (HashT->lists_ar[hash]->prev)
            HashT->lists_ar[hash]->prev->next = HashT->lists_ar[hash]->next;
        if (HashT->lists_ar[hash]->next)
            HashT->lists_ar[hash]->next->prev = HashT->lists_ar[hash]->prev;
        else
            HashT->list_tail = HashT->list_head;

        HashT->lists_ar[hash]->next = HashT->list_head;
        HashT->list_head->prev = HashT->lists_ar[hash];
        HashT->list_head = HashT->lists_ar[hash];

        hits = 1;
    }
    HashT->inserts += 1;
    return hits;
}

//==================================================================================

#ifdef HASH_T_RESIZE

struct Hashtable* HashTableResize (struct Hashtable* HashT)
{
    for (unsigned long long int i = 0; i < HashT->size; i++)
        if(HashT->lists_ar[i] != 0)
            free (HashT->lists_ar[i]);
    free (HashT->lists_ar);
    
    
    HashT-> size *= 2;
    HashT->lists_ar = calloc (HashT->size, sizeof (struct node*));

    char* temp_str = 0;
    size_t str_len = 0;
    struct node *last = HashT->list_tail;
    unsigned long long old_inserts = HashT->inserts;
    struct node* cur = HashT->list_head;
    //+++++++++++++++++++++++++++++++++++++++++
    while (cur->next != last)
    {
        HashT->inserts = 0;
        str_len = strlen (cur->next->word);
        temp_str = calloc (str_len + 1, sizeof (char));
        memcpy (temp_str, cur->next->word, str_len);
        DeleteNodeAft (HashT, cur);
        HashtableInsert (HashT, temp_str);
        free (temp_str);
    }
    HashT->inserts = 0;
    str_len = strlen (cur->next->word);
    temp_str = calloc (str_len + 1, sizeof (char));
    memcpy (temp_str, cur->next->word, str_len);
    DeleteNodeAft (HashT, cur);
    HashtableInsert (HashT, temp_str);
    free (temp_str);
    //+++++++++++++++++++++++++++++++++++++++++
    HashT->inserts = old_inserts;
    
    return HashT;
}
#endif

//==================================================================================

void DeleteHastable (struct Hashtable* HashT)
{
    DeleteList (HashT->list_head);
    free (HashT->lists_ar);
    free (HashT);
}