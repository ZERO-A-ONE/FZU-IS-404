# CG CTF 南邮 RE逆向题 笔记

### 1.Hello，RE！

没什么好讲的，签到题，把获得的题目文件 1.exe 直接拖进IDA Pro即可

```
; int __cdecl main(int argc, const char **argv, const char **envp)
public _main
_main proc near
push    ebp
mov     ebp, esp
and     esp, 0FFFFFFF0h
sub     esp, 90h
call    ___main
mov     dword ptr [esp], 410000h ; char *
call    __Z6printfPKcz  ; printf(char const*,...)
mov     dword ptr [esp+75h], 67616C66h
mov     dword ptr [esp+79h], 6C65577Bh
mov     dword ptr [esp+7Dh], 656D6F63h
mov     dword ptr [esp+81h], 5F6F545Fh
mov     dword ptr [esp+85h], 575F4552h
mov     dword ptr [esp+89h], 646C726Fh
mov     word ptr [esp+8Dh], 7D21h
mov     byte ptr [esp+8Fh], 0
jmp     short loc_401592
```

有个 strcmp 函数，比较 v4 和 v5 地址的。选中 v5 ，发现倒序的 flag 字样。

按R即可获得Flag：flag{Welcome_To_RE_World!}

### 2.ReadAsm2

单纯的汇编语言考察题目，题目有两段汇编代码

```c
int main(int argc, char const *argv[])
{
  char input[] = {0x0,  0x67, 0x6e, 0x62, 0x63, 0x7e, 0x74, 0x62, 0x69, 0x6d,
                  0x55, 0x6a, 0x7f, 0x60, 0x51, 0x66, 0x63, 0x4e, 0x66, 0x7b,
                  0x71, 0x4a, 0x74, 0x76, 0x6b, 0x70, 0x79, 0x66 , 0x1c};
  func(input, 28);
  printf("%s\n",input+1);
  return 0;
}
```

打开题目文件 2.asm 可获得第二段 func函数 汇编代码

```haxe
00000000004004e6 <func>:
  4004e6: 55                    push   rbp
  4004e7: 48 89 e5              mov    rbp,rsp
  4004ea: 48 89 7d e8           mov    QWORD PTR [rbp-0x18],rdi
  4004ee: 89 75 e4              mov    DWORD PTR [rbp-0x1c],esi
  4004f1: c7 45 fc 01 00 00 00  mov    DWORD PTR [rbp-0x4],0x1
  4004f8: eb 28                 jmp    400522 <func+0x3c>
  4004fa: 8b 45 fc              mov    eax,DWORD PTR [rbp-0x4]
  4004fd: 48 63 d0              movsxd rdx,eax
  400500: 48 8b 45 e8           mov    rax,QWORD PTR [rbp-0x18]
  400504: 48 01 d0              add    rax,rdx
  400507: 8b 55 fc              mov    edx,DWORD PTR [rbp-0x4]
  40050a: 48 63 ca              movsxd rcx,edx
  40050d: 48 8b 55 e8           mov    rdx,QWORD PTR [rbp-0x18]
  400511: 48 01 ca              add    rdx,rcx
  400514: 0f b6 0a              movzx  ecx,BYTE PTR [rdx]
  400517: 8b 55 fc              mov    edx,DWORD PTR [rbp-0x4]
  40051a: 31 ca                 xor    edx,ecx
  40051c: 88 10                 mov    BYTE PTR [rax],dl
  40051e: 83 45 fc 01           add    DWORD PTR [rbp-0x4],0x1
  400522: 8b 45 fc              mov    eax,DWORD PTR [rbp-0x4]
  400525: 3b 45 e4              cmp    eax,DWORD PTR [rbp-0x1c]
  400528: 7e d0                 jle    4004fa <func+0x14>
  40052a: 90                    nop
  40052b: 5d                    pop    rbp
  40052c: c3                    ret
```

分析过程记录：

#### （1）main() 部分

