#include "hashtable.h"
#include "../dump/dump.h"
#include <string.h>
#include <assert.h>

struct node_t {
    unsigned ip1;
    unsigned ip2;
    struct node_t *next;
};

struct Hashtable_elem {
    struct node_t *next;
    unsigned capacity;
};

struct Hashtable {
    struct Hashtable_elem **lists_ar;
    struct node_t  *list_head;
    struct node_t  *list_tail;
    unsigned long long size;
    unsigned long long inserts;
    unsigned long long (*HashFunc)(struct buffer*, struct node_t*);
    int (*Cmp)(struct buffer*, struct node_t*, struct node_t*);
};

struct node_t *ListInit (void);
size_t ListCount (struct node_t *top, struct node_t *aim_node);
int nodecmp (struct node_t* node1, struct node_t* node2);
struct node_t *ListInsert (struct node_t *last, size_t str_len, char* word);
void DeleteNodeAft (struct Hashtable *HashT, struct node_t* last);
void DeleteList (struct node_t* top);
void ClearStr (char* str);
void ListDump (struct node_t *top);
unsigned long long djb2 (const char* str);


//==================================================================================
//=================================STRUCT_FUNCTIONS=================================
//==================================================================================
#define MAX_STR_LEN 128

int NodesCmp (struct buffer *buf, struct node_t *node1, struct node_t *node2)
{
    int res = 0;
    char *temp_str_1 = calloc (MAX_STR_LEN, sizeof(char));
    char *temp_str_2 = calloc (MAX_STR_LEN, sizeof(char));
    strcat (temp_str_1, buf->str_array[node1->ip1]);
    strcat (temp_str_1, buf->str_array[node1->ip2]);

    strcat (temp_str_2, buf->str_array[node1->ip1]);
    strcat (temp_str_2, buf->str_array[node1->ip2]);

    res = strcmp (temp_str_1, temp_str_2);
    
    free (temp_str_1);
    free (temp_str_2);
    return res;
}
//==================================================================================

unsigned long long HashNode (struct buffer *buf, struct node_t *node)
{
    unsigned long long hash = 0;
    char *temp_str = calloc (MAX_STR_LEN, sizeof(char));
    strcat (temp_str, buf->str_array[node->ip1]);
    strcat (temp_str, buf->str_array[node->ip2]);

    hash = djb2 (temp_str);

    free (temp_str);
    return hash;
}

#undef MAX_STR_LEN
//==================================================================================

unsigned long long djb2 (const char* str)
{
    unsigned long long hash = 0;
    unsigned long long c = 0;
    while ((c = (unsigned long long)(*str++)) != 0)
        hash = (hash << 5) + (hash << 16) - hash  + c;
    return hash;
}


//==================================================================================
//===================================LIST_FUNCTIONS=================================
//==================================================================================
struct node_t *ListInit (void)
{
    struct node_t *top = calloc (1, sizeof (struct node_t));
    return top;
}
//==================================================================================
size_t ListCount (struct node_t *top, struct node_t *aim_node)
{
    assert (top);
    assert (aim_node);

    size_t cnt = 0;
    struct node_t *cur = top;
    while (cur)
    {
        if (cur != top && nodecmp (cur, aim_node) == 0)
            cnt += 1;
        cur = cur->next;
    }
    return cnt;
}

//==================================================================================
void ListDump (struct node_t *top)
{
    struct node_t *cur = top->next;

    while (cur)
    {
        printf ("\"%s\"[%llu]->", cur->word, Hash (cur->word) % 200);
        cur = cur->next;
    }
    printf("\n\n");
}
//==================================================================================

struct Hashtable* HashTableInit (size_t size, unsigned long long (*hash_f)(const char*))
{
    assert (size);
    struct Hashtable* HashT = calloc (1, sizeof(struct Hashtable));
    HashT->list_head        = calloc (1, sizeof (struct node_t));
    HashT->lists_ar         = calloc (size, sizeof(struct Hashtable_elem*));
    assert (HashT);
    assert (HashT->lists_ar);
    assert (HashT->list_head);
    HashT->size      = size;
    HashT->HashFunc = hash_f;
    HashT->list_tail = HashT->list_head;

