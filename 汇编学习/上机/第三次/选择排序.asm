;Code by 苏煜程，18级信息安全，福州大学，031803108
INCLUDE Irvine32.inc
.data
buffer db 128 dup(0)
Array dword 76h,12h,28h,230h,10h
ArraySize = ($-Array)/4
.code
main PROC
	mov ecx,ArraySize
	mov ebx,offset Array
@@:
	mov eax,[ebx]
	call writedec
	mov eax,' '
	call writechar
	add	ebx,4
	loop @B
	call crlf

	mov eax,ArraySize
	push eax
	mov eax,offset Array
	push eax
	call sort
	add esp,4

	mov ecx,ArraySize
	mov ebx,offset Array
@@:
	mov eax,[ebx]
	call writedec
	mov eax,' '
	call writechar
	add	ebx,4
	loop @B
	exit
main ENDP
sort PROC ptr2,count
	mov ecx,count
	dec ecx
L1:
	push ecx	;	定义外层循环
	mov esi,ptr2
L2:
	mov eax,[esi]	;定义内层循环
	cmp [esi+4],eax
	jge  L3
	xchg eax,[esi+4]
	mov [esi],eax
L3:
	add esi,4
	loop L2
	pop ecx
	loop L1
	ret
sort ENDP
END main