import numpy as np
def exgcd(a,b,x,y):
    if b==0:
        x=1
        y=0
    d = exgcd(b,a%b,y,x)
    y = y - (a/b)*x
    return d
def InverseElement(b,p):#求逆元
    inv = 1
    while 1:
        if (inv*b)%p == 1:
            break
        inv = inv +1
    return inv
def Det(a,n):#求行列式
    b = np.zeros((n, n))#临时数组用于降阶
    sum = int(0)
    sign = int(0)
    p = int(0)
    if n == 1:
        return a[0][0]
    for i in range(n):#此处大循环实现将余子式存入数组b中
        for c in range(n-1):
            for j in range(n-1):
                if c<i:
                    p = 0#当p=0时，行列式只向左移，即消去对应的第一列的数
                else:
                    p = 1#否则行列式左移后再上移
                b[c][j]=a[c+p][j+1]
        if i%2 == 0:
            sign = 1#i为偶数，加法
        else:
            sign = -1#i为奇数，减法
        sum = sum + a[i][0]*Det(b,n-1)*sign#计算行列式的值
    return  sum
def getAStart(arcs,n,ans):#计算每一行每一列的每个元素所对应的余子式，组成A*
    if n == 1:
        ans[0][0] = 1
    temp = np.zeros((n, n))
    for i in range(n):
        for j in range(n):
            for k in range(n-1):
                for t in range(n-1):
                    temp[k][t] = arcs[(k+1 if k>=i else k)][(t+1 if t>=j else t)]
                ans[j][i] = Det(temp,n-1)
                if (i+j)%2 == 1:
                    ans[j][i] = -ans[j][i]
def InverseMat(a,n,p,ans):
    astar = np.zeros((n, n))
    getAStart(a, n, astar)#求A的伴随矩阵
    deta = int(Det(a,n))#求A的行列式
    if deta < 0:
        deta = deta + p
    inv = int(InverseElement(deta,p))
    for i in range(n):
        for j in range(n):
            ans[i][j] = astar[i][j]*inv
            ans[i][j] = ans[i][j]%p
            if ans[i][j] <0:
                ans[i][j] = ans[i][j] + p
if __name__ == '__main__':
    n = int(input())
    p = int(input())
    A = np.zeros((n, n))
    ans = np.zeros((n, n))
    for row in range(n):
        A[row] = input().split(' ')
    for row in range(n):
        for column in range(n):
            A[row][column] = int(A[row][column])
    InverseMat(A,n,p,ans)
    print(ans)

