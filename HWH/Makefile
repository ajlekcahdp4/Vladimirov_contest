CC = gcc
CFLAGS = -Wall -Werror -Wextra
all: HWH
HWH: main HT dump_
	$(CC) $(CFLAGS) -g main.o hashtable.o dump.o -o HWH.out
main:
	$(CC) $(CFLAGS) -g -c main.c
HT:
	$(CC) $(CFLAGS) -g -c hashtable/hashtable.c
dump_:
	$(CC) $(CFLAGS) -g -c dump/dump.c
clean:
	rm -rf *.o *.out