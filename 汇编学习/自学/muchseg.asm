assume cs:code,ds:data,ss:stack
data segment
    dw  0123H,0456H,0789H,0abcH,0defH,0fedH,0cbaH,0987H
data ends
stack segment
    dw  0,0,0,0,0,0,0,0
stack ends
code segment
start:  mov ax,stack
        mov ss,ax
        mov sp,16
        mov ax,data
        mov ds,ax
        mov bx,0
        mov cx,8
    s:  push [bx]
        add bx,2
        loop s
        mov bx,0
        int 21h
codesg ends
end start