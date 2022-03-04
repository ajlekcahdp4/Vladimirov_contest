#include <stdio.h>
#include <stdlib.h>
struct node;
struct Hashtable;

unsigned long long Hash (const char* str);
struct Hashtable* HashTableInit   (size_t size, unsigned long long (*hash_f)(const char*));
struct Hashtable* HashTableResize (struct Hashtable* HashT);
struct Hashtable* HashtableInsert (struct Hashtable* HashT, char* word);
void HashTDump (struct Hashtable *HashT, char *name);
int NumOfWord       (struct Hashtable* HashT, char* word);
void DeleteHastable (struct Hashtable* HashT);
