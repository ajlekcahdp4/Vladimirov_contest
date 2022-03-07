CC = gcc
CFLAGS = -Wall -Wextra -Werror -Walloc-zero -Walloca -Walloca-larger-than=8192 -Warray-bounds -Wcast-align -Wcast-qual		\
-Wchar-subscripts -Wconversion -Wdangling-else -Wduplicated-branches -Wempty-body -Wfloat-equal -Wformat-nonliteral			\
-Wformat-security -Wformat-signedness -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Winline -Wlarger-than=8192		\
-Wvla-larger-than=8192 -Wlogical-op -Wmissing-declarations -Wopenmp-simd -Wpacked -Wpointer-arith -Wredundant-decls			\
-Wrestrict -Wshadow -Wstack-usage=8192 -Wstrict-overflow=2 -Wstringop-overflow=4 -Wsuggest-attribute=noreturn				\
-Wsuggest-final-types -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wvariadic-macros 		\
-Wno-missing-field-initializers -Wnarrowing -Wvarargs -fcheck-new -fstack-check -fstrict-overflow -flto-odr-type-merging 	\
-fchkp-first-field-has-own-bounds -fchkp-narrow-to-innermost-array 
all:
EX:
	$(CC) $(CFLAGS) EX.c -o EX.out
D_no_pivot:
	$(CC) $(CFLAGS) -g D_no_pivot.c -o D_no_pivot.out -lm
DT:
	$(CC) $(CFLAGS) -g DT.c -lm -o DT.out
RP:
	$(CC) $(CFLAGS) RP.c -o rp.out -lm
clean:
	rm -rf *.o *.out *.txt