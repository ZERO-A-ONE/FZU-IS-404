import numpy as np
def AtoN(A):#处理字符和数字的关系
    N = 0
    if(ord(A)>=65 and ord(A)<=90):
        N = ord(A) - ord('A')
    if (ord(A) >= 97 and ord(A) <= 122):
        N = ord(A) - ord('a')
    return N
def NtoA(N):
    A = chr(N + ord('A'))
    return A
def Encrypt(clearlist,A,B,n,N):#加密函数
    CipherText = []
    lenth = len(clearlist)
    flag = 0
    offset = 0
    #补位操作
    if(lenth%n == 0):
        flag = 0
    else:
        flag = 1
        offset = n-lenth%n
    for i in range(offset):
        clearlist.append('A')
    groups = int(len(clearlist)/n)
    for i in range(len(clearlist)):
        clearlist[i] = AtoN(clearlist[i])
    #生成M序列
    M = np.ones((groups,n))
    index = 0
    for row in range(groups):
        for column in range(n):
            M[row][column] = clearlist[index]
            index = index + 1
    for i in range(groups):#实现矩阵乘法和矩阵加法，A*M+Bmod(N)
        tmp = np.zeros((n, 1))
        tmpp = np.zeros((n, 1))
        for row in range(n):#初始化Mi
            tmp[row][0] = M[i][row]
        for row in range(n):#实现A*M
            for column in range(n):
                tmpp[row][0] = int(tmpp[row][0] + (int(tmp[column][0]) * int(A[row][column])))
            tmpp[row][0] = int((tmpp[row][0]) % N)
        for row in range(n):#实现+
            tmpp[row][0] = tmpp[row][0] + B[row][0]
        for row in range(n):
            CipherText.append(NtoA(int(tmpp[row][0])))
    if flag == 1:
        for i in range(offset):#消除补位影响
            del CipherText[-1]
    index = 0
    print("CipherText is:", end="")
    for i in range(len(CipherText)):
        if index == n:
            print(" ",end="")
            index = 0
        print(CipherText[i],end="")
        index = index + 1
def Decrypt(CipherText,A,B,n,N,model):#解密函数
    clearlist = []
    lenth = len(CipherText)
    flag = 0
    offset = 0
    # 补位操作
    if (lenth % n == 0):
        flag = 0
    else:
        flag = 1
        offset = n - lenth % n
    for i in range(offset):
        CipherText.append('A')
    groups = int(len(CipherText) / n)
    for i in range(len(CipherText)):
        CipherText[i] = AtoN(CipherText[i])
    # 生成M序列
    M = np.zeros((groups, n))
    index = 0
    for row in range(groups):
        for column in range(n):
            M[row][column] = CipherText[index]
            index = index + 1
    if model == 'y':
        A = A
    if model == 'n':
        A = np.linalg.inv(A)
    #求C-B
    for i in range(groups):#实现矩阵乘法和矩阵加法，InA*(C-B)
        tmp = np.zeros((n, 1))
        tmpp = np.zeros((n, 1))
        for row in range(n):#初始化Mi
            tmp[row][0] = M[i][row]
        for row in range(n):  # 实现C-B
            tmp[row][0] = tmp[row][0] - B[row][0]
        for row in range(n):#实现InA*(C-B)mod(N)
            for column in range(n):
                tmpp[row][0] = int(tmpp[row][0] + (int(tmp[column][0]) * int(A[row][column])))
            tmpp[row][0] = int((tmpp[row][0]) % N)
        for row in range(n):
            clearlist.append(NtoA(int(tmpp[row][0])))
    if flag == 1:
        for i in range(offset):#消除补位影响
            del clearlist[-1]
    index = 0
    print("clearlist is:", end="")
    for i in range(len(clearlist)):
        if index == n:
            print(" ",end="")
            index = 0
        print(clearlist[i],end="")
        index = index + 1
if __name__ == '__main__':
    Model = 0
    clear = input("Your Text:")
    flag = ' '
    #clear = "WGI FGJ TMR LHH XTH WBX ZPS BRB"
    #clear = "YOUR PIN NO IS FOUR ONE TWO SIX"
    #clear = "PLEASE SEND ME THE BOOK, MY CREDIT CARD NO IS SIX ONE TWO ONE THREE EIGHT SIX ZERO ONE SIX EIGHT FOUR NINE SEVEN ZERO TWO"
    clear = list(clear)
    #字符串初始化转换为纯字母序列
    for i in range(len(clear)):
        if clear[i] == ',':
            clear[i] = ' '
    while ' ' in clear:
        clear.remove(' ')
    Model = int(input("Model (1) is Decrypt,(2) is Encrypt:"))
    n = int(input("n:"))
    N = int(input("N:"))
    A = np.zeros((n,n))
    B = np.zeros((n,1))
    #Initialize A
    if Model == 2:
        print("Please input A")
        for row in range(n):
            A[row] = input().split(' ')
        for row in range(n):
            for column in range(n):
                A[row][column] = int(A[row][column])
    if Model == 1:
        flag = input("Do you have the inverse matrix (y/n):")
        if flag == 'y':
            print("Please input inverse matrix")
            for row in range(n):
                A[row] = input().split(' ')
            for row in range(n):
                for column in range(n):
                    A[row][column] = int(A[row][column])
        if flag == 'n':
            print("Please input A")
            for row in range(n):
                A[row] = input().split(' ')
            for row in range(n):
                for column in range(n):
                    A[row][column] = int(A[row][column])
    #Initialize B
    print("Please input B")
    for row in range(n):
            B[row] = input().split(' ')
    for row in range(n):
        B[row] = int(B[row])
    if Model == 1 :
        Decrypt(clear,A,B,n,N,flag)
    if Model == 2 :
        Encrypt(clear,A,B,n,N)

