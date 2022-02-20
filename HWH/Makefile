CC = gcc
CFLAGS = -Wall -Werror -Wextra
all: HWH
HWH: main HT
	$(CC) $(CFLAGS) -g main.o hashtable.o -o HWH.out
main:
	$(CC) $(CFLAGS) -g -c main.c
HT:
	$(CC) $(CFLAGS) -g -c hashtable/hashtable.c
clean:
	rm -rf *.o *.out