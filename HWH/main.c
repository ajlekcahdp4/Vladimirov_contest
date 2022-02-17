#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable/hashtable.h"



int ReadWord (char* temp_str)
{
    char c = getchar();
    int i = 0;
    while (c == ' ' || c == '\n' || c == '\r')
        c = getchar();

    while (c != ' ' && c != '\n' && c != '\r')
    {
        temp_str[i] = c;
        i++;
        c = getchar();
    }
    temp_str[i] = '\0';
    return strlen (temp_str);
}   




void TextInput (struct Hashtable* HashT, long long text_len)
{
    char* temp_str = calloc (100, sizeof(char));

    int str_len = 0;
    for (int len_trav = 0; len_trav < text_len; len_trav++)
    {
        ReadWord (temp_str);
        str_len = strlen (temp_str);
        HashtableInsert (HashT, temp_str);
        len_trav += str_len;
    }
    free (temp_str);
}



char** WordsInput (int N)
{
    int words_len = 0;
    char** words = calloc (N, sizeof(char*));

    scanf("%d", &words_len);
    for (int i = 0; i < N; i++)
    {
        words[i] = calloc (words_len, sizeof(char));
        scanf("%s", words[i]);
    }
    return words;
}




void End (struct Hashtable* HashT, char** words, int N)
{
    DeleteHastable (HashT);
    for (int i = 0; i < N; i++)
    {
        if (words[i] != 0)
            free (words[i]);
    }
    free(words);
}


int main ()
{
    int N = 0;
    long long text_len = 0;
    struct Hashtable* HashT = 0;
    char** words = 0;

    scanf("%d", &N);
    scanf("%lld", &text_len);
    HashT = HashTableInit (10, Hash);
    TextInput (HashT, text_len); 
    words = WordsInput (N);
    

    
    HashT = HashTableResize (HashT);

    //======================================================
    for (int i = 0; i < N; i++)
        printf ("%d ", NumOfWord(HashT, words[i]));
    putchar('\n');
    End (HashT, words, N);
    return 0;
}