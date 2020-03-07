;Code by 苏煜程，18级信息安全，福州大学，031803108
INCLUDE Irvine32.inc
.data?
sz dd 32 dup(?)
max dd (?)
.const
ad	dd 4
.code
main PROC
	mov eax,32
	push eax
	mov eax,offset sz
	push eax
	call Creat
	mov eax,32
	push eax
	mov eax,offset sz
	push eax
	call MMax
	mov eax,32
	push eax
	mov eax,offset sz
	push eax
	call WHO
	exit	
main ENDP

Creat PROC	_addr,_num
	mov	ebx,_addr
	mov ecx,_num
	dec	ecx
	mov	edx,0
@@:
	mov	[ebx],edx
	add	ebx,ad
	inc	edx
	loop @B
	ret
Creat ENDP

CM PROC  _Var1
	mov eax,_Var1
	cmp max,eax
	jl	T1
	ret
T1:
	mov max,eax
	ret
CM ENDP

MMax PROC  _addr,_num
	mov	ebx,_addr
	mov eax,dword ptr[ebx]
	mov max,eax
	mov ecx,_num
	dec	ecx
@@:
	add ebx,ad
	mov eax,dword ptr[ebx]
	push eax
	call CM
	loop @B
	ret
MMax ENDP

WHO PROC _addr,_num
	mov	ebx,_addr
	mov ecx,_num
	dec	ecx
	sub ebx,ad
	mov edx,-1
@@:
	inc edx
	add	ebx,ad
	mov eax,dword ptr[ebx]
	cmp max,eax
	jg S
	loop @B
S:	mov	eax,ecx
	call writeint
	ret
WHO ENDP
END main