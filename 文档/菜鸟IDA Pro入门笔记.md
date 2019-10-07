# 菜鸟IDA Pro入门笔记

## 开始界面

###### New（新建）

###### Go（运行）

###### Previous（上一个）

## 主界面工作区

###### IDA View-A 反汇编窗口

###### HexView-A 十六进制格式显示的窗口

###### Imports 导入表（程序中调用到的外面的函数）

###### Functions 函数表（这个程序中的函数）

###### Structures 结构

###### Enums 枚举

## IDA View-A反汇编窗口

##### 寄存器

###### AX BX CX DX——通用寄存器

###### CS——代码段寄存器

###### IP——指令指针寄存器

###### DS——段地址寄存器

###### SS——栈段寄存器

###### SP——栈偏移寄存器

###### IEAX——”累加器”(accumulator), 它是很多加法乘法指令的缺省寄存器。 

###### EBX——”基地址”(base)寄存器, 在内存寻址时存放基地址。 

###### ECX——计数器(counter), 是重复(REP)前缀指令和LOOP指令的内定计数器。 

###### EDX——被用来放整数除法产生的余数。 

###### ESI/EDI——分别叫做”源/目标索引寄存器”(source/destination index),因为在很多字符串操作指令中， DS:ESI指向源串,而ES:EDI指向目标串。 

###### EBP——”基址指针”(BASE POINTER), 它最经常被用作高级语言函数调用的”框架指针”(frame pointer)。

###### ESP——专门用作堆栈指针，被形象地称为栈顶指针，堆栈的顶部是地址小的区域，压入堆栈的数据越多，ESP也就越来越小。在32位平台上，ESP每次减少4字节。

##### 资料转移指令

######MOV——移动

######MOVC——程式记忆体移动 

######MOVX——外部RAM和扩展I/O口与寄存器A的数据传送指令

###### PUSH——放入堆栈

###### POP——由堆叠取回 

###### XCH——8位元交换 

###### XCHD——低4位元交换 

###### SWAP——高低4位元交换

##### 算术指令 

###### ADD——两数相加

###### ADDC——两数相加再加C

###### SUBB——两数相减再减C

###### INC——加一指令

###### DEC——减一指令

###### MUL——（MUL AB乘法指令仅此一条）相乘指令，所得的16位二进制数低8位存累加器A高8位存B

###### DIV——（DIV AB 除法指令仅此一条）相除指令，所得商存A，余数存B

##### 控制转移类指令 

###### JC——C=1时跳

###### JNC——C=0时跳

###### JB——位元=1时跳

###### JNB——位元=0时跳

###### JBC——位元=1时跳且清除此位元

###### LCALL——长调用子程序

###### ACALL——绝对调用子程序

###### RET——由副程式返回

###### RETI——由中断副程式返回

###### AJMP——绝对转移

###### SJMP——相对转移

###### JMP——@A+DPTR 散转，相对DPTR的间接转移

###### JZ——A=0时跳

###### JNZA——0时跳

###### CJNE——二数比较,不相等时跳

###### DJNZ——减一,不等於0时跳

###### NOP——空操作

##### 位变量指令

###### SETB——设定为1ORG 程序开始，规定程序的起始地址

###### END——程序结束

###### EQU——等值指令（先赋值后使用）例：SUM EQU 30H

###### DB——定义字节指令

###### DW——定义字内容

###### DS——定义保留一定的存贮单元数目   

###### BIT——位地址符号指令 例：SAM BIT P1.0

###### RET——子程序返回指令

###### RETI——中断子程序返回指令$ 本条指令地址

## IDA快捷键

###### 空格键——反汇编窗口切换文本跟图形

###### ESC——退到上一个操作地址

###### G——搜索地址或者符号

###### N——重命名

###### ；——注释

###### ALT+M——添加标签

###### CTRL+M——列出所有标签

###### CTRL +S——二进制段的开始地址结束地址

###### C code——光标地址出内容解析成代码

###### P——在函数开始处使用P，从当前地址处解析成函数

###### D——data解析成数据

###### A——ASCII解析成ASCII

###### U——unDefined解析成未定义的内容

###### X——交叉引用

###### F5——C伪代码

###### ALT+T——搜索文本

###### ALT+B——搜索16进制 搜索opcode

###### CTRL+ALT+B——打开断点列表 

###### F7——单步步入

###### F8——单步不过

###### CTRL+F7——运行到函数返回地址 

###### F4——运行到光标处 

| 窗口名称          | 快捷键    |
| ----------------- | --------- |
| Names Window      | Shift+F4  |
| Functions Window  | Shift+F3  |
| Strings Window    | Shift+F12 |
| Segments          | Shift+F7  |
| Segment registers | Shift+F8  |
| Signatures        | Shift+F5  |
| Type libraries    | Shift+F11 |
| Structures        | Shift+F9  |
| Enumerations      | Shift+F10 |

------

Data Format Options

| 窗口名称            | 快捷键 | 备注 |
| ------------------- | ------ | ---- |
| ASCII strings style | Alt+A  |      |
| Setup data types    | Alt+D  |      |

------

File Operations

| 窗口名称            | 快捷键  | 备注 |
| ------------------- | ------- | ---- |
| Parse C header file | Ctrl+F9 |      |
| Create ASM file     | Alt+F10 |      |
| Save database       | Ctrl+W  |      |

------

Navigation

