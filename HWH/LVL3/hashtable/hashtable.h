#ifndef HASHTABLE_INCLUDED
#define HASHTABLE_INCLUDED
struct node_t;
struct Hashtable;

struct buffer
{
    char **str_array;
    size_t capacity;
    size_t size;
};



struct Hashtable *FillHashtable (struct Hashtable *HashT, struct buffer *buf);
int NodesCmp (struct buffer *buf, const struct node_t *node1, const struct node_t *node2);
unsigned long long HashNode (struct buffer *buf, struct node_t *node);
void DeleteHastable (struct Hashtable* HashT);
void HashTDump (struct Hashtable *HashT, struct buffer *buf, char *name);
size_t NumberOfFour (struct buffer *buf, struct Hashtable *HashT);
struct Hashtable* HashTableInit (size_t size, unsigned long long (*HashFunc)(struct buffer*, struct node_t*), \
    int (*Cmp)(struct buffer *buf, const struct node_t *node1, const struct node_t *node2));

#endif