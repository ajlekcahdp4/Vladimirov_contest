import random as rand

def FileToBuf (filename, buf):
    file = open (filename, "r")
    N = int(file.readline())

    for i in range (0, N):
        buf.append((file.readline()).strip())

    file.close()
    return N

def CrushingWords (buf, N):
    text = []
    for i in range (0, N):
        str_len = len (buf[i])
        l1 = rand.randint (3, str_len - 2)
        text.append (buf[i][l1:str_len])
        text.append (buf[i][:l1])
        
        l2 = l1
        while (l2 == l1):
            l2 = rand.randint (3, str_len - 2)
        text.append (buf[i][l2:str_len])
        text.append (buf[i][:l2])
    return text

def GenerateTest (words, N1, text2, N2):
    test = []
    words_index_list = []

    test_len = rand.randint (3, N2)
    answ = rand.randint (3, 100)

    print ("test_len = " + str(test_len + 4*answ))
    print ("answ = %s"%(answ))
    test.append (str(answ * 4 + test_len))
    #insert fours
    for cnt in range(answ):
        i = 1
        while (i % 4 != 0 or words_index_list.count(i) > 0):
            i = rand.randint (0, N1 - 4)
        words_index_list.append (i)
        test.append (words[i])
        test.append (words[i + 1])
        test.append (words[i + 2])
        test.append (words[i + 3])
    #insert other words
    words_index_list = []
    for i in range (0, test_len):
        index = 0
        while (words_index_list.count(index) > 0):
            index = rand.randint (0, N2 - 1)
        words_index_list.append (index)
        test.append (text2[index])


    return test
    
#=================================================================
#===============================MAIN==============================
#=================================================================

first_text = []
second_text = []

N1 = FileToBuf ("tests/src/1.src", first_text)
N2 = FileToBuf ("tests/src/3.src", second_text)

test_file = open ("tests/dat/6.dat", "w")

#---------------------------get_text------------------------------
words = CrushingWords (first_text, N1)
test = GenerateTest (words, N1 * 4, second_text, N2)
#---------------------------write text----------------------------
test_len = len (test)
for i in range (0, test_len):
    test_file.write (test[i] + '\n')
#-----------------------------------------------------------------
test_file.close()