| 窗口名称                  | 快捷键     | 备注 |
| ------------------------- | ---------- | ---- |
| Jump to operand           | Enter      |      |
| Jump in new window        | Alt+Enter  |      |
| Jump to previous position | Esc        |      |
| Jump to next position     | Ctrl+Enter |      |
| Jump to address           | G          |      |
| Jump by name              | Ctrl+L     |      |
| Jump to function          | Ctrl+P     |      |
| Jump to segment           | Ctrl+S     |      |
| Jump to segment register  | Ctrl+G     |      |
| Jump to problem           | Ctrl+Q     |      |
| Jump to cross reference   | Ctrl+X     |      |
| Jump to xref to operand   | X          |      |
| Jump to entry point       | Ctrl+E     |      |
| Mark Position             | Alt+M      |      |
| Jump to marked position   | Ctrl+M     |      |

------

Debugger

| 窗口名称          | 快捷键  | 备注 |
| ----------------- | ------- | ---- |
| Start process     | F9      |      |
| Terminate process | Ctrl+F2 |      |
| Step into         | F7      |      |
| Step over         | F8      |      |
| Run until return  | Ctrl+F7 |      |
| Run to cursor     | F4      |      |

------

Breakpoints

| 窗口名称        | 快捷键     | 备注 |
| --------------- | ---------- | ---- |
| Breakpoint list | Ctrl+Alt+B |      |

------

Watches

| 窗口名称     | 快捷键 | 备注 |
| ------------ | ------ | ---- |
| Delete watch | Del    |      |

------

Tracing

| 窗口名称    | 快捷键     | 备注 |
| ----------- | ---------- | ---- |
| Stack trace | Ctrl+Alt+S |      |

------

Search

| 窗口名称               | 快捷键 | 备注 |
| ---------------------- | ------ | ---- |
| Next code              | Alt+C  |      |
| Next data              | Ctrl+D |      |
| Next explored          | Ctrl+A |      |
| Next unexplored        | Ctrl+U |      |
| Immediate value        | Alt+I  |      |
| Next immediate value   | Ctrl+I |      |
| Text                   | Alt+T  |      |
| Next text              | Ctrl+T |      |
| Sequence of bytes      | Alt+B  |      |
| Next sequence of bytes | Ctrl+B |      |
| Not function           | Alt+U  |      |
| Next void              | Ctrl+V |      |
| Error operand          | Ctrl+F |      |

------

Graphing

| 窗口名称       | 快捷键   | 备注 |
| -------------- | -------- | ---- |
| Flow chart     | F12      |      |
| Function calls | Ctrl+F12 |      |

------

Miscellaneous

| 窗口名称                 | 快捷键      | 备注 |
| ------------------------ | ----------- | ---- |
| Calculator               | ?           |      |
| Cycle through open views | Ctrl+Tab    |      |
| Select tab               | Alt + [1…N] |      |
| Close current view       | Ctrl+F4     |      |
| Exit                     | Alt+X       |      |
| IDC Command              | Shift+F2    |      |

------

Edit (Data Types – etc)

| 窗口名称           | 快捷键   | 备注 |
| ------------------ | -------- | ---- |
| Copy               | Ctrl+Ins |      |
| Begin selection    | Alt+L    |      |
| Manual instruction | Alt+F2   |      |
| Code               | C        |      |
| Data               | D        |      |
| Struct variable    | Alt+Q    |      |
| ASCII string       | A        |      |
| Array              | Num *    |      |
| Undefine           | U        |      |
| Rename             | N        |      |

------

Operand Type

| 窗口名称                 | 快捷键         | 备注 |
| ------------------------ | -------------- | ---- |
| Offset (data segment)    | O              |      |
| Offset (current segment) | Ctrl+O         |      |
| Offset by (any segment)  | Alt+R          |      |
| Offset (user-defined)    | Ctrl+R         |      |
| Offset (struct)          | T              |      |
| Number (default)         | #              |      |
| Hexadecimal              | Q              |      |
| Decimal                  | H              |      |
| Binary                   | B              |      |
| Character                | R              |      |
| Segment                  | S              |      |
| Enum member              | M              |      |
| Stack variable           | K              |      |
| Change sign              | Underscore (_) |      |
| Bitwise negate           | ~              |      |
| Manual                   | _ Alt+F1       |      |

------

Comments

| 窗口名称                  | 快捷键    | 备注 |
| ------------------------- | --------- | ---- |
| Enter comment             | :         |      |
| Enter repeatable comment  | ;         |      |
| Enter anterior lines      | Ins       |      |
| Enter posterior lines     | Shift+Ins |      |
| Insert predefined comment | Shift+F1  |      |

------

Segments

| 窗口名称                      | 快捷键 | 备注 |
| ----------------------------- | ------ | ---- |
| Edit segment                  | Alt+S  |      |
| Change segment register value | Alt+G  |      |

------

Structs

| 窗口名称                | 快捷键 | 备注 |
| ----------------------- | ------ | ---- |
| Struct var              | Alt+Q  |      |
| Force zero offset field | Ctrl+Z |      |
| Select union member     | Alt+Y  |      |

------

Functions

| 窗口名称             | 快捷键 | 备注 |
| -------------------- | ------ | ---- |
| Create function      | P      |      |
| Edit function        | Alt+P  |      |
| Set function end     | E      |      |
| Stack variables      | Ctrl+K |      |
| Change stack pointer | Alt+K  |      |
| Rename register      | V      |      |
| Set function type    | Y      |      |

------