`0x` 表示十六进制。
flag 是对此 input 数组的操作组合而成。

<http://www.bluesock.org/~willg/dev/ascii.html>

#### （2）函数调用部分

**4004e6**：表示该指令对应的虚拟内存地址
**55**：该指令对应的计算机指令

函数调用过程：

> 入栈，将寄存器的值压入调用 bp 栈中
> 建立新栈帧，别掉函数栈帧栈底地址放入寄存器

实现

```
 push   rbp
 mov    rbp,rsp
```

寄存器类型：

```
ax(accumulator): 可用于存放函数返回值
bp(base pointer): 用于存放执行中的函数对应的栈帧的栈底地址
sp(stack poinger): 用于存放执行中的函数对应的栈帧的栈顶地址
ip(instruction pointer): 指向当前执行指令的下一条指令
```

前缀加上 r 表示 64 位， e 表示 32 位，使用时表示该寄存器存储 xx 位的数据。

#### （3）执行过程

```haxe
00000000004004e6 <func>:
  4004e6: 55                    push   rbp                         /*函数调用
  4004e7: 48 89 e5              mov    rbp,rsp                              */
  4004ea: 48 89 7d e8           mov    QWORD PTR [rbp-0x18],rdi       //rdi 存第一个参数
  4004ee: 89 75 e4              mov    DWORD PTR [rbp-0x1c],esi       //esi 存第二个参数
  4004f1: c7 45 fc 01 00 00 00  mov    DWORD PTR [rbp-0x4],0x1        //在[rbp-0x4]写入 0x1
  4004f8: eb 28                 jmp    400522 <func+0x3c>
  4004fa: 8b 45 fc              mov    eax,DWORD PTR [rbp-0x4]         //把[rbp-0x4]的值送入 eax ,即 eax = 1
  4004fd: 48 63 d0              movsxd rdx,eax                         //扩展,传送 rdx=1
  400500: 48 8b 45 e8           mov    rax,QWORD PTR [rbp-0x18]        //第一个参数 [rbp-0x18]，rax=input[0]
  400504: 48 01 d0              add    rax,rdx                         //rax = input[1]
  400507: 8b 55 fc              mov    edx,DWORD PTR [rbp-0x4]         //第 6 行中存储的 0x1 ,传入 edx ,即 edx =1
  40050a: 48 63 ca              movsxd rcx,edx                          //rcx=1
  40050d: 48 8b 55 e8           mov    rdx,QWORD PTR [rbp-0x18]         // rdx = input[0]
  400511: 48 01 ca              add    rdx,rcx                          //rdx += rcx ,rdx = input[1]
  400514: 0f b6 0a              movzx  ecx,BYTE PTR [rdx]               //ecx = input[1]
  400517: 8b 55 fc              mov    edx,DWORD PTR [rbp-0x4]          //edx = 0x1 
  40051a: 31 ca                 xor    edx,ecx                          //edx ^= ecx ,原先 ecx 为 1100111，edx 为 0000001，操作后 edx 为 1100110，即 f
  40051c: 88 10                 mov    BYTE PTR [rax],dl                //rax = dl
  40051e: 83 45 fc 01           add    DWORD PTR [rbp-0x4],0x1          //[rbp-0x4]处为 0x1
  400522: 8b 45 fc              mov    eax,DWORD PTR [rbp-0x4]          //把[rbp-0x4]的值送入 eax，eax=1
  400525: 3b 45 e4              cmp    eax,DWORD PTR [rbp-0x1c]         // 比较操作，将[rbp-0x1c] 处的值与eax比较，改变状态位，eax=28时，ZF=1，否则ZF=0
  400528: 7e d0                 jle    4004fa <func+0x14>               //eax < 28 时跳转至 4004fa   func(input, 28); ZF=1时跳出
  40052a: 90                    nop
  40052b: 5d                    pop    rbp
  40052c: c3                    ret
```

- -word 表示字
  q 四字 d 双字
  dword qword

