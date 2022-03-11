#===========================================================================
#=================================main()====================================
#===========================================================================
test_file_name = input ()
file = open ("tests/dat/" + test_file_name, "r")
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

#---------------------------------------------------------------------------------
output_file = open ("tests/ans/" + test_file_name[:len(test_file_name) - 4] + ".ans", "w")
output_file.write (str(cnt))
output_file.close()
