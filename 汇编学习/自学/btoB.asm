assume cs:codesg,ds:datasg
datasg segment
    db 'BaSiC' ;ACSII One Char 1byte 1db
    db 'MinIX'
datasg ends
codesg segment
start:  mov ax,datasg
        mov ds,ax
        mov bx,0
        mov cx,0
    s:  mov al,[bx] ;0[bx]
        and al,11011111b
        mov [bx],al
        mov al,[5+bx] ;5[bx]
        or  al,00100000b
        mov [5+bx],al
        inc bx
        loop s
codesg ends
end start