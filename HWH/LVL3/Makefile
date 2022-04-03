CC = gcc
CFLAGS = -Wall -Wextra -Werror -Walloc-zero -Walloca -Walloca-larger-than=8192 -Warray-bounds -Wcast-align -Wcast-qual		\
-Wchar-subscripts -Wconversion -Wdangling-else -Wduplicated-branches -Wempty-body -Wfloat-equal -Wformat-nonliteral			\
-Wformat-security -Wformat-signedness -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Winline -Wlarger-than=8192		\
-Wvla-larger-than=8192 -Wlogical-op -Wmissing-declarations -Wopenmp-simd -Wpacked -Wpointer-arith 							\
-Wrestrict -Wshadow -Wstack-usage=8192 -Wstrict-overflow=2 -Wstringop-overflow=4 -Wsuggest-attribute=noreturn				\
-Wsuggest-final-types -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wvariadic-macros 		\
-Wno-missing-field-initializers -Wnarrowing -Wvarargs -fcheck-new -fstack-check -fstrict-overflow -flto-odr-type-merging

OPTIMISATION = -O2
all: HWH
HWH: main HT dump_
	$(CC) $(CFLAGS) $(OPTIMISATION) -g main.o hashtable.o dump.o -o HWH.out
main:
	$(CC) $(CFLAGS) $(OPTIMISATION) -g -c main.c
HT:
	$(CC) $(CFLAGS) $(OPTIMISATION) -g -c hashtable/hashtable.c
dump_:
	$(CC) $(CFLAGS) $(OPTIMISATION) -g -c dump/dump.c
TestGen:
	python3 tests/TestGen.py
clean:
	rm -rf *.o *.out *.png