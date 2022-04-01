CC = gcc
CFAGS = -Wall -Werror -Wextra
DEBUG = -g


all: AS_T


AS_T: MAIN_T LEXER_T PARSER_T
	$(CC) $(DEBUG) AS.o lexer.o parser.o -o AS.out

AS2_T:
	$(CC) $(DEBUG) $(CFLAGS) AS2.c -o AS2.out

MAIN_T:
	$(CC) -c $(DEBUG) $(CFLAGS) AS.c

LEXER_T:
	$(CC) -c $(DEBUG) $(CFLAGS) lexer.c
PARSER_T:
	$(CC) -c $(DEBUG) $(CFLAGS) parser.c

