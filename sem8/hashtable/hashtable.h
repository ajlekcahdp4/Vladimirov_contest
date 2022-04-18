#include <stdio.h>
#include <stdlib.h>
struct node;
struct Hashtable;

unsigned long long hash (int val);
struct Hashtable* HashTableInit (size_t size, unsigned long long (*hash_f)(int));
int HashtableInsert (struct Hashtable* HashT, int m, int val);
void DeleteHastable (struct Hashtable* HashT);
