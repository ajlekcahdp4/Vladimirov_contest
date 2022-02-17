#include <stdio.h>
#include <stdlib.h>
struct node;
struct Hashtable;
//opaque data type

unsigned long long Hash (const char* str);
struct Hashtable* HashTableInit (size_t size, unsigned long long (*Hash)(const char*));
void DeleteHastable (struct Hashtable* HashT);
void DeleteList (struct node* top);
struct Hashtable* HashTableResize (struct Hashtable* Hash_T);
struct Hashtable* HashtableInsert (struct Hashtable* HashT, char* word);
int NumOfWord (struct Hashtable* HashT, char* word);
