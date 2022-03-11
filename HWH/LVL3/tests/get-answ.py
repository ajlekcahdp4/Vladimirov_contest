#===========================================================================
#=================================main()====================================
#===========================================================================
file = open ("tests/dat/" + input(), "r")

N = int(file.readline())

text = []
words = []
passed_words = []
cnt = 0

for i in range (0, N):
    text.append(file.readline().strip())

for i in range (0, N):
    for j in range (0, N):
        if i != j:
            words.append(text[i] + text[j])

for i in range (0, N):
    count_of_word = words.count (words[i])
    if passed_words.count(words[i]) == 0 and count_of_word > 1:
        #print ("string = <%s>, count = %s\n" %(words[i], words.count (words[i])))
        cnt += count_of_word
        passed_words.append (words[i])
print (str(cnt))