```
dword 2*16 =32 位
qword 4*16 = 64 位 
```

- PTR 指针（pointer）
  没有寄存器名时， X ptr 指明内存单元的长度，X 在汇编指令中可以为word 或 byte 。
- 内存地址

```
[rbp-0x18]
```

- 涉及指令

```
1.movsxd 指令为扩展至零
将32位的寄存器和内存操作数符号扩展到64位的寄存器
2.逻辑异或运算指令 XOR 
XOR OPRD1,OPRD2 
实现两个操作数按位‘异或’(异为真,相同为假)运算,结果送至目的操作数中.
OPRD1<--OPRD1 XOR OPRD2
3.JLE
 小于等于时转移
```

操作行为链：

```
rdx——rax
edx——rcx
rcx——rdx 作为累加
```

简单来说就是input[i]*i，最后用ASCII码输出

我们来用Swift语言实现

```swift
import UIKit;
func main()
{
    var inputs:[Int] = [0x67, 0x6e, 0x62, 0x63, 0x7e, 0x74, 0x62, 0x69, 0x6d,0x55, 0x6a, 0x7f, 0x60, 0x51, 0x66, 0x63, 0x4e, 0x66, 0x7b,0x71, 0x4a, 0x74, 0x76, 0x6b, 0x70, 0x79, 0x66 , 0x1c]
    var flag = Slove(inputs: inputs,num: 28)
    print((flag))
}
func Slove(inputs:Array<Int>,num:Int)-> String
{
    var flag = " "
    for i in 1...num
    {
        var char1 = Character(UnicodeScalar(inputs[i-1]^i)!);
        flag += String(char1);
    }
    return flag
}
main()
```

还可以使用Python语言来实现

```python
def func(inputs, num):
    flag = ''
    for i in range(1, num):
        flag += chr(inputs[i-1] ^ i)
    return flag

def main():
    inputs = [0x67, 0x6e, 0x62, 0x63, 0x7e, 0x74, 0x62, 0x69, 0x6d,0x55, 0x6a, 0x7f, 0x60, 0x51, 0x66, 0x63, 0x4e, 0x66, 0x7b,0x71, 0x4a, 0x74, 0x76, 0x6b, 0x70, 0x79, 0x66 , 0x1c]
    flag = func(inputs, 28)
    print flag

if __name__=='__main__':
    main()
```

可获得Flag：flag{read_asm_is_the_basic}

### 3.Py交易

根据题意可知，即为Python逆向题目，打开在线Python反编译应用，推荐：https://tool.lu/pyc/

可获得反编译代码

```python

#!/usr/bin/env python
# encoding: utf-8
import base64
 
def encode(message):                        #def定义了一个encode模块的变量
    s = ''                                  #为了存入最后的目标串
    for i in message:                       #ord()函数主要用来返回对应字符的ascii码
        x = ord(i) ^ 32                     #将输入的字符串中每个字符ascii码都与32进行异或运算
        x = x + 16                          #每个都加上16
        s += chr(x)                         #再将它们一个一个转为字符
    
    return base64.b64encode(s)              #最后再将新串进行一次base64加密
 
correct = 'XlNkVmtUI1MgXWBZXCFeKY+AaXNt'    #输入的串
flag = ''                                   #为了存入最后的目标串
print 'Input flag:'                         #屏幕提示信息 请输入flag
flag = raw_input()                          #获取输入
if encode(flag) == correct:                 #如果加密后的flag与correct相同  输出correct
                                                            
    print 'correct' 
else:                                       #否则输出wrong
    print 'wrong'                
```

分析代码可知，输入的Flag，要经过每个字符对应的ascii码与32进行异或运算，且加上16，再转换为ascii字符，最后再将新的flag字符串进行一次base64加密，与'XlNkVmtUI1MgXWBZXCFeKY+AaXNt'进行匹配。那么反过来，只要将'XlNkVmtUI1MgXWBZXCFeKY+AaXNt'进行base64解密，每个字符转换为ascii码，减去16，与32进行异或，再输出为字符即可获得flag。

