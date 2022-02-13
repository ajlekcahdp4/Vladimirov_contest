CC = gcc
CFLAGS = -Wall -Werror -Wextra
all:
hl2:
	$(CC) $(CFLAGS) hl2.c -o hl2.out
HWH:
	$(CC) $(CFLAGS) dictionary_HWH.c -o HWH.out
clean:
	rm -rf *.out