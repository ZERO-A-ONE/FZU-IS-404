A=0x01234567
B=0x89abcdef
C=0xfedcba98
D=0x76543210
def Datafill(text):
    if len(text) == 448:
        for i in range(512):
            if i == 0:
                text += "1"
            else:
                text += "0"
    else:
        tmp = 1
        while len(text) % 512 != 448:
            if tmp == 1:
                text += "1"
                tmp = 0
            else:
                text += "0"
    return text
def chrtobin(ch):
    bi = bin(ord(ch))
    bi = bi[2:len(bi)]
    while len(bi) != 8:
        bi += "0"
    return bi
def strtobin(strr):
    linstr = ""
    for ch in strr:
        linstr += chrtobin(ch)
    return linstr
def addmeslen(lenth):
    lenth = bin(lenth)
    lenth = lenth[2:len(lenth)]
    if len(lenth) <= 64:
        tmplin = ""
        tmpplin = ""
        for i in range(64 - (len(lenth) % 64)):
            tmpplin += "0"
        tmpplin += lenth
        index = len(tmpplin) - 1
        while 1:
            tmplin += tmpplin[index]
            index = index - 1
            if index < 0:
                break
        return tmplin
    else:
        tmppstr = lenth[len(lenth) - 63:len(lenth) - 1]#取低64位
        tmpstr = ""
        index = len(tmppstr) - 1
        while 1:
            tmpstr += tmppstr[index]
            index = index - 1
            if index < 0:
                break
        return  tmpstr
def FiveGroup(text):#数据按每个512位为一组进行分组
    endtable = []
    groupnum = int(len(text) / 512)
    for i in range(groupnum):
        start = 0
        end = 512
        for i in range(groupnum):
            endtable.append(text[start:end])
            start = start + 512
            end = end + 512
    return  endtable
def SixGroup(table):#每组里面分成16个32位，也就是16个long
    fintable = []
    Sixtable = []
    for i in range(len(table)):
        tmpstr = table[i]
        tmppstr = ""
        start = 0
        end = 32
        for i in range(16):
            tmppstr = tmpstr[start:end]
            start = start + 16
            end = end + 16
            Sixtable.append(tmppstr)
        fintable.append(Sixtable)
        Sixtable = []
    return fintable
if __name__ == '__main__':
    text = input()
    text = strtobin(text)
    solen = len(text)
    text = Datafill(text)
    mfg = addmeslen(solen)
    sostr = text + mfg
    table = FiveGroup(sostr)
    table = SixGroup(table)
