import random
import numpy as np
def  result(txt,count):
    try:
        if len(txt) > 28:
            raise NameError
    except TypeError:
        pass
    txt = txt[count:] + txt[0:count]
    return txt
def createkey(key):
    Movetimes = [1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1]
    PC_1_LTABLE = [57, 49, 41, 33, 25, 17, 9,
             1, 58, 50, 42, 34, 26, 18,
             10, 2, 59, 51, 43, 35, 27,
             19, 11, 3, 60, 52, 44, 36]
    PC_1_RTABLE = [63, 55, 47, 39, 31, 23, 15,
             7, 62, 54, 46, 38, 30, 22,
             14, 6, 61, 53, 45, 37, 29,
             21, 13, 5, 28, 20, 12, 4]
    PC_2_TABLE = [14, 17, 11, 24, 1, 5,
                        3, 28, 15, 6, 21, 10,
                        23, 19, 12, 4, 26, 8,
                        16, 7, 27, 20, 13, 2,
                        41, 52, 31, 37, 47, 55,
                        30, 40, 51, 45, 33, 48,
                        44, 49, 39, 56, 34, 53,
                        46, 42, 50, 36, 29, 32]
    if len(key) != 64 :
        print("Your Key lenth is Error!")
        assert len(key) == 64#if no 64bit error
    else:
        L0 = ""
        R0 = ""
        for i in PC_1_LTABLE:
            L0 += key[i - 1]
        for i in PC_1_RTABLE:
            R0 += key[i - 1]
        assert len(L0) == 28 #if no 28bit error
        assert len(R0) == 28
        Sonkey = []
        for i in range(0, 16):
            L0 = result(L0, Movetimes[i])
            R0 = result(R0, Movetimes[i])
            mergedKey = L0 + R0
            tempkey = ""
            for j in PC_2_TABLE:
                tempkey += mergedKey[j - 1]
            assert len(tempkey) == 48
            print("Your NO.",i," Sonkey :",tempkey)
            Sonkey.append(tempkey)
        return Sonkey
def IP(ClearTxt):
    IPTABLE = [58, 50, 42, 34, 26, 18, 10, 2,
                 60, 52, 44, 36, 28, 20, 12, 4,
                 62, 54, 46, 38, 30, 22, 14, 6,
                 64, 56, 48, 40, 32, 24, 16, 8,
                 57, 49, 41, 33, 25, 17, 9, 1,
                 59, 51, 43, 35, 27, 19, 11, 3,
                 61, 53, 45, 37, 29, 21, 13, 5,
                 63, 55, 47, 39, 31, 23, 15, 7]
    if len(ClearTxt) != 64:
        print("Your key Text lenth is Error!")
        assert len(ClearTxt) == 64  # if no 64bit error
    else:
        ret = ""
        for i in IPTABLE:
            ret = ret + ClearTxt[i - 1]
        print("Source ClearText : ",ClearTxt)
        print("IP Replace : ",ret)
        return ret
def expend(Rn):
    ETABLE = [32, 1, 2, 3, 4, 5,
                4, 5, 6, 7, 8, 9,
                8, 9, 10, 11, 12, 13,
                12, 13, 14, 15, 16, 17,
                16, 17, 18, 19, 20, 21,
                20, 21, 22, 23, 24, 25,
                24, 25, 26, 27, 28, 29,
                28, 29, 30, 31, 32, 1]
    retRn = ""
    for i in ETABLE:
        retRn += Rn[i - 1]
    assert len(retRn) == 48
    return retRn
def S_sub(S_Input):
    STABLE = [(14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13),
                (15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9),
                (10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12),
                (7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14),
                (2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3),
                (12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13),
                (4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12),
                (13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11)]
    S_Input = bin(S_Input)[2:]
    while len(S_Input) < 48:
        S_Input = "0" + S_Input
    index = 0
    retstr = ""
    for Slist in STABLE:
        row = int(S_Input[index] + S_Input[index + 5], base=2)
        col = int(S_Input[index + 1:index + 5], base=2)
        ret_single = bin(Slist[row * 16 + col])[2:]
        while len(ret_single) < 4:
            ret_single = "0" + ret_single
        retstr += ret_single
        index += 6
    assert len(retstr) == 32
    return retstr
def P(Ln, S_sub_str, oldRn):
    PTABLE = [16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
                2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25]
    tmp = ""
    for i in PTABLE:
        tmp += S_sub_str[i - 1]
    LnNew = int(tmp, base=2) ^ int(Ln, base=2)
    LnNew = bin(LnNew)[2:]
    while len(LnNew) < 32:
        LnNew = "0" + LnNew
    assert len(LnNew) == 32
    (Ln, Rn) = (oldRn, LnNew)
    return (Ln, Rn)