我们用Swift语言进行实现(Swift的Base64我没搞定，有莫名其妙的BUG）

```swift
import UIKit
extension Character//扩充方法使字符转为ascii码
{
    func toInt() -> Int
    {
        var intFromCharacter:Int = 0
        for scalar in String(self).unicodeScalars
        {
            intFromCharacter = Int(scalar.value)
        }
        return intFromCharacter
    }
}
func main()
{
    var str:String = "^SdVkT#S ]`Y\\!^)ism"
    var flag = " "
    for i in str
    {
        var num = Character(UnicodeScalar((i.toInt()-16)^32)!)
        flag += String(num)
    }
    print(flag)
}
main()
```

也可以使用Python实现

```python
import base64
correct ='XlNkVmtUI1MgXWBZXCFeKY+AaXNt'
s = base64.b64decode(correct)
flag =''
for i in s:
i = chr((ord(i)-16)^32)
flag += i 
print flag
```

可获得Flag：nctf{d3c0mpil1n9_PyC}

### 4、WxyVM

用Winhex打开以后可以看出来是ELF文件，所以用Ghidra打开,在内存地址为004006e2的地方发现名为FUN_004006e3的函数，通过分析可以得知即为main函数

```c
undefined8 FUN_004006e3(void)
{
  size_t sVar1;
  bool bVar2;
  int local_c;
  
  puts("[WxyVM 0.0.1]");
  puts("input your flag:");
  scanf("%s",&DAT_00604b80);
  FUN_004005b6();
  sVar1 = strlen(&DAT_00604b80);
  bVar2 = sVar1 == 0x18;
  local_c = 0;
  while (local_c < 0x18) {
    if ((int)(char)(&DAT_00604b80)[(long)local_c] != *(int *)(&DAT_00601060 + (long)local_c * 4)) 
    {
      bVar2 = false;
    }
    local_c = local_c + 1;
  }
  if (bVar2) {
    puts("correct");
  }
  else {
    puts("wrong");
  }
  return 0;
}
```

所以经过分析可以判断变换后的flag在601060处。函数的主体还是比较简单的，现在需要对输入之后的4005b6函数进行分析。

```c
__int64 sub_4005B6()
{
  unsigned int v0; // ST04_4
  __int64 result; // rax
  signed int i; // [rsp+0h] [rbp-10h]
  char v3; // [rsp+8h] [rbp-8h]
 
  for ( i = 0; i <= 14999; i += 3 )
  {
    v0 = byte_6010C0[i];
    v3 = byte_6010C0[i + 2];
    result = v0;
    switch ( v0 )
    {
      case 1u:
        result = byte_6010C0[i + 1];
        *(&byte_604B80 + result) += v3;
        break;
      case 2u:
        result = byte_6010C0[i + 1];
        *(&byte_604B80 + result) -= v3;
        break;
      case 3u:
        result = byte_6010C0[i + 1];
        *(&byte_604B80 + result) ^= v3;
        break;
      case 4u:
        result = byte_6010C0[i + 1];
        *(&byte_604B80 + result) *= v3;
        break;
      case 5u:
        result = byte_6010C0[i + 1];
        *(&byte_604B80 + result) ^= *(&byte_604B80 + byte_6010C0[i + 2]);
        break;
      default:
        continue;
    }
  }
  return result;
}
```

函数是对一个比较长的数组进行操作6010c0处的数组进行操作，一共有15000个数据，每三个为一组，v0决定进行什么操作，v2用来寻址操作，v3作为操作数利用这个函数对已知的数据进行逆运算就能够得到最终的输入结果了。这里要注意对已知数据进行逆向的时候计数的时候也要倒着计数，从14999~0

### 9.注意！！！

> 再次重申，请不要未经同意便盗用我们的题目，如果有使用的需要，请和我们联系，联系方式已经在notice已经给出.flag{zhaowomen}

可获得Flag：flag{zhaowomen}