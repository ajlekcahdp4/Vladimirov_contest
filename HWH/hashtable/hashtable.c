#include "hashtable.h"
#include "../dump/dump.h"
#include <string.h>
#include <assert.h>

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


//==================================================================================
void DeleteNodeAft (struct Hashtable *HashT, struct node* last);
//==================================================================================
unsigned long long Hash (const char* str)
{
    unsigned long long hash = 0;
    int c = 0;
    while ((c = *str++) != 0)
        hash = (hash << 5) + (hash << 16) - hash  + c;
    return hash;
}

//==================================================================================

struct Hashtable* HashTableInit (size_t size, unsigned long long (*Hash)(const char*))
{
    assert (size);
    struct Hashtable* HashT = calloc (1, sizeof(struct Hashtable));
    HashT->list_head        = calloc (1, sizeof (struct node));
    HashT->lists_ar         = calloc (size, sizeof(struct node*));
    assert (HashT);
    assert (HashT->lists_ar);
    assert (HashT->list_head);
    HashT->size      = size;
    HashT->hash_func = Hash;
    HashT->list_tail = HashT->list_head;

    return HashT;
}
//==================================================================================
struct node *ListInsert (struct node *last, int str_len, char* word)
{
    struct node *cur = last;
    if (cur->next == 0)
    {
        cur->next       = calloc (1, sizeof (struct node));
        cur->next->word = calloc (str_len + 1, sizeof (char));

        assert (cur->next);
        assert (cur->next->word);

        memcpy (cur->next->word, word, str_len);
    }
    else
    {
        struct node *new_node = calloc (1, sizeof (struct node));
        new_node->word        = calloc (str_len + 1, sizeof (char));

        assert (new_node);
        assert (new_node->word);

        new_node->next = cur->next;
        memcpy (new_node->word, word, str_len * sizeof (char));
        cur->next = new_node;
    }
    
    return cur->next;
}
//==================================================================================



struct Hashtable* HashtableInsert (struct Hashtable* HashT, char* word)
{
    int str_len = strlen (word);
    unsigned long long hash = HashT->hash_func (word) % HashT->size;

    if (HashT->lists_ar[hash] == 0)
    {
        //printf("+ ");
        HashT->lists_ar[hash] = calloc (1, sizeof(struct node));
        assert (HashT->lists_ar[hash]);
        
        HashT->lists_ar[hash]->next = ListInsert (HashT->list_tail, str_len, word);
        HashT->list_tail       = HashT->list_tail->next;
    }
    else
    {
        //printf("* ");
        if ((float)HashT->inserts / (float)HashT->size >= 0.7)
        {
            HashT = HashTableResize (HashT);
            hash  = HashT->hash_func (word) % HashT->size;
        }
        struct node* cur = HashT->lists_ar[hash];

        while (cur != HashT->list_tail && HashT->hash_func(cur->next->word) % HashT->size == hash) //segfault
            cur = cur->next;//Дошли до последнего элемента с нашим хэшем
        if (cur == HashT->list_tail)
        {
            ListInsert (cur, str_len, word);
            HashT->list_tail = HashT->list_tail->next;
        }
        else
        {
            ListInsert (cur, str_len, word);
        }
    }

    HashT->inserts += 1;
    //printf ("list_tail = %p\n", HashT->list_tail);
    return HashT;
}

//==================================================================================



struct Hashtable* HashTableResize (struct Hashtable* HashT) //This fucking shitty bug, not work after
{
    HashTDump (HashT, "BefResize.png");
    struct node* cur = HashT->list_head;
    assert (cur);
    free (HashT->lists_ar);
    HashT-> size *= 2;
    HashT->lists_ar = calloc (HashT->size, sizeof (struct node*));
    char* temp_str = 0;
    int str_len = 0;
    struct node *last = HashT->list_tail;

    unsigned long long old_inserts = HashT->inserts;
    //+++++++++++++++++++++++++++++++++++++++++
    while (cur != last)
    {   printf ("<%s>\n", cur->next->word);
        str_len = strlen (cur->next->word);
        temp_str = calloc (str_len + 1, sizeof (char));
        memcpy (temp_str, cur->next->word, str_len);
        DeleteNodeAft (HashT, cur);
        HashtableInsert (HashT, temp_str);
        cur = cur->next;
        free (temp_str);
    }
    HashT->inserts = old_inserts;
    /*
        str_len = strlen (cur->next->word);
        temp_str = calloc (str_len + 1, sizeof (char));
        memcpy (temp_str, cur->next->word, str_len);
        DeleteNodeAft (HashT, cur);
        HashtableInsert (HashT, temp_str);*/
        HashTDump (HashT, "aftRes.png");
    //+++++++++++++++++++++++++++++++++++++++++
    return HashT;
}

//==================================================================================

int NumOfWord (struct Hashtable* HashT, char* word) //Still does not rewrite to one-list hashtable
{
    
    //printf ("%p->", HashT->lists_ar[hash]->next->word);
    //printf ("%p->", HashT->lists_ar[hash]->next->next->word);
    //printf ("%p\n", HashT->lists_ar[hash]->next->next->next->word);

    int N  = 0;
    unsigned long long word_hash = HashT->hash_func (word) % HashT->size;
    struct node* cur_node        = HashT->lists_ar[word_hash];

    if (cur_node == 0)
        return 0;


    while (cur_node->next != 0 && HashT->hash_func (cur_node->next->word) % HashT->size == word_hash)
    {
        if (strcmp(word, cur_node->next->word) == 0)
            N += 1;
        cur_node = cur_node->next;
    }

    return N;
}

//==================================================================================
void HashTDump (struct Hashtable *HashT, char *name)
{
    FILE *dotfile  = fopen ("dump.dot", "w");

    DtStart (dotfile);
    DtSetTitle (dotfile, HashT);
    struct node *cur = HashT->list_head->next;
    while (cur != 0)
    {
        DtSetNode (dotfile, cur);
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
    free (command);
}
//==================================================================================

void DeleteNodeAft (struct Hashtable *HashT, struct node* last)
{
    assert (last->next);

    struct node* cur = last->next;
    last->next       = cur->next;

    if (HashT->list_tail == last->next)
        HashT->list_tail = last;
    free (cur->word);
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
        free(cur_node->word);
        free(cur_node);
        cur_node = next_node;
    }
    free(cur_node->word);
    free(cur_node);
}

//==================================================================================

void DeleteHastable (struct Hashtable* HashT)
{
    DeleteList (HashT->list_head);
    free (HashT->lists_ar);
    free (HashT);
}