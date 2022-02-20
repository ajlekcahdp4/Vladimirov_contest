#include <stdio.h>
#include <stdlib.h>
struct node;
struct Hashtable;

unsigned long long Hash (const char* str);
struct Hashtable* HashTableInit (size_t size, unsigned long long (*Hash)(const char*));
void DeleteHastable (struct Hashtable* HashT);
struct Hashtable* HashTableResize (struct Hashtable* OldHashT);
struct Hashtable* HashtableInsert (struct Hashtable* HashT, char* word);
int NumOfWord (struct Hashtable* HashT, char* word);
