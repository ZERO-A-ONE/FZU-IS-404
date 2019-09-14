import random
def testinput(n):
    var = 0
def encode(s):#字符串转二进制
    tmp = []
    for c in s:
        tmp.append(bin(ord(c)).replace('0b', ''))
    str_bin = ' '.join(tmp)
    for i in range(len(tmp)):
        if len(tmp[i]) != 7:
            tmpp = ""
            for j in range(7-len(tmp[i])):
                tmpp += '0'
            tmp[i] =  tmpp + tmp[i]
    return tmp
def decode(s):
    bin_str = ''.join([chr(i) for i in [int(b, 2) for b in s.split(' ')]])
    tmp = list(bin_str.split(' '))
    return tmp
def inkey():
    model = input("Random (y/n): ")
    strr = ""
    if model == "y":
        tmplist = []
        for i in range(8):
            tmplist.append(chr(random.randint(33,125)))
        for i in tmplist:
            strr += i
    if model == "n":
        key = input("Please input your key(len = 8): ")
        strr = key
    print(strr)
    print(encode(strr))
    return strr
print(encode('0'))
while 1:
    inkey()