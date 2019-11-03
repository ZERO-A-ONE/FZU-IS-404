import random
import math
def create_prime_num(keylength):#生成大素数
    while True:
        n = random.randint(0, keylength)
        if n % 2 != 0:
            found = True
            for i in range(0, 1000):
                if miller_rabin_test(n):
                    pass
                else:
                    found = False
                    break
            if found:
                return n
def miller_rabin_test(n):#素性检测
    p = n - 1
    r = 0
    # P110定理5.17 P108定理5.3.6
    # 寻找满足n-1 = 2^s  * m 的s,m两个数
    #  n -1 = 2^r * p
    while p % 2 == 0:  # 最后得到为奇数的p(即m)
        r += 1
        p /= 2
    b = random.randint(2, n - 2)  # 随机取b=（0.n）
    # 如果情况1    b得p次方  与1  同余  mod n
    if fastExpMod(b, int(p), n) == 1:
        return True  # 通过测试,可能为素数
    # 情况2  b得（2^r  *p）次方  与-1 (n-1) 同余  mod n
    for i in range(0,7):  # 检验六次
        if fastExpMod(b, (2 ** i) * p, n) == n - 1:
            return True  # 如果该数可能为素数，
    return False  # 不可能是素数