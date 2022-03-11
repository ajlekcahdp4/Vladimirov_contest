#include <stdio.h>
#include <stdlib.h>
struct node;
struct Hashtable;

unsigned long long Hash (const char* str);
struct Hashtable *HashTableInit   (size_t size, unsigned long long (*hash_f)(const char*));
struct Hashtable *HashTableResize (struct Hashtable* HashT);
struct Hashtable *HashtableInsert (struct Hashtable* HashT, char* word);
struct Hashtable *FillHashtable (struct Hashtable *HashT, char **buf, size_t N);
void HashTDump (struct Hashtable *HashT, char *name);
size_t NumOfWord       (struct Hashtable* HashT, char* word);
size_t NumberOfFour (struct Hashtable *HashT);
void DeleteHastable (struct Hashtable* HashT);
