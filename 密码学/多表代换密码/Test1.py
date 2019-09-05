import numpy as np
n = int(input())
A = np.zeros((n,n))
for row in range(n):
    A[row] = input().split(' ')
for row in range(n):
    for column in range(n):
        A[row][column] = int(A[row][column])
ReA = np.linalg.inv(A)
print(ReA)
print(ReA * A)
