#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct HashTable {
    char* word;
    struct HashTable* next;
}HashTable;


long long Hash (char* str)
{
    long long hash = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
        hash += i*str[i];
    hash = hash % 1000;
    return hash;
}

HashTable** TextInput (long long text_len)
{
    int hash = 0;
    HashTable** buf = calloc(1000, sizeof(HashTable*));
    char* temp_str = calloc (text_len + 1, sizeof(char));

    int str_len = 0;
    for (int len_trav = 0; len_trav < text_len; len_trav++)
    {
        scanf("%s", temp_str);
        str_len = strlen (temp_str);

        hash = Hash (temp_str);
        if (buf[hash] == 0)
        {
            buf[hash] = calloc (1, sizeof(HashTable));
            buf[hash]->word = calloc (str_len + 1, sizeof(char));
            memcpy(buf[hash]->word, temp_str, str_len);
        }
        else
        {
            HashTable* cur = buf[hash];
            while (cur->next != 0)
                cur = cur->next;
            cur->next = calloc (1, sizeof (HashTable));
            cur = cur->next;
            cur->word = calloc (str_len + 1, sizeof(char));
            memcpy(cur->word, temp_str, str_len);
        }
        len_trav += str_len;
    }
    free (temp_str);
    return buf;
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

int NumOfWord (HashTable** text, char* word)
{
    int N = 0;
    
    int word_hash = Hash (word);
    HashTable* cur_node = text[word_hash];
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

void DeleteList (HashTable* top)
{
    HashTable* cur_node = top;
    HashTable* next_node = top;
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


void End (HashTable** buf, char** words, int N)
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
    //Приём данных==========================================
    int N = 0;

    long long text_len = 0;
    HashTable** buf = 0;
    char** words = 0;
    scanf("%d", &N);
    scanf("%lld", &text_len);

    buf = TextInput (text_len);    
    words = WordsInput (N);
    //Приём данных окончен==================================
    for (int i = 0; i < N; i++)
        printf ("%d ", NumOfWord(buf, words[i]));
    End (buf, words, N);
    return 0;
}