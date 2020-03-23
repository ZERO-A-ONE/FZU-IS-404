include irvine32.inc
.data
i dd 1
j dd ?
.code
main proc
	mov ecx,9
@@:
	call Lo
	mov eax,i
	inc eax
	mov i,eax
	loop @B
	exit
main endp

Lo proc
	pushad
	mov j,1
	mov ecx,i
@@:
	mov eax,i
	call writedec

	mov eax,"*"
	call writechar

	mov eax,j
	call writedec

	mov eax,"="
	call writechar

	xor edx,edx
	mov eax,i
	mov ebx,j
	mul j
	call writedec
	mov eax,j
	inc eax
	mov j,eax

	mov eax," "
	call writechar

	loop @B

	call crlf
	popad
	ret
Lo endp

end  main
