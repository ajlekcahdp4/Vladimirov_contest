import random as rand

src = open ("tests/test.src", "r")
src2 = open ("tests/test2.src", "r")
dest = open ("tests/4.dat", "w")

N = int(src.readline())
N = 10
strings = []
text = []
src2_buf = []

for i in range (0, N):
    strings.append((src.readline()).strip())
for i in range (0, N):
    src2_buf.append((src2.readline()).strip())

src.close()
for i in range (0, N):
    str_len = len (strings[i])
    l1 = rand.randint (3, str_len - 2)
    text.append (strings[i][l1:str_len])
    text.append (strings[i][:l1])
    
    l2 = l1

    while (l2 == l1):
        l2 = rand.randint (3, str_len - 2)
    text.append (strings[i][l2:str_len])
    text.append (strings[i][:l2])
    i += 1



N1 = rand.randint (3, N)
print (str(2*N1))
dest.write (str(2 * N1) + '\n')

for i in range (0, N1):
    dest.write (text[i] + '\n')
    l = rand.randint (N1 // 2, len(src2_buf) - 1)
    dest.write (src2_buf[l] + '\n')


dest.close()
src2.close()