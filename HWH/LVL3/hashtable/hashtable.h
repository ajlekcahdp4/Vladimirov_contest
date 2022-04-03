#include <stdio.h>
#include <stdlib.h>
struct node;
struct Hashtable;

struct buffer
{
    char **str_array;
    size_t capacity;
    size_t size;
};




unsigned long long HashIndex (struct buffer *buf, struct node_t *node);
struct Hashtable *HashTableInit   (size_t size, unsigned long long (*hash_f)(const char*));
struct Hashtable *HashTableResize (struct Hashtable* HashT);
struct Hashtable* HashtableInsert (struct Hashtable* HashT, struct buffer *buf, size_t ip1, size_t ip2);
struct Hashtable *FillHashtable (struct Hashtable *HashT, struct buffer *buf);
void HashTDump (struct Hashtable *HashT, char *name);
size_t NumOfWord       (struct Hashtable* HashT, char* word);
size_t NumberOfFour (struct Hashtable *HashT);
void DeleteHastable (struct Hashtable* HashT);
