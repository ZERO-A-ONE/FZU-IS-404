call crlf ;回车换行

Expone PROC Base,Index ;幂运算
    push eax
    push ebx
    push ecx
    mov ecx,Index
    mov eax,Base
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
    call WriteDec
    call crlf
    pop ecx
    pop ebx
    pop eax
    ret
L2:
    mov eax,Base
    mov Endd,eax
    call WriteDec
    call crlf
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
    call WriteDec
    call crlf
    pop ecx
    pop ebx
    pop eax
    ret
Expone ENDP

.data
buffer db 34 DUP(?),0,0
.data?
stdInHandle dd ?
bytesRead dd ?
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

ShowStr PROC _Val
    mov ebx,_Val
    mov ecx,bytesRead
    @@:
    mov eax,[ebx]
    call WriteChar
    inc ebx
    loop @B
    ret
ShowStr ENDP


Pstack PROC ;字符串逆序
    mov ebx,offset buffer
    mov ecx,bytesRead
    sub ecx,2
    @@:     ;压栈逆序循环
    mov eax,[ebx]
    push eax
    inc ebx
    loop @B

    mov ecx,bytesRead
    sub ecx,2
    mov edx,0
    @@:
    pop eax
    call WriteChar
    mov eax,edx
    call WriteDec


    inc edx
    call crlf
    loop @B
    ret
Pstack ENDP

TryStr PROC AdStr1,Adstr2 ;比较字符串
    mov esi,AdStr1
    mov edi,Adstr1
    CMPSB
    JG L ;不相等
    mov edx,offset str2
    call WriteString
    push 1
    ret
L:
    mov edx,offset str1
    call WriteString
    push 0
    ret
TryStr ENDP

IntSize PROC    ;获取整形大小
	mov SourceData,123
	mov ecx,0
S:
	inc ecx
	mov eax,SourceData
	mov edx,0
	mov ebx,10
	div ebx
	mov SourceData,eax
	cmp eax,0
	JA S
	mov SSize,ecx
	ret
IntSize ENDP
ToUnderTen PROC  BaseNum ;可实现10转10以下任意进制数字
    mov eax,SourceData
    mov ecx,0
S:
	inc ecx
	mov eax,SourceData
	mov edx,0
	mov ebx,BaseNum
	div ebx
	mov SourceData,eax
	push edx
	cmp eax,0
	JA S
@@:
	pop eax
	call writedec
	loop @B
    ret
ToUnderTen ENDP

ToUnderHex PROC BaseNum ;可实现10转16以下任意进制数字
      mov eax,SourceData
      mov ecx,0
S:
	inc ecx
	mov eax,SourceData
	mov edx,0
	mov ebx,BaseNum
	div ebx
	mov SourceData,eax
	push edx
	cmp eax,0
	JA S
@@:
	pop eax
    call TenoHex
	loop @B
      ret
ToUnderHex ENDP

TenoHex PROC
	cmp eax,0
	JA L1
	mov eax,'0'
	call writechar
	ret
L1:
	cmp eax,1
	JA L2
	mov eax,'1'
	call writechar
	ret
L2:
	cmp eax,2
	JA L3
	mov eax,'2'
	call writechar
	ret
L3:
	cmp eax,3
	JA L4
	mov eax,'3'
	call writechar
	ret
L4:
	cmp eax,4
	JA L5
	mov eax,'4'
	call writechar
	ret
L5:
	cmp eax,5
	JA L6
	mov eax,'5'
	call writechar
	ret
L6:
	cmp eax,6
	JA L7
	mov eax,'6'
	call writechar
	ret
L7:
	cmp eax,7
	JA L8
	mov eax,'7'
	call writechar
	ret
L8:
	cmp eax,8
	JA L9
	mov eax,'8'
	call writechar
	ret
L9:
	cmp eax,9
	JA LA
	mov eax,'9'
	call writechar
	ret
LA:
	cmp eax,10
	JA LB
	mov eax,'A'
	call writechar
	ret
LB:
	cmp eax,11
	JA LC
	mov eax,'B'
	call writechar
	ret
LC:
	cmp eax,12
	JA LD
	mov eax,'C'
	call writechar
	ret
LD:
	cmp eax,13
	JA LEE
	mov eax,'D'
	call writechar
	ret
LEE:
	cmp eax,14
	JA LF
	mov eax,'E'
	call writechar
	ret
LF:
	mov eax,'F'
	call writechar
	ret
TenoHex ENDP


HextoTen PROC _Val1
    mov eax,_Val1
    sub eax,48
    ret
HextoTen ENDP
