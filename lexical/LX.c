#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

enum lexem_kind_t { OP, BRACE, NUM };
enum operation_t { ADD, SUB, MUL, DIV };
enum braces_t { LBRAC, RBRAC };

struct lexem_t {
    enum lexem_kind_t kind;
    union {
        enum operation_t op;
        enum braces_t b;
        int num;
    } lex;
};

struct lex_array_t {
    struct lexem_t *lexems;
    int size;
    int capacity;
};

char *Input (char *filename)
{
    FILE *f = fopen (filename, "r");

    struct stat stat_buf;
    stat(filename, &stat_buf);
    size_t char_num = stat_buf.st_size;

    char *buf = calloc (char_num, sizeof (char));
    fread (buf, sizeof(char), char_num, f);
    printf ("%s\n", buf);

    fclose (f);

    return buf;
}

void End (char *buf)
{
    free (buf);
}


struct lex_array_t *lex_string (const char *str)
{

}

int main (int argc, char **argv)
{
    char *buf = Input (argv[argc - 1]);

    

    End (buf);
    return 0;
}