CC = gcc
CFLAGS = -Wall -Wextra -Werror -Walloc-zero -Walloca -Walloca-larger-than=8192 -Warray-bounds -Wcast-align -Wcast-qual		\
-Wchar-subscripts -Wconversion -Wdangling-else -Wduplicated-branches -Wempty-body -Wfloat-equal -Wformat-nonliteral		\
-Wformat-security -Wformat-signedness -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Winline -Wlarger-than=8192		\
-Wvla-larger-than=8192 -Wlogical-op -Wmissing-declarations -Wopenmp-simd -Wpacked -Wpointer-arith 				\
-Wrestrict -Wshadow -Wstack-usage=8192 -Wstrict-overflow=2 -Wstringop-overflow=4 -Wsuggest-attribute=noreturn			\
-Wsuggest-final-types -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wvariadic-macros 		\
-Wno-missing-field-initializers -Wnarrowing -Wvarargs

OPTIMISATION = -O3
DEBUG = -g


all: HWH
HWH: MAIN_T HT_T DUMP_T
	$(CC) $(CFLAGS) $(OPTIMISATION) $(DEBUG) main.o hashtable.o dump.o -o HWH.out
MAIN_T:
	$(CC) $(CFLAGS) $(OPTIMISATION) $(DEBUG) -c main.c
HT_T:
	$(CC) $(CFLAGS) $(OPTIMISATION) $(DEBUG) -c hashtable/hashtable.c
DUMP_T:
	$(CC) $(CFLAGS) $(OPTIMISATION) $(DEBUG) -c dump/dump.c
TestGen:
	python3 tests/TestGen.py
clean:
	rm -rf *.o *.out *.png *.dot *.dis *.x vgcore.*
