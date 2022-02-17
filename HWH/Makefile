CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
all: HWH
HWH: main HT
	$(CC) $(CFLAGS) main.o hashtable.o -o HWH.out
main:
	$(CC) $(CFLAGS) -c main.c
HT:
	$(CC) $(CFLAGS) -c hashtable/hashtable.c
clean:
	rm -rf *.o *.out