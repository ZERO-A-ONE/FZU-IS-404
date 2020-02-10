assume cs:code
code segment
start:
        mov ax,cs 
        mov ds,ax
        mov si,offser dp0   ;设置ds:si指向源地址
        mov ax,0
        mov es,ax
        mov di,200h         ;设置es:di指向目的地址
        mov cx,offset do0end- offset do0    ;设置cx为传输长度
        cld                 ;设置传输方向为正
        rep movsb

        mov ax,0;设置中断向量表
        mov es,ax
        mov word ptr es:[0*4],200h
        mov word ptr es:[0*4+2],0
        
        mov ax,4c00h
        int 21h
do0:    
        jmp short do0start
        db  "Hello World"   ;将数据存放在代码段
do0start:
        mov ax,cs
        mov ds,ax
        mov si,202h         ;设置ds:si指向字符串
        mov ax,0b800h
        mov es,ax
        mov di,12*160+36*2  ;设置es:di指向显存空间的中间位置
        mov cx,21           ;设置cx为字符串长度
doend:
        nop
code ends
end start
;"-"是编译器可以识别的运算符号，两个常数的减法，编译器还可以处理很多表达式