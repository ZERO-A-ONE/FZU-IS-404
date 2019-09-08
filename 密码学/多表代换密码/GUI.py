import random
import time
import sys
import tkinter as tk
import numpy as np
from tkinter.simpledialog import *
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
def Decrypt():#解密函数
    var = 0
def Encrypt():#加密函数
    var = 0
def getIdentityMatrix(n):#生成单位矩阵
    A = np.zeros((n,n))
    for i in range(n):
        for j in range(n):
            if i == j:
                A[i][j] = 1
            else:
                A[i][j] = 0
    return A
def getInvertibleMatrix(n):#生成可逆矩阵
    A = getIdentityMatrix(n)
    tempArray = np.zeros(n)
    B = np.zeros((n,n))
    transformTime = int(random.randint(0,1000))
    maxint = sys.maxsize
    for i in range(transformTime):
        mainRowNum = int((random.randint(0,n) % (n - 1)))#选择一个主行作初等行变换
        for k in range(n):
            #元素数值是否会溢出
            if maxint - (A[mainRowNum][k])*(int(random.randint(0,10))) < 0 and maxint*(-1) - (A[mainRowNum][k])*(int(random.randint(0,10))) > tempArray[k]:
                tempArray[k] = A[mainRowNum][k]
            else:
                tempArray[k] = (A[mainRowNum][k]*(int(random.randint(0,10))))%26
        for j in range(n):
            if mainRowNum != j:
                for k in range(n):
                    if maxint - A[j][k]< tempArray[k] and maxint * (-1) - (A[j][k]) > tempArray[k]:
                        A[j][k] = (A[j][k]/4)%26
                    else:
                        A[j][k] = (A[j][k] + tempArray[k])%26
    return A
def nnb():
    var = 0
def newwind(n):
    winNew = Toplevel(window)
    winNew.geometry('320x400')
    winNew.title('Random Key')
    lb1 = tk.Label(winNew, text='Random A Key', font=('Arial', 16), width=40, height=2)
    lb1.pack(fill='x')
    nt1 = tk.Text(winNew, height=8, width=40)
    nt1.pack(fill='x')
    lb2 = tk.Label(winNew, text='Random B Key', font=('Arial', 16), width=40, height=2)
    lb2.pack(fill='x')
    nt2 = tk.Text(winNew, height=8, width=40)
    nt2.pack(fill='x')
    lb3 = tk.Label(winNew, text='@FZU-IS-404 ZERO-A-ONE', font=('Arial', 10), width=40, height=2)
    lb3.pack(fill='x')
    nb = tk.Button(winNew, text='Save as file', font=('Arial', 12), width=10, height=1, command=nnb())
    nb.pack()

    B = np.zeros((n, 1))
    A = getInvertibleMatrix(n)
    for row in range(n):
        B[row] = int(random.randint(0, 26))
    for row in range(n):
        str1 = ""
        for line in range(n):
            str1 += str(int(A[row][line]))
            str1 += ' '
        str1 += "\n"
        nt1.insert("%d.%d" % (0, int(row)),str1)
    for row in range(n):
        str2 = ""
        str2 += str(int(A[row][0]))
        str2 += "\n"
        nt2.insert("%d.%d" % (0, int(row)), str2)
def nb1():
    var = 0
def buttonRK():
    if e1.get() != "":
        n = int(e1.get())
        newwind(n)
    else:
        messagebox.showinfo("Error", "Please input n")
def Dewin():#解密函数GUI
    if t1.get("0.0","end") != "" and t2.get("0.0","end") != "" and e1.get() != "" and e2.get() != "":
       var = 0
    else:
        messagebox.showinfo("Error", "Please input n,m,A key,B key")
def Enwin():#加密函数GUI
    if t1.get("0.0","end") != "" and t2.get("0.0","end") != "" and e1.get() != "" and e2.get() != "":
        var = 0
    else:
        messagebox.showinfo("Error", "Please input n,m,A key,B key")
if __name__ == '__main__':
    #主窗口
    window = tk.Tk()
    window.title('Multi-table')
    window.geometry('300x950')
    #随机密钥
    b = tk.Button(window, text='Random Key', font=('Arial', 12), width=10, height=1,command=buttonRK)
    b.pack()
    # 2标签
    l2 = tk.Label(window, text='Please input n', font=('Arial', 16), width=40, height=2)
    l2.pack(fill='x')
    # 输入框控件entry
    e1 = tk.Entry(window, show=None, width=8,justify = 'center')  # 显示成明文形式
    e1.pack()
    # 3标签
    l3 = tk.Label(window, text='Please input M', font=('Arial', 16), width=40, height=2)
    l3.pack(fill='x')
    # 输入框控件entry
    e2 = tk.Entry(window, show=None, width=8, justify='center')  # 显示成明文形式
    e2.pack()
    b1 = tk.Button(window, text='From file', font=('Arial', 12), width=10, height=1, command=nb1())
    b1.pack()
    #4标签
    l4 = tk.Label(window, text='A Key', font=('Arial', 16), width=40, height=2)
    l4.pack(fill='x')
    #Text
    t1 = tk.Text(window, height=8,width = 40)
    t1.pack(fill='x')
    #5标签
    l5 = tk.Label(window, text='B Key', font=('Arial', 16), width=40, height=2)
    l5.pack(fill='x')
    # Text
    t2 = tk.Text(window, height=8, width=40)
    t2.pack(fill='x')
    # 5标签
    ll5 = tk.Label(window, text='Text', font=('Arial', 16), width=20, height=2)
    ll5.pack(fill='x')
    # Text
    tt2 = tk.Text(window, height=8, width=20)
    tt2.pack(fill='x')
    # 加密
    De = tk.Button(window, text='Decrypt', font=('Arial', 12), width=10, height=1,command=Dewin())
    De.pack(side=TOP)
    # 解密
    En = tk.Button(window, text='Encrypt', font=('Arial', 12), width=10, height=1,command=Enwin())
    En.pack(side=TOP)
    # 6标签
    l6 = tk.Label(window, text='SOLUTION', font=('Arial', 16), width=20, height=2)
    l6.pack(fill='x')
    # Text
    t3 = tk.Text(window, height=8, width=20)
    t3.pack(fill='x')
    # 8标签
    l8 = tk.Label(window, text='@FZU-IS-404 ZERO-A-ONE', font=('Arial', 10), width=40, height=2)
    l8.pack(fill='x')
    window.mainloop()