    return HashT;
}
//==================================================================================
struct node_t *ListInsert (struct node_t *last, size_t str_len, char* word)
{
    struct node_t *cur = last;
    if (cur->next == 0)
    {
        cur->next       = calloc (1, sizeof (struct node_t));
        cur->next->word = calloc (str_len + 1, sizeof (char));

        assert (cur->next);
        assert (cur->next->word);

        memcpy (cur->next->word, word, str_len * sizeof(char));
    }
    else
    {
        struct node_t *new_node = calloc (1, sizeof (struct node_t));
        new_node->word        = calloc (str_len + 1, sizeof (char));

        assert (new_node);
        assert (new_node->word);

        memcpy (new_node->word, word, str_len * sizeof (char));
        new_node->next = cur->next;
        cur->next = new_node;
    }
    
    return cur->next;
}
//==================================================================================

void DeleteNodeAft (struct Hashtable *HashT, struct node_t* last)
{
    assert (last->next);

    if (HashT->list_tail == last->next)
        HashT->list_tail = last;

    struct node_t* cur = last->next;
    last->next       = cur->next;

    free (cur->word);
    free (cur); 
}

//==================================================================================

void DeleteList (struct node_t* top)
{
    struct node_t* cur_node = top;
    struct node_t* next_node = top;
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

//==================================================================================



struct Hashtable* HashtableInsert (struct Hashtable* HashT, struct buffer *buf, size_t ip1, size_t ip2) //done
{
    assert (HashT);
    assert (buf);
    if ((float)HashT->inserts / (float)HashT->size >= 0.7)
    {
        HashT = HashTableResize (HashT);
    }

    struct node_t *new_node = calloc (1, sizeof(char));
    new_node->ip1 = ip1;
    new_node->ip2 = ip2;


    unsigned long long hash = HashT->HashFunc (buf, new_node) % HashT->size;

    if (HashT->lists_ar[hash] == 0)
    {
        HashT->lists_ar[hash] = calloc (1, sizeof(struct Hashtable_elem));
        assert (HashT->lists_ar[hash]);
        
        HashT->lists_ar[hash]->next = ListInsert (HashT->list_tail, new_node);
        HashT->list_tail            = HashT->list_tail->next;
    }
    else
    {
        struct node_t* cur = HashT->lists_ar[hash]->next;
        
        size_t i = 0;
        while (cur->next && i < HashT->lists_ar[hash]->capacity - 1)
        {
            cur = cur->next;
            i++;
        }
        assert (cur);
        if (cur == HashT->list_tail)
        {
            ListInsert (HashT->list_tail, new_node);
            HashT->list_tail = HashT->list_tail->next;
        }
        else
        {
            ListInsert (cur, new_node);
        }
    }

    HashT->lists_ar[hash]->capacity += 1;
    HashT->inserts                  += 1;
    return HashT;
}

//==================================================================================



struct Hashtable* HashTableResize (struct Hashtable* HashT)
{
    for (unsigned long long int i = 0; i < HashT->size; i++)
        if(HashT->lists_ar[i] != 0)
            free (HashT->lists_ar[i]);
    free (HashT->lists_ar);
    
    
    HashT-> size *= 2;
    HashT->lists_ar = calloc (HashT->size, sizeof (struct node_t*));

    char* temp_str = 0;
    size_t str_len = 0;
    struct node_t *last = HashT->list_tail;
    unsigned long long old_inserts = HashT->inserts;
    struct node_t* cur = HashT->list_head;
    //+++++++++++++++++++++++++++++++++++++++++
    while (cur->next != last)
    {
        HashT->inserts = 0;
        str_len = strlen (cur->next->word);
        temp_str = calloc (str_len + 1, sizeof (char));
        memcpy (temp_str, cur->next->word, str_len);
        DeleteNodeAft (HashT, cur);
        HashtableInsert (HashT, temp_str);
        free (temp_str);
    }
    HashT->inserts = 0;
    str_len = strlen (cur->next->word);
    temp_str = calloc (str_len + 1, sizeof (char));
    memcpy (temp_str, cur->next->word, str_len);
    DeleteNodeAft (HashT, cur);
    HashtableInsert (HashT, temp_str);
    free (temp_str);
    //+++++++++++++++++++++++++++++++++++++++++
    HashT->inserts = old_inserts;
    
    return HashT;
}

//==================================================================================

size_t NumOfWord (struct Hashtable* HashT, char* word)
{

    size_t N  = 0;
    unsigned long long word_hash = HashT->hash_func (word) % HashT->size;
    if (HashT->lists_ar[word_hash] == 0)
        return 0;

    struct node_t* cur_node        = HashT->lists_ar[word_hash]->next;
    
    for (size_t i = 0; i < HashT->lists_ar[word_hash]->capacity - 1; i++)
    {

        if (strcmp(word, cur_node->word) == 0)
            N += 1;
        cur_node = cur_node->next;
    }

    if (strcmp(word, cur_node->word) == 0)
            N += 1;

    return N;
}

size_t NumberOfFour (struct Hashtable *HashT)
{
    size_t numb_of_four   = 0;
    size_t cnt            = 0;
    struct node_t *cur      = 0;
    struct node_t *cmp_node = 0;
    struct node_t *top      = 0;
    struct node_t *last     = 0;
    struct node_t *runner   = 0;

    for (size_t i = 0; i < HashT->size; i++)
    {
        if (HashT->lists_ar[i])
        {
            top = ListInit ();
            last = top;

            cur = HashT->lists_ar[i]->next;
            cmp_node = cur;

            for (size_t j = 0; j < HashT->lists_ar[i]->capacity - 1; j++)
            {
                if (ListCount (top, cmp_node) == 0)
                {
                    last = ListInsert (last, strlen (cmp_node->word), cmp_node->word);
                    //=====================================
                    cnt = 0;
                    runner = HashT->lists_ar[i]->next;
                    size_t k = 0;
                    while (runner && k < HashT->lists_ar[i]->capacity)
                    {
                        if (nodecmp (runner, cmp_node) == 0)
                        {
                            cnt += 1;
                        }
                        runner = runner->next;
                        k++;
                    }
                    //=====================================
                    if (cnt > 1)
                    {
                        numb_of_four += (cnt * (cnt - 1)) / 2;
                    }
                }
                cmp_node = cmp_node->next;
            }
            DeleteList (top);
        }
    }
    


    return numb_of_four;
}


//==================================================================================
void HashTDump (struct Hashtable *HashT, char *name)
{
    FILE *dotfile  = fopen ("dump.dot", "w");

    DtStart (dotfile);
    DtSetTitle (dotfile, HashT);
    struct node_t *cur = HashT->list_head->next;
    DtSetBuf (dotfile, HashT);
    while (cur != 0)
    {
        DtSetNodes (dotfile, cur, HashT);
        cur = cur->next;
    }
    fprintf (dotfile, "\n\n\n");

    DtSetDependence (dotfile, HashT);

    DtEnd (dotfile);
    fclose (dotfile);
    
    char *command = calloc (100, sizeof(char));
    memcpy (command, "dot dump.dot -T png -o ", 23 * sizeof(char));
    strcat (command, name);
    system (command);
    //system ("rm dump.dot");
    free (command);
}
//==================================================================================
struct Hashtable *FillHashtable (struct Hashtable *HashT, struct buffer *buf)
{
    for (size_t first = 0; first < buf->size; first++)
    {
        for (size_t second = 0; second < buf->size; second++)
        {
            if (first != second)
                HashTableInsert (HashT, buf, first, second);
        }
    }
    
    return HashT;
}




//==================================================================================
void ClearStr (char* str)
{
    size_t i = 0;
    while (str[i] != '\0')
    {
        str[i] = '\0';
        i++;
    }
}
//==================================================================================
void DeleteHastable (struct Hashtable* HashT)
{
    DeleteList (HashT->list_head);
    for (unsigned long long int i = 0; i < HashT->size; i++)
        if(HashT->lists_ar[i] != 0)
            free (HashT->lists_ar[i]);
    free (HashT->lists_ar);
    free (HashT);
}
