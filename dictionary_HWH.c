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
        hash += str[i];
    hash = hash % 1000;
    return hash;
}

HashTable** TextInput (long long text_len)
{
    HashTable** buf = calloc(999, sizeof(HashTable*));
    char* temp_str = calloc (text_len + 1, sizeof(char));


    int str_len = 0;
    for (int len_trav = 0; len_trav < text_len; len_trav++)
    {
        scanf("%s", temp_str);
        str_len = strlen (temp_str);

        int hash = Hash (temp_str);
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
    scanf("%d", &words_len);
    char** words = calloc (N, sizeof(char*));
    for (int i = 0; i < N; i++)
    {
        words[i] = calloc (words_len, sizeof(char));
        scanf("%s", words[i]);
    }
    return words;
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
    scanf("%d", &N);

    long long text_len = 0;
    scanf("%lld", &text_len);

    HashTable** buf = TextInput (text_len);    
    char** words = WordsInput (N);
    //Приём данных окончен==================================


    //final=================================================
    End (buf, words, N);

    return 0;
}