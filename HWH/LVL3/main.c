#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable/hashtable.h"

struct buffer *TextInput (size_t N);
size_t ReadWord  (char **temp_str);
void End (struct Hashtable* HashT, struct buffer *buf);
struct buffer *BufferResize (struct buffer *buf);


//==================================================================================
//====================================FUNCTIONS=====================================
//==================================================================================

#define MAX_STR_LEN 20
size_t ReadWord (char **temp_str)
{
    *temp_str = calloc (MAX_STR_LEN, sizeof(char));
    int c = getchar ();
    int i = 0;

    while (c == ' ' || c == '\n' || c == '\r')
        c = getchar ();

    while (c != ' ' && c != '\n' && c != EOF && c != '\0')
    {
        (*temp_str)[i] = (char)c;
        i++;
        c = getchar();
    }
    (*temp_str)[i] = '\0';
    return strlen (*temp_str);
}   
#undef MAX_STR_LEN

struct buffer *BufferResize (struct buffer *buf)
{
    buf->capacity *= 2;
    buf->str_array = realloc (buf->str_array, buf->capacity * sizeof (char*));
    for (size_t i = buf->size; i < buf->capacity; i++)
        buf->str_array[i] = NULL;
    return buf;
}


#define START_BUFFER_CAPACITY 128
struct buffer *TextInput (size_t N)
{
    char  *temp_str = NULL;

    struct buffer *buf = calloc (1, sizeof(struct buffer));
    assert (buf);
    buf->capacity = START_BUFFER_CAPACITY;
    buf->str_array = calloc (buf->capacity, sizeof (char*));
    assert (buf->str_array);

    for (size_t i = 0; i < N; i++)
    {
        if (buf->size == buf->capacity)
            BufferResize (buf);
        ReadWord (&temp_str);
        buf->str_array[i] = temp_str;
        buf->size += 1;
    }
    return buf;
}
#undef START_BUFFER_CAPACITY




void End (struct Hashtable* HashT, struct buffer *buf)
{
    DeleteHastable (HashT);
    for (size_t i = 0; i < buf->size; i++)
    {
        if (buf->str_array[i] != 0)
            free (buf->str_array[i]);
    }
    free (buf->str_array);
    free(buf);
}

//==================================================================================
//=======================================MAIN=======================================
//==================================================================================


#define START_SIZE_OF_HASH_TABLE 8
int main ()
{
    int res                 = 0;
    size_t N                = 0;
    struct Hashtable* HashT = 0;

    res = scanf("%lu", &N);
    assert (res);

    struct buffer *buf = TextInput (N);
    assert (buf);
    

    HashT = HashTableInit (START_SIZE_OF_HASH_TABLE, HashNode, NodesCmp);
    FillHashtable (HashT, buf);
    printf ("%lu\n", NumberOfFour (buf, HashT));


    End (HashT, buf);
    return 0;
}
#undef START_SIZE_OF_HASH_TABLE