def IP_inverse(L16, R16):
    IPINVERSETABLE = [40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
                         38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
                         36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
                         34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25]
    tmp = L16 + R16
    retstr = ""
    for i in IPINVERSETABLE:
        retstr += tmp[i - 1]
    assert len(retstr) == 64
    return retstr
def DES_ECB(ClearTxt,Keylist):
    InitKeyCode = IP(ClearTxt)
    Ln = InitKeyCode[0:32]
    Rn = InitKeyCode[32:]
    for key in Keylist:
        while len(Rn) < 32:
            Rn = "0" + Rn
        while len(Ln) < 32:
            Ln = "0" + Ln
        Rn_expand = expend(Rn)
        S_Input = int(Rn_expand, base=2) ^ int(key, base=2)
        S_sub_str = S_sub(S_Input)
        (Ln, Rn) = P(Ln, S_sub_str, Rn)
    (Ln, Rn) = (Rn, Ln)
    re_text = IP_inverse(Ln, Rn)
    return re_text
def DIYDES(ClearTxt,Key,Model):
    keylist = createkey(Key)

def Feistel(ClearTxt,Key,Model,F):
    #Step 1 is CreateKey
    keylist = createkey(Key)
    print()
    if Model == 1:
        keylist = keylist
    if Model == 2:
        keylist = keylist[::-1] #INVERSEKEY
    #Step 2 is ClearTxt
    text = F(ClearTxt,keylist)
    return  text
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
def inkey():
    model = input("Random Kry (y/n): ")
    strr = ""
    if model == "y":
        tmplist = []
        for i in range(8):
            j = random.randint(1,3)
            if j == 1:
                tmplist.append(chr(random.randint(48, 57)))
            if j == 2:
                tmplist.append(chr(random.randint(65, 90)))
            if j == 3:
                tmplist.append(chr(random.randint(97, 122)))
        for i in tmplist:
            strr += i
        keylist = encode(strr)
        # 补充奇偶校验位
        for i in range(len(keylist)):
            keylist[i] = ParityCheck(keylist[i])
        key_bin = ''.join(keylist)
        print("Your Key: ", strr)
        print("Your Binary Key: ", key_bin)
        print("Your Hex Key: ", hex(int(key_bin, base=2)).upper())
        return key_bin
    if model == "n":
        flag = int(input("Please choose your key (1)hex (2)binary (3)string: "))
        if flag == 3:
            key = input("Please input your string(len = 8): ")
            strr = key
            keylist = encode(strr)
            # 补充奇偶校验位
            for i in range(len(keylist)):
                keylist[i] = ParityCheck(keylist[i])
            key_bin = ''.join(keylist)
            print("Your Key: ", key)
            print("Your Binary Key: ", key_bin)
            print("Your Hex Key: ", hex(int(key_bin, base=2)).upper())
            return key_bin
        if flag == 1:
            strr = input("Please input your Hex : ")
            hexx = bin(int(strr, 16))
            strlist = list(hexx)
            for i in range(2):
                del strlist[0]
            while len(strlist) != 64:
                strlist.insert(0,"0")
            key_bin = ''.join(strlist)
            print("Your Binary Key: ", key_bin)
            print("Your Hex Key: ", hex(int(key_bin, base=2)).upper())
            return key_bin
        if flag == 2:
            strr = input("Please input your binary : ")
            key_bin = strr
            print("Your Binary Key: ", key_bin)
            print("Your Hex Key: ", hex(int(key_bin, base=2)).upper())
            return key_bin
def Encryptmohex(tmplist):
    str_bin = ''.join(tmplist)
    groups = int(len(str_bin) / 64)
    # 生成加密分组
    M = np.zeros((groups, 64))
    index = -8
    for i in range(groups):
        index += 8
        strr = ""
        for j in range(8):
            strr += tmplist[index + j]
        for j in range(64):
            M[i][j] = int(strr[j])
    print("Your List Clear Text: ", tmplist)
    print("Your Binary Clear Text: ", str_bin)
    print("Your Hex Clear Text: ", hex(int(str_bin, base=2)).upper())
    print("Your Clear Text groups: ", groups)
    key_bin = inkey()
    # 打印加密群
    AllCiphertext = ""
    for i in range(groups):
        print("ClearText Group ", i, ": ", end='')
        tmptext = ""
        for j in range(64):
            tmptext += str(int(M[i][j]))
        ciphertext = Feistel(tmptext, key_bin, 1,DES_ECB)
        AllCiphertext += ciphertext
        print("Ciphertext: ", ciphertext)
    print("Your Binary Ciphertext: ", AllCiphertext)
    print("Your Hex Ciphertext: ", hex(int(AllCiphertext, base=2)).upper())
