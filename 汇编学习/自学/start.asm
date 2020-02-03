assume cs:codesg
codesg segment
dw 0123h,0456h,0789h
start:  mov bx,0
        mov ax,0
        mov cx,8
    s:  add ax,cs:[bx]
        add bx,2
        loop s
        move ax,4c00h
        int 21h
codesg ends
end start