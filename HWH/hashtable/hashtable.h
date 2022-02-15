#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    char* word;
    struct node* next;
}node;

typedef struct Hashtable {
    node** lists_ar;
    size_t size;
    size_t inserts;
    unsigned long long (*hash_func)(const char*);
} Hashtable;


unsigned long long Hash (const char* str);
Hashtable* HashTableInit (size_t size, unsigned long long (*Hash)(const char*));
void DeleteList (node* top);
Hashtable* HashTableResize (Hashtable* Hash_T);