def Encryptmostr(text):
    lenth = len(text)
    flag = 0
    offset = 0
    # 补位操作
    if (lenth % 8 == 0):
        flag = 0
    else:
        flag = 1
        offset = 8 - lenth % 8
    for i in range(offset):
        text += 'A'
    tmplist = encode(text)
    groups = int(len(tmplist) / 8)
    #对齐8位
    for i in range(len(tmplist)):
        if len(tmplist[i]) != 8:
            tmpp = ""
            for j in range(8 - len(tmplist[i])):
                tmpp += '0'
            tmplist[i] = tmpp + tmplist[i]
    str_bin = ''.join(tmplist)
    #生成加密分组
    M = np.zeros((groups, 64))
    index = -8
    for i in range(groups):
        index += 8
        strr = ""
        for j in range(8):
            for k in tmplist[index+j]:
                strr += k
        for j in range(64):
            M[i][j] = int(strr[j])
    print("Your List Clear Text: ",tmplist)
    print("Your Binary Clear Text: ",str_bin)
    print("Your Hex Clear Text: ", hex(int(str_bin, base=2)).upper())
    print("Your Clear Text offset: ", offset)
    print("Your Clear Text groups: ", groups)
    key_bin = inkey()
    #打印加密群
    AllCiphertext = ""
    for i in range(groups):
        print("ClearText Group ", i)
        tmptext = ""
        for j in range(64):
            tmptext += str(int(M[i][j]))
        ciphertext = Feistel(tmptext, key_bin, 1,DES_ECB)
        AllCiphertext += ciphertext
        print("Ciphertext: ",ciphertext)
    print("Your Binary Ciphertext: ",AllCiphertext)
    print("Your Hex Ciphertext: ", hex(int(AllCiphertext, base=2)).upper())
if __name__ == '__main__':
    model = 0
    flag = int(input("Please choose Encrypt or Decrypt (1)Encrypt (2)Decrypt :"))
    if flag == 1:
        model = int(input("Please choose your Model of Text (1)Hex (2)String :"))
    if flag == 2:
        model = int(input("Please choose your Model of Text (1)Hex (2)Binary :"))
    if flag == 1:
        if model == 1:
            strr = input("Please input your Hex (0x) :")
            hexx = bin(int(strr, 16))
            strlist = list(hexx)
            for i in range(2):
                del strlist[0]
            while len(strlist) != 64:
                strlist.insert(0, '0')
            groups = int(len(strlist) / 8)
            tmplist = []
            index = -8
            for i in range(groups):
                index += 8
                tlist = ""
                for j in range(8):
                    tlist += strlist[index + j]
                tmplist.append(tlist)
            Encryptmohex(tmplist)
        if model == 2:
            strr = input("Please input your String : ")
            # 消除空格
            strr = list(strr)
            while ' ' in strr:
                strr.remove(' ')
            str1 = ""
            for i in strr:
                str1 += i
            Encryptmostr(str1)
    if flag == 2:
        if model == 1:
            strr = input("Please input your ClearMessage Hex : ")
            hexx = bin(int(strr, 16))
            strlist = list(hexx)
            for i in range(2):
                del strlist[0]
            while len(strlist) != 64:
                strlist.insert(0, '0')
            groups = int(len(strlist) / 8)
            tmplist = []
            index = -8
            for i in range(groups):
                index += 8
                tlist = ""
                for j in range(8):
                    tlist += strlist[index + j]
                tmplist.append(tlist)
            str_bin = ''.join(tmplist)
            key = input("Please input your key(Hex) : ")
            hexx = bin(int(key, 16))
            strlist = list(hexx)
            for i in range(2):
                del strlist[0]
            while len(strlist) != 64:
                strlist.insert(0,"0")
            key_bin = ''.join(strlist)
            print("Your Binary Clear Text : ",str_bin)
            print("Your Binary Key : ",key_bin)
            txt = Feistel(str_bin, key_bin, 2)
            print("Your Binary Decode Message : ",txt)
            print("Your Hex Decode Message : ",  hex(int(txt, base=2)).upper())
        if model == 2:
            strr = input("Please input your Binary Clear Text : ")
            key = input("Please input your Binary key : ")
            txt = Feistel(strr, key, 2)
            print("Your Binary Decode Message : ", txt)
            print("Your Hex Decode Message : ", hex(int(txt, base=2)).upper())