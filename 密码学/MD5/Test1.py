a = "11000110110010001100101011001100"
tmp = 31
tmpnum = 0
for i in a:
    tmpnum = tmpnum + (ord(i)-ord('0'))*pow(2,tmp)
    tmp = tmp - 1
    if tmp < 0:
        break
print(tmpnum)


def strtonum(strr):
    tmp = 31
    tmpnum = 0
    for i in strr:
        tmpnum = tmpnum + (ord(i) - ord('0')) * pow(2, tmp)
        tmp = tmp - 1
        if tmp < 0:
            break
    return  tmpnum