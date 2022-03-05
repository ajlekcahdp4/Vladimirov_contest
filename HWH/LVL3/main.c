#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable/hashtable.h"


size_t ReadWordF  (char* temp_str);
void   TextInput  (char** buf, size_t N);
char** WordsInput (size_t N);
void   End        (struct Hashtable* HashT, char** buf, size_t N);
size_t ReadWord   (char* temp_str);

struct Hashtable *FillHashtable (struct Hashtable *HashT, size_t N);
//======================================================================


size_t ReadWord (char* temp_str)
{
    int c = getchar ();
    int i = 0;
    while (c == ' ' || c == '\n' || c == '\r')
        c = getchar ();

    while (c != ' ' && c != '\n' && c != '\r' && c != EOF)
    {
        temp_str[i] = (char)c;
        i++;
        c = getchar();
    }
    temp_str[i] = '\0';
    return strlen (temp_str);
}   




void TextInput (char** buf, size_t N)
{
    size_t str_len = 0;
    char* temp_str = calloc (100, sizeof(char));

    for (size_t i = 0; i < N; i++)
    {
        Readword (temp_str);
        str_len = strlen (temp_str);
        buf[i] = calloc (str_len, sizeof (char));
        memcpy (buf[i], temp_str, (str_len + 1)*sizeof(char));
    }
}

struct Hashtable *FillHashtable (struct Hashtable *HashT, size_t N)
{
    for (size_t first = 0; first < N; first++)
    {
        for (size_t second = 0; second < N; second++)
        {
                
        }
    }
}


void End (struct Hashtable* HashT, char** buf, size_t N)
{
    DeleteHastable (HashT);
    for (size_t i = 0; i < N; i++)
    {
        if (buf[i] != 0)
            free (buf[i]);
    }
    free(buf);
}


int main ()
{
    int res                 = 0;
    size_t N                = 0;
    struct Hashtable* HashT = 0;
    char** buf = 0;
    size_t start_size = 10000;

    res = scanf("%lu", &N);
    assert (res);
    
    buf = calloc (N, sizeof (char*));
    TextInput (buf, N);

    HashT = HashTableInit (start_size, Hash);

    End (HashT, buf, N);
    return 0;
}