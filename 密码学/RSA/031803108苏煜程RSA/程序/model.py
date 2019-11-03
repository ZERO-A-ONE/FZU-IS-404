import random
import math
from sys import exit
# 模N大数的幂乘的快速算法
def fastExpMod(b, e, m):  # 底数，幂，大数N
    result = 1
    e = int(e)
    while e != 0:
        if e % 2 != 0:  # 按位与
            e -= 1
            result = (result * b) % m
            continue
        e >>= 1
        b = (b * b) % m
    return result
    # 测试案例
    # c = fastExpMod(3,22,12)
    # print(c) 9


# 针对随机取得p，q两个数的素性检测
def miller_rabin_test(n):  # p为要检验得数
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


# 生成大素数：
def create_prime_num(keylength):  # 为了确保两素数乘积n  长度不会太长，使用keylength/2
    while True:
        # Select a random number n
        # n = random.randint(0, 1<<int(halfkeyLength))
        n = random.randint(0, keylength)
        if n % 2 != 0:
            found = True
            # 如果经过10次素性检测，那么很大概率上，这个数就是素数
            for i in range(0, 10):
                if miller_rabin_test(n):
                    pass
                else:
                    found = False
                    break
            if found:
                return n


# 生成密钥（包括公钥和私钥）
def create_keys(keylength):
    p = create_prime_num(keylength / 2)
    q = create_prime_num(keylength / 2)
    n = p * q
    # euler函数值
    fn = (p - 1)*(q - 1)
    e = selectE(fn, keylength / 2)
    d = match_d(e, fn)
    return (n, e, d)


# 随机在（1，fn）选择一个E，  满足gcd（e,fn）=1
def selectE(fn, halfkeyLength):
    while True:
        # e and fn are relatively prime
        e = random.randint(0, fn)
        if math.gcd(e, fn) == 1:
            return e


# 根据选择的e，匹配出唯一的d
def match_d(e, fn):
    d = 0
    while True:
        if (e * d) % fn == 1:
            return d
        d += 1




def encrypt(M, e, n):
    return fastExpMod(M, e, n)

def decrypt( C, d, m):
    return fastExpMod(C, d, m)

def display():
    print("_________________RSA_________________")
    print("1.encrypt")
    print("2.decrypt")
    print("q.quit")
    print("Enter the key you wanna try")
    print("_____________________________________")

def encrypt_file():
    f = input("Please input your message: ")
    mess = f
    n, e, d = create_keys(1024)
    print("请妥善保管私钥（解密时需要用到）：（n:",n," ,d:",d,")")
    s = ''
    t = ""
    #s = encrypt(int(mess), e, n)
    print(mess)
    for ch in mess:
        c = chr(encrypt(ord(ch), e, n))
        t += str(hex(encrypt(ord(ch), e, n)))
        s += c
    print("Encrypt hex message :",t)
    print("Encrypt message :"+s)
    print("Encrypt Done!")

def decrypt_file():
    f = input("Please input your encrypt message: ")
    mess = f
    #n,d = input("私钥：")
    n,d= map(int, input("输入您的私钥（n,d）:").split())
    s = ''
    for ch in mess:
        c = chr(decrypt(ord(ch), d, n))
        s += c
    print(s)
    print("Decrypt Done!")

if __name__ =='__main__':
    display()
    while True:
        c = input(">>>")
        if c=='1':
            encrypt_file()
        if c=='2':
            decrypt_file()
        if c=='q':
            exit(0)
        display()


