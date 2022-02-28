#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable/hashtable.h"


size_t ReadWordF (char* temp_str, FILE* input);
void TextInput (struct Hashtable* HashT, size_t text_len, FILE* input);
char** WordsInput (size_t N, FILE* input);
void End (struct Hashtable* HashT, char** words, size_t N);
//======================================================================


size_t ReadWordF (char* temp_str, FILE* input)
{
    int c = fgetc (input);
    int i = 0;
    while (c == ' ' || c == '\n' || c == '\r')
        c = fgetc (input);

    while (c != ' ' && c != '\n' && c != '\r' && c != EOF)
    {
        temp_str[i] = (char)c;
        i++;
        c = fgetc(input);
    }
    temp_str[i] = '\0';
    return strlen (temp_str);
}   




void TextInput (struct Hashtable* HashT, size_t text_len, FILE* input)
{
    char* temp_str = calloc (100, sizeof(char));
    assert(temp_str);

    size_t str_len = 0;
    for (size_t len_trav = 0; len_trav < text_len; len_trav++)
    {
        ReadWordF (temp_str, input);
        str_len = strlen (temp_str);
        HashtableInsert (HashT, temp_str);
        len_trav += str_len;

    }
    free (temp_str);
}



char** WordsInput (size_t N, FILE* input)
{
    size_t words_len = 0;
    char** words = calloc (N, sizeof(char*));

    assert(fscanf(input, "%lu", &words_len));
    for (size_t i = 0; i < N; i++)
    {
        words[i] = calloc (words_len, sizeof(char));
        ReadWordF (words[i], input);
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
    size_t N                = 0;
    size_t text_len         = 0;
    struct Hashtable* HashT = 0;
    char** words            = 0;
    FILE* input = fopen ("input.txt", "r");

    assert(fscanf(input, "%lu", &N));
    assert(fscanf(input, "%lu", &text_len));
    
    
    HashT = HashTableInit (16, Hash);
    TextInput (HashT, text_len, input); 
    words = WordsInput (N, input);
    
    for (size_t i = 0; i < N; i++)
        printf ("%d ", NumOfWord(HashT, words[i]));
    putchar('\n');
    End (HashT, words, N);
    fclose (input);
    return 0;
}