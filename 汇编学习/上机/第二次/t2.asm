include irvine32.inc
.data
i dd ?
sb dd ?
.code
main proc	
	mov ecx,10000;i<=n
	mov esi,2;i=2
S1:
	mov sb,0;s=0
	mov i,esi
	call LON
	;s=s-i
	mov eax,sb
	sub eax,esi	
	mov sb,eax 
	;if(s == i)
	cmp eax,esi
	JB S2
	JA S2
	mov eax,esi
	call writedec
	call crlf
S2:
	inc esi;i++
	loop S1
	exit
main endp

LON PROC
	push eax
	push ecx
	push edx
	mov ecx,i
	mov ebx,1	;j=1
L:
	mov edx,0
	mov eax,i
	div ebx
	cmp edx,0
	JG S	
	call Scall
S:
	inc ebx
	loop L
	pop edx
	pop ecx
	pop eax
	ret
LON ENDP

Scall PROC
	push eax

	mov eax,sb
	add eax,ebx
	mov sb,eax

	pop eax
	ret
Scall ENDP
DumpL PROC
	ret
DumpL ENDP
end  main
