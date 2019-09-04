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
if(lenth%3 == 0):
    flag = 0
else:
    flag = 1
    offset = 3-lenth%3
for i in range(offset):
    clearlist.append('A')
groups = len(clearlist)/3
for i in range(len(clearlist)):
    clearlist[i] = AtoN(clearlist[i])
print(clearlist)
print(offset)
print(groups)
lenth = len(clearlist)
flag = 0
offset = 0
# 补位操作
if (lenth % 3 == 0):
    flag = 0
else:
    flag = 1
    offset = 3 - lenth % 3
for i in range(offset):
    clearlist.append('A')
groups = int(len(clearlist) / 3)
# 生成M序列
M = np.ones((3,groups))
index = 0
for column in range(groups):
    for row in range(3):
        M[row][column] = clearlist[index]
        index = index + 1

print(M)