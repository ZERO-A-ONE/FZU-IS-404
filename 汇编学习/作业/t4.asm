INCLUDE Irvine32.inc
.data
sz dd 1,12,163,4,5,6,7,8,9,10
.data?
max dd 1 dup(?)
.const
ad dd 4
.code
main PROC
    mov	ebx,offset sz
	mov eax,dword ptr[ebx]
	mov max,eax
	mov ecx,9
@@:
	add ebx,ad
	mov eax,dword ptr[ebx]
	push eax
	call CM
	add esp,4
	loop @B
	mov eax,max
	call writeint
	exit	
main ENDP
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