#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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

unsigned long long Hash (const char* str)
{
    unsigned long long hash = 0;
    int c = 0;
    while ((c = *str++) != 0)
        hash = (hash << 5) + (hash << 16) - hash  + c;
    return hash % 1000;
}

Hashtable* HashTableInit (size_t size, unsigned long long (*Hash)(const char*))
{
    Hashtable* HashT = calloc (1, sizeof(Hashtable));
    HashT->size = size;
    HashT->lists_ar = calloc (HashT->size, sizeof(node*));
    HashT->hash_func = Hash;
    return HashT;
}


void TextInput (Hashtable* HashT, long long text_len) //segfault на больших текстах
{
    int hash = 0;
    char* temp_str = calloc (100, sizeof(char));

    int str_len = 0;
    for (int len_trav = 0; len_trav < text_len; len_trav++)
    {
        ReadWord (temp_str);
        str_len = strlen (temp_str);

        hash = Hash (temp_str) % HashT->size;
        if (HashT->lists_ar[hash] == 0)
        {

            HashT->lists_ar[hash] = calloc (1, sizeof(node));
            HashT->lists_ar[hash]->word = calloc (str_len + 1, sizeof(char));
            memcpy(HashT->lists_ar[hash]->word, temp_str, str_len);
        }
        else
        {
            node* cur = HashT->lists_ar[hash];
            while (cur->next != 0)
                cur = cur->next;
            cur->next = calloc (1, sizeof (node));
            cur = cur->next;
            cur->word = calloc (str_len + 1, sizeof(char));
            memcpy(cur->word, temp_str, str_len);
        }
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

int NumOfWord (node** text, char* word)
{
    int N = 0;

    int word_hash = Hash (word);
    node* cur_node = text[word_hash];
    if (cur_node == 0)
        return 0;
    while (cur_node->next != 0)
    {
        if (strcmp(word, cur_node->word) == 0)
            N += 1;
        cur_node = cur_node->next;
    }
    if (strcmp(word, cur_node->word) == 0)
        N += 1;
    cur_node = cur_node->next;
    return N;
}

void DeleteList (node* top)
{
    node* cur_node = top;
    node* next_node = top;
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


void End (node** buf, char** words, int N)
{
    for (int i = 0; i < 999; i++)
    {
        if (buf[i] != 0)
        {
            DeleteList (buf[i]);
        }
    }
    free(buf);


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
    Hashtable* HashT = 0;
    char** words = 0;

    scanf("%d", &N);
    scanf("%lld", &text_len);
    HashT = HashTableInit (1000, Hash);
    TextInput (HashT, text_len); 
    words = WordsInput (N);

    //======================================================
    for (int i = 0; i < N; i++)
        printf ("%d ", NumOfWord(HashT->lists_ar, words[i]));
    End (HashT->lists_ar, words, N);
    return 0;
}