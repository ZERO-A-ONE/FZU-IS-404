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
clearlist = "PLEASE SEND ME THE BOOK, MY CREDIT CARD NO IS SIX ONE TWO ONE THREE EIGHT SIX ZERO ONE SIX EIGHT FOUR NINE SEVEN ZERO TWO"
clearlist = list(clearlist)
# 字符串初始化转换为纯字母序列
for i in range(len(clearlist)):
    if clearlist[i] == ',':
        clearlist[i] = ' '
while ' ' in clearlist:
    clearlist.remove(' ')
lenth = len(clearlist)
flag = 0
offset = 0
# 补位操作
if (lenth % 4 == 0):
    flag = 0
else:
    flag = 1
    offset = 4 - lenth % 4
for i in range(offset):
    clearlist.append('A')
for i in range(len(clearlist)):
    clearlist[i] = AtoN(clearlist[i])
groups = int(len(clearlist)/4)
print(clearlist)
print(offset)
print(groups)
# 生成M序列
M = np.ones((groups,4))
index = 0
for row in range(groups):
    for column in range(4):
        M[row][column] = clearlist[index]
        index = index + 1
print(M)
for i in range(groups):
    tmp = np.ones((4, 1))
    for row in range(4):
        tmp[row][0] = M[i][row]
    print(tmp)