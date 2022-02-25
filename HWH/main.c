#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable/hashtable.h"


struct node {
    char* word;
    struct node *next;
};

struct Hashtable {
    struct node **lists_ar;
    struct node  *list_head;
    struct node  *list_tail;
    unsigned long long size;
    unsigned long long inserts;
    unsigned long long (*hash_func)(const char*);
};

struct node *ListInsert (struct node *last, int str_len, char* word);
//======================================================================


int ReadWordF (char* temp_str, FILE* input)
{
    char c = fgetc (input);
    int i = 0;
    while (c == ' ' || c == '\n' || c == '\r')
        c = fgetc (input);

    while (c != ' ' && c != '\n' && c != '\r' && c != EOF)
    {
        temp_str[i] = c;
        i++;
        c = fgetc(input);
    }
    temp_str[i] = '\0';
    return strlen (temp_str);
}   




void TextInput (struct Hashtable* HashT, long long text_len, FILE* input) //не все слова
{
    char* temp_str = calloc (100, sizeof(char));
    assert(temp_str);

    int str_len = 0;
    for (int len_trav = 0; len_trav < text_len; len_trav++)
    {
        ReadWordF (temp_str, input);
        str_len = strlen (temp_str);
        HashtableInsert (HashT, temp_str);
        len_trav += str_len;

    }
    free (temp_str);
}



char** WordsInput (int N, FILE* input)
{
    int words_len = 0;
    char** words = calloc (N, sizeof(char*));

    assert(fscanf(input, "%d", &words_len));
    for (int i = 0; i < N; i++)
    {
        words[i] = calloc (words_len, sizeof(char));
        ReadWordF (words[i], input);
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
    int N                   = 0;
    long long text_len      = 0;
    struct Hashtable* HashT = 0;
    char** words            = 0;
    FILE* input = fopen ("input.txt", "r");

    assert(fscanf(input, "%d", &N));
    assert(fscanf(input, "%lld", &text_len));
    
    
    HashT = HashTableInit (100, Hash);
    TextInput (HashT, text_len, input); 
    words = WordsInput (N, input);
    //printffff
    /*
    struct node *cur = HashT->list_head->next;
    while (cur->next)
    {
        printf ("\n%p, %s, %p\n", cur, cur->word, cur->next);
        cur = cur->next;
    }
    printf ("\n%p, %s, %p\n", cur, cur->word, cur->next);
    //printffff
    */

    HashTDump (HashT, "end.png");
    //======================================================
    for (int i = 0; i < N; i++)
        printf ("%d ", NumOfWord(HashT, words[i]));
    putchar('\n');
    End (HashT, words, N);
    fclose (input);
    return 0;
}