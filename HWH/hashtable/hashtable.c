#include "hashtable.h"
#include <string.h>

struct node {
    char* word;
    struct node* next;
};

struct Hashtable {
    struct node** lists_ar;
    size_t size;
    size_t inserts;
    unsigned long long (*hash_func)(const char*);
};

unsigned long long Hash (const char* str)
{
    unsigned long long hash = 0;
    int c = 0;
    while ((c = *str++) != 0)
        hash = (hash << 5) + (hash << 16) - hash  + c;
    return hash;
}

struct Hashtable* HashTableInit (size_t size, unsigned long long (*Hash)(const char*))
{
    struct Hashtable* HashT = calloc (1, sizeof(struct Hashtable));
    HashT->size = size;
    HashT->lists_ar = calloc (HashT->size, sizeof(struct node*));
    HashT->hash_func = Hash;
    return HashT;
}

struct Hashtable* HashtableInsert (struct Hashtable* HashT, char* word)
{
    int str_len = strlen (word);
    unsigned long long hash = HashT->hash_func (word) % HashT->size;
    if (HashT->lists_ar[hash] == 0)
    {
        HashT->lists_ar[hash] = calloc (1, sizeof(struct node));
        HashT->lists_ar[hash]->word = calloc (str_len + 1, sizeof(char));
        memcpy(HashT->lists_ar[hash]->word, word, str_len);
    }
    else
    {
        if (HashT->inserts / HashT->size >= 0.7)
            HashT = HashTableResize (HashT);
        struct node* cur = HashT->lists_ar[hash];
        while (cur->next != 0)
            cur = cur->next;
        cur->next = calloc (1, sizeof (struct node));
        cur = cur->next;
        cur->word = calloc (str_len + 1, sizeof(char));
        memcpy(cur->word, word, str_len);
    }
    return HashT;
}


struct Hashtable* HashTableResize (struct Hashtable* Hash_T)
{
    Hash_T->size = Hash_T->size * 2;
    Hash_T->lists_ar = realloc (Hash_T->lists_ar, Hash_T->size * sizeof(struct node));
    return Hash_T;
}

int NumOfWord (struct Hashtable* HashT, char* word)
{
    int N = 0;

    int word_hash = Hash (word) % HashT->size;
    struct node* cur_node = HashT->lists_ar[word_hash];

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
void DeleteHastable (struct Hashtable* HashT)
{
    for (unsigned int i = 0; i < HashT->size; i++)
    {
        if (HashT->lists_ar[i] != 0)
        {
            DeleteList (HashT->lists_ar[i]);
        }
    }
    free(HashT->lists_ar);
    free (HashT);
}