#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable/hashtable.h"



int RequestInput(struct Hashtable *HashT, int m, int n)
{
    int request = 0;
    int res = 0;
    int hits = 0;
    for (int i = 0; i < n; i++)
    {
        res = scanf("%d", &request);
        assert(res);
        hits += HashtableInsert(HashT, m, request);
    }
    return hits;
}

#define MAGIC_NUMBER ((size_t)1000000)

int main()
{
    int res = 0;
    int m = 0;
    int n = 0;
    int hits = 0;
    struct Hashtable *HashT = NULL;

    res = scanf("%d", &m);
    assert(res);
    res = scanf("%d", &n);
    assert(res);

    HashT = HashTableInit(MAGIC_NUMBER, hash);

    hits = RequestInput(HashT, m, n);

    printf("%d\n", hits);

    DeleteHastable(HashT);
    return 0;
};