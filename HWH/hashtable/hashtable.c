#include "hashtable.h"
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
    size_t size;
    size_t inserts;
    unsigned long long (*hash_func)(const char*);
};


//==================================================================================
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
        HashT->lists_ar[hash] = calloc (1, sizeof(struct node));
        assert (HashT->lists_ar[hash]);
        
        HashT->list_tail->next = ListInsert (HashT->lists_ar[hash], str_len, word);
        HashT->list_tail       = HashT->list_tail->next;
    }
    else
    {
        if (HashT->inserts / HashT->size >= 0.7)
            HashT = HashTableResize (HashT);
        
        struct node* cur = HashT->lists_ar[hash]->next;

        while (HashT->hash_func(cur->next->word) == hash)
            cur = cur->next;//Дошли до последнего элемента с нашим хэшем

        ListInsert (cur, str_len, word);
    }
    return HashT;
}

//==================================================================================



struct Hashtable* HashTableResize (struct Hashtable* OldHashT) //Still does not rewrite to one-list hashtable
{
    struct Hashtable* NewHashT = 0;
    struct node* cur = 0;
    struct node* next = 0;
    NewHashT = HashTableInit (2 * OldHashT->size, Hash);
    //+++++++++++++++++++++++++++++++++++++++++
    for (unsigned int i = 0; i < OldHashT->size; i++)
    {
        if (OldHashT->lists_ar[i])
        {
            cur = OldHashT->lists_ar[i];
            next = cur->next;
            while (next)
            {
                if (cur->word != 0)
                    HashtableInsert (NewHashT, cur->word);
                cur = next;
                next = cur->next;
            }
            if (cur->word != 0)
                    HashtableInsert (NewHashT, cur->word);
        }
    }
    //+++++++++++++++++++++++++++++++++++++++++
    DeleteHastable (OldHashT);
    return NewHashT;
}

//==================================================================================

int NumOfWord (struct Hashtable* HashT, char* word) //Still does not rewrite to one-list hashtable
{
    int N = 0;

    int word_hash = HashT->hash_func (word) % HashT->size;
    if (HashT->lists_ar[word_hash] == 0)
        return 0;
    struct node* cur_node = HashT->lists_ar[word_hash]->next;

    if (cur_node == 0)
        return 0;

    while (cur_node->next != 0)
    {
        if (strcmp(word, cur_node->word) == 0)
            N += 1;
        cur_node = cur_node->next;
    }
    
    if (strcmp(word, cur_node->word) == 0)
        N += 1;
    cur_node = cur_node->next;
    return N;
}


//==================================================================================

void ListDeleteNodeAft (struct node* last)
{
    assert (last->next);

    struct node* cur = last->next;
    last->next       = cur->next;

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