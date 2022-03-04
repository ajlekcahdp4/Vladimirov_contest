#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable/hashtable.h"


size_t ReadWordF (char* temp_str);
void TextInput (struct Hashtable* HashT, size_t text_len);
char** WordsInput (size_t N);
void End (struct Hashtable* HashT, char** words, size_t N);
size_t ReadWord (char* temp_str);
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




void TextInput (struct Hashtable* HashT, size_t text_len)
{
    char* temp_str = calloc (100, sizeof(char));
    assert(temp_str);

    size_t str_len = 0;
    for (size_t len_trav = 0; len_trav < text_len; len_trav++)
    {
        ReadWord (temp_str);
        str_len = strlen (temp_str);
        HashtableInsert (HashT, temp_str);
        len_trav += str_len;

    }
    free (temp_str);
}



char** WordsInput (size_t N)
{
    int res = 0;
    size_t words_len = 0;
    char** words = calloc (N, sizeof(char*));

    res = scanf("%lu", &words_len);
    assert (res);
    for (size_t i = 0; i < N; i++)
    {
        words[i] = calloc (words_len, sizeof(char));
        ReadWord (words[i]);
    }
    return words;
}




void End (struct Hashtable* HashT, char** words, size_t N)
{
    DeleteHastable (HashT);
    for (size_t i = 0; i < N; i++)
    {
        if (words[i] != 0)
            free (words[i]);
    }
    free(words);
}


int main ()
{
    int res                 = 0;
    size_t N                = 0;
    size_t text_len         = 0;
    struct Hashtable* HashT = 0;
    char** words            = 0;

    res = scanf("%lu", &N);
    assert (res);
    res = scanf("%lu", &text_len);
    assert (res);
    
    
    HashT = HashTableInit (128, Hash);
    TextInput (HashT, text_len); 
    words = WordsInput (N);
    
    for (size_t i = 0; i < N; i++)
        printf ("%d ", NumOfWord(HashT, words[i]));
    putchar('\n');
    End (HashT, words, N);
    return 0;
}