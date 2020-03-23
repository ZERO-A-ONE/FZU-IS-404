;Code by 苏煜程，18级信息安全，福州大学，031803108
INCLUDE Irvine32.inc
.data
str1	db "请输入整数：",0
Men1	db "1）2进制",0
Men2	db "2）8进制",0
Men3	db "3）10进制",0
Men4	db "4）16进制",0
Men5	db "请输入选项：",0
.data?
buf dd 128 dup(?)
SourceData dd ?
BaseData dd ?
SSize	dd ?
tmp	dd ?
.const
msg	dd offset Men1
	dd offset Men2
	dd offset Men3
	dd offset Men4
	dd offset Men5
.code
main PROC
	mov edx,offset str1
	call WriteString
	call Readint
	mov	SourceData,eax
	call ShowMenu
	call Readint
	call MenuCh
	exit
main ENDP

IntSize PROC
	mov tmp,eax
	mov ecx,0
S:
	inc ecx
	mov eax,tmp
	mov edx,0
	mov ebx,10
	div ebx
	mov tmp,eax
	cmp eax,0
	JA S
	mov SSize,ecx
	ret
IntSize ENDP

ShowMenu PROC
	mov esi,0
again:
	cmp esi,4
	ja final
	mov edx,msg[4*esi]
	call writestring
	call crlf
	add esi,1
	jmp again
final:
	ret
ShowMenu ENDP

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

MenuCh PROC
	cmp eax,1
	JA L2
	mov eax,2;执行转化成8进制
	push eax
	call ToUnderHex
	add esp,4
	ret
L2:;执行转化成8进制
	cmp eax,2
	JA L3
	mov eax,8
	push eax
	call ToUnderHex
	add esp,4
	ret
L3:;执行转化成10进制
	cmp eax,3
	JA L4
	mov eax,10
	push eax
	call ToUnderHex
	add esp,4
	ret
L4:;执行转化成16进制
	mov eax,16
	push eax
	call ToUnderHex
	add esp,4
	ret
MenuCh ENDP
END main