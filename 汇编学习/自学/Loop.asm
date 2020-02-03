assume cs:code
code segment
start:    mov ax,2
    mov cx,11
S:  add ax,ax
    loop S
    mov ax,4c00h
    int 21h
code ends
end