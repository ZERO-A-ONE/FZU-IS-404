def ParityCheck(s):#偶校验
    num = 0
    for i in s:
        if i == '1':
            num = num +1
    if num%2 == 0:
        s += '0'
    else:
        s += '1'
    return s
def hexx(s):#消除校验位
    index = 0
    tmp = 0
    for i in range(len(s)):
        index = i % 8
        if index == 0 and i !=0:
            print(tmp)
            print(chr(tmp))
            tmp = 0
        else:
            tmp += int(s[i])
while 1:
    s = input()
    hexx(s)
