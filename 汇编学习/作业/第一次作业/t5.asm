INCLUDE Irvine32.inc
.data?
sz dd 10 dup(?)
max dd (?)
.const
ad dd 4
.code
main PROC
	call INPUT
	mov	ebx,offset sz
	mov eax,dword ptr[ebx]
	mov max,eax
	mov ecx,9
S:
	add ebx,ad
	mov eax,dword ptr[ebx]
	push eax
	call CM
	add esp,4
	loop S
	mov eax,max
	call writeint
	exit	
main ENDP

INPUT PROC
	mov	ebx,offset sz
	mov ecx,10
S:
	call readint
	mov [ebx],eax
	add ebx,ad
	loop S
	ret
INPUT ENDP

CM PROC  _Var1
	mov eax,_Var1
	cmp max,eax
	jl	T1
	ret
T1:
	mov max,eax
	ret
CM ENDP
END main