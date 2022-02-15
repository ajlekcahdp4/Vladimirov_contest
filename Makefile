CC = gcc
CFLAGS = -Wall -Werror -Wextra
all:
hl2:
	$(CC) $(CFLAGS) -g hl2.c list/list.c -o hl2.out
clean:
	rm -rf *.out