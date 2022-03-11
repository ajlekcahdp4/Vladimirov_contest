import hashlib
#hash_ = hashlib.md5(b"hui")
#dict = {hash_.hexdigest():  "hui"}
#print(dict[hash_.hexdigest()])

src = open ("tests/1.dat", "r")

N = int(src.readline())

dict = {}
for i in range (0, N):
    string = (src.readline()).strip()
    print(string + '\n')
    hash_ = hashlib.md5(string.encode()).hexdigest()
    dict[hash_] = string
print(dict.items())


