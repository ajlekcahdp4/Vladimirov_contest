#ifndef LEXER_INCLUDED
#define LEXER_INCLUDED
enum reg_t {  A = 0, B, C, D, RLAST };

enum opcode_t { MOVI = 0, ADD = 8, SUB = 9, MUL = 10, DIV = 11, IN, OUT };

enum lexem_kind { CMD, REG, VAL };

struct lexem_t 
{
    union 
    {
        enum opcode_t CMD;
        enum reg_t REG;
        int val;
    }lex;
    enum lexem_kind kind;
};

struct lex_array_t 
{
    struct lexem_t *lexarr;
    size_t capacity;
    size_t size;
};

size_t Input (char **buf);
struct lex_array_t *lex_string (const char *buf);




#endif