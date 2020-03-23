INCLUDE Irvine32.inc
.data
buffer db 34 DUP(?),0,0
str1 db "12345"
tmp dd ?
.data?
stdInHandle dd ?
bytesRead dd ?
tmps1 db 14 dup(?)
tmps2 db 14 dup(?)
tmp1 dd ?
tmp2 dd ?
lent1 dd ?
lent2 dd ?
Endd dd ?
modd dd ?
num dd ?
index dd ?
.code
main PROC
    ;call ReadStr
    ;call Find
    ;call Init
    ;call Tes
    mov ebx,offset str1
    mov ecx,5
    mov edx,0
@@:
    xor eax,eax
    mov al,byte ptr [ebx]

    push edx
    call Expone
    add esp,4   ;Endd

    call HextoTen
    call writedec

    push ebx
    push edx
    mov ebx,Endd
    mul ebx
    add eax,tmp
    mov tmp,eax
    call writedec
    call crlf
    pop edx
    pop ebx

    inc ebx
    inc edx
    loop @B
    exit
main ENDP

Init PROC
    ;初始化符号位
    mov eax,LENGTHOF buffer
    sub eax,index 
    mov index,eax
    ;初始化左串长
    mov eax,index
    dec eax
    mov lent1,eax
    ;初始化右串长
    mov eax,bytesRead
    sub eax,2
    sub eax,index 
    mov lent2,eax
    ;初始化左串
    cld                        
    mov esi, OFFSET buffer     
    mov edi, OFFSET tmps1     
    mov ecx, lent1   
    rep movsb 
    ;初始化右串
    cld                        
    mov esi, OFFSET buffer     
    add esi,index
    mov edi, OFFSET tmps2     
    mov ecx, lent2  
    rep movsb 

    ret
Init ENDP

ReadStr PROC
      ;获取到标准输入的句柄
      INVOKE GetStdHandle,STD_INPUT_HANDLE
      mov stdInHandle,eax
      ;等待用户输入
      INVOKE ReadConsole,stdInHandle,ADDR buffer,\
      34 - 2 , ADDR bytesRead , 0
      ;因为回车、换行要占用2个字节
      ret
ReadStr ENDP

Addd PROC
    mov eax,tmp1
    mov ebx,tmp2
    add eax,ebx
    call writedec
    ret
Addd ENDP

Subb PROC
    mov eax,tmp1
    mov ebx,tmp2
    sub eax,ebx
    call writedec
    ret  
Subb ENDP

Mull PROC
    mov eax,tmp1
    mov ebx,tmp2
    mul ebx
    call writedec
    ret  
Mull ENDP

Divv PROC
    mov eax,tmp1
    mov edx,0
    mov ebx,tmp2
    div ebx
    call writedec
    ret 
Divv ENDP


Find PROC
	mov edi,OFFSET buffer
    mov al, '+'
    mov ecx,LENGTHOF buffer
    cld
    repne scasb
    jnz S
	mov index,ecx
    mov eax,1
    mov modd,eax
    ret
S:
    mov edi,OFFSET buffer
    mov al, '-'
    mov ecx,LENGTHOF buffer
    cld
    repne scasb
    jnz M
	mov index,ecx
    mov eax,2
    mov modd,eax
    ret
M:
    mov edi,OFFSET buffer
    mov al, '*'
    mov ecx,LENGTHOF buffer
    cld
    repne scasb
    jnz D
	mov index,ecx
    mov eax,3
    mov modd,eax
    ret
D:
    mov edi,OFFSET buffer
    mov al, '/'
    mov ecx,LENGTHOF buffer
    cld
    repne scasb
    jnz E
	mov index,ecx
    mov eax,4
    mov modd,eax
    ret
E:
    ret
Find ENDP

Tes PROC
    mov eax,index
    call writedec
    call crlf

    mov eax,modd
    call writedec
    call crlf

    mov eax,lent1
    call writedec
    call crlf

    mov eax,lent2
    call writedec
    call crlf

    mov edx,OFFSET tmps1      
    call writestring
    call crlf

    mov edx,OFFSET tmps2      
    call writestring
    call crlf

    ret
Tes ENDP

Expone PROC ndex ;幂运算
    push eax
    push ebx
    push ecx
    push edx
    mov ecx,ndex
    mov eax,10 ;Base
    mov ebx,eax
    mov num,eax
    cmp ecx,0
    JNG L1
    cmp ecx,1
    JNG L2
    JMP L3
L1:
    mov eax,1
    mov Endd,eax
    pop edx
    pop ecx
    pop ebx
    pop eax
    ret
L2:
    mov eax,10
    mov Endd,eax
    pop edx
    pop ecx
    pop ebx
    pop eax
    ret
L3:
    dec ecx
    @@:
    xor edx,edx
    mul ebx
    mov Endd,eax
    loop @B
    mov eax,Endd
    pop edx
    pop ecx
    pop ebx
    pop eax
    ret
Expone ENDP

HextoTen PROC 
    sub eax,48
    ret
HextoTen ENDP
END main
