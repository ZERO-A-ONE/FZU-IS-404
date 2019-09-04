import numpy as np
def AtoN(A):#处理字符和数字的关系
    N = 0
    if(ord(A)>=65 and ord(A)<=90):
        N = ord(A) - ord('A')
    if (ord(A) >= 97 and ord(A) <= 122):
        N = ord(A) - ord('A')
    return N
def NtoA(N):
    A = chr(N + ord('A'))
    return A
def Decrypt(clearlist,A,B,n):#解密函数
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
    M = np.ones((n,groups))
    index = 0
    for column in range(groups):
        for row in range(n):
            M[row][column] = clearlist[index]
            index = index + 1
    index = 0
    for A_column in range(n):
        for
def Encrypt(clearlist,A,B,n):#加密函数
    ReA = np.linalg.inv(A)
if __name__ == '__main__':
    Model = 0
    #clear = input("Your ClearText:)
    clear = "PLEASE SEND ME THE BOOK, MY CREDIT CARD NO IS SIX ONE TWO ONE THREE EIGHT SIX ZERO ONE SIX EIGHT FOUR NINE SEVEN ZERO TWO"
    clear = list(clear)
    #字符串初始化转换为纯字母序列
    for i in range(len(clear)):
        if clear[i] == ',':
            clear[i] = ' '
    while ' ' in clear:
        clear.remove(' ')
    Model = int(input("Model (1) is Decrypt,(2) is Encrypt:"))
    n = int(input("n:"))
    A = np.ones((n,n))
    B = np.ones((n,1))
    print("Initialize A")
    for row in range(n):
            A[row] = input().split(' ')
    for row in range(n):
        for column in range(n):
            A[row][column] = int(A[row][column])
    print(A)
    print("Initialize B")
    for row in range(n):
            B[row] = input().split(' ')
    for row in range(n):
        B[row] = int(B[row])
    print(B)
    if Model == 1 :
        Decrypt(clear,A,B,n)
    if Model == 2 :
        Encrypt(clear,A,B,n)

