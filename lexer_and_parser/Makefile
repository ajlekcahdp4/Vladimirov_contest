CC = gcc
CFLAGS = -Wall -Wextra -Werror -Walloc-zero -Walloca -Walloca-larger-than=8192 -Warray-bounds -Wcast-align -Wcast-qual		\
-Wchar-subscripts -Wconversion -Wdangling-else -Wduplicated-branches -Wempty-body -Wfloat-equal -Wformat-nonliteral			\
-Wformat-security -Wformat-signedness -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Winline -Wlarger-than=8192		\
-Wvla-larger-than=8192 -Wlogical-op -Wmissing-declarations -Wopenmp-simd -Wpacked -Wpointer-arith -Wredundant-decls			\
-Wrestrict -Wshadow -Wstack-usage=8192 -Wstrict-overflow=2 -Wstringop-overflow=4 -Wsuggest-attribute=noreturn				\
-Wsuggest-final-types -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wvariadic-macros 		\
-Wno-missing-field-initializers -Wnarrowing -Wvarargs -fcheck-new -fstack-check -fstrict-overflow -flto-odr-type-merging


PARSER = bu_parser

all:
LX:
	$(CC) -g $(CFLAGS) LX.c -o LX.out
ST: tree_dump
	$(CC) -g $(CFLAGS) ST.c dump_tree.o -o ST.out
main:
	$(CC) -g -c $(CFLAGS) main.c
lex:
	$(CC) -g -c $(CFLAGS) lexer/lexer.c
parse:
	$(CC) -g -c $(CFLAGS) parser/$(PARSER).c
tree_dump:
	$(CC) -g -c $(CFLAGS) dump_tree/dump_tree.c

LexParse: main lex parse tree_dump
	$(CC) -g $(CFLAGS) main.o lexer.o $(PARSER).o dump_tree.o -o LexParse.out
clean:
	rm -rf *.o *.out *.txt vgcore.* *.dot *.png
