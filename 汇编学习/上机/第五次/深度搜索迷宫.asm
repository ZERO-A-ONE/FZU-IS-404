Include Irvine32.inc
.data
pa dd 	    	 2, 2, 2, 2, 2, 2, 2, 2, 2
	     dd            2, 0, 0, 0, 0, 0, 0, 0, 2
	dd	       2, 2, 2, 0, 2, 2, 2, 0, 2
	dd	       2, 2, 2, 0, 2, 2, 2, 0, 2
	dd	       2, 2, 2, 0, 2, 2, 2, 0, 2
	dd	       2, 0, 0, 0, 0, 0, 0, 0, 2
	dd	       2, 0, 2, 2, 2, 2, 2, 0, 2
	dd	       2, 0, 0, 0, 0, 0, 0, 0, 2
	dd	       2, 2, 2, 2, 2, 2, 2, 2, 2
	nine dd 9
	msg db "find path: ",0
	t dd ?
.code
main PROC
	mov esi,1
	mov edi,1
	push edi
	push esi
	call visited
	pop esi
	pop edi
	exit
main ENDP
visited proc
	mov eax,esi
	mul nine
	add eax,edi
	mov pa[eax*4],1

	cmp esi,7
	jl move
	cmp edi,7
	jl move
	mov edx,offset msg
	call writestring
	call crlf
	mov ecx,0
againi:	cmp ecx,9
	jge move
	mov edx,0
againj:	cmp edx,9
	jge iplus
	mov eax,ecx
	push edx
	mul nine
	pop edx
	add eax,edx
	cmp pa[eax*4],1
	je print
	mov eax,ebx
	call writedec
	mov al,' '
	call writechar
	jmp jplus
print:	mov al,'*'
	call writechar
	mov al,' '
	call writechar
jplus:	inc edx
	jmp againj
iplus:	inc ecx
	call crlf
	jmp againi
move:	mov eax,esi
	sub eax,1
	mul nine
	add eax,edi
	mov ebx,pa[eax*4]
	cmp ebx,0
	jg next1
	push edi
	push esi
	sub esi,1
	call visited
	pop esi
	pop edi

next1:	mov eax,esi
	add eax,1
	mul nine
	add eax,edi
	mov ebx,pa[eax*4]
	cmp ebx,0
	jg next2
	push edi
	push esi
	add esi,1
	call visited
	pop esi
	pop edi

next2:	mov eax,esi
	mul nine
	add eax,edi
	sub eax,1
	mov ebx,pa[eax*4]
	cmp ebx,0
	jg next3
	push edi
	push esi
	sub edi,1
	call visited
	pop esi
	pop edi
	
next3:	mov eax,esi
	mul nine
	add eax,edi
	add eax,1
	mov ebx,pa[eax*4]
	cmp ebx,0
	jg final
	push edi
	push esi
	add edi,1
	call visited
	pop esi
	pop edi

final:	mov eax,esi
	mul nine
	add eax,edi
	mov pa[eax*4],0
	ret
visited endp
END main