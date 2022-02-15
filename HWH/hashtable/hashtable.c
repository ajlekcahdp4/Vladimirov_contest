#include "hashtable.h"


unsigned long long Hash (const char* str)
{
    unsigned long long hash = 0;
    int c = 0;
    while ((c = *str++) != 0)
        hash = (hash << 5) + (hash << 16) - hash  + c;
    return hash % 1000;
}

Hashtable* HashTableInit (size_t size, unsigned long long (*Hash)(const char*))
{
    Hashtable* HashT = calloc (1, sizeof(Hashtable));
    HashT->size = size;
    HashT->lists_ar = calloc (HashT->size, sizeof(node*));
    HashT->hash_func = Hash;
    return HashT;
}

Hashtable* HashTableResize (Hashtable* Hash_T)
{
    Hash_T->size = Hash_T->size * 2;
    Hash_T->lists_ar = realloc (Hash_T->lists_ar, Hash_T->size * sizeof(node));
    return Hash_T;
}

void DeleteList (node* top)
{
    node* cur_node = top;
    node* next_node = top;
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