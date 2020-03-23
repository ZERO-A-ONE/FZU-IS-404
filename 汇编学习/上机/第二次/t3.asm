include irvine32.inc
.data
k dd ?
i dd ?
j dd 0
.code
main proc	
	call readdec
	mov k,eax
	xor eax,eax
	call fjzys	
	exit
main endp

fjzys PROC
	mov esi,2 ;int i = 2
S:
	mov eax,k ;eax=100
	cmp eax,esi
	JB fin	
	mov i,esi
	call ifel
	JMP S
fin:
	ret
fjzys ENDP

ifel PROC	
	;k%i == 0
	mov edx,0
	mov eax,k
	mov ebx,esi ;esi i
	div ebx
	cmp edx,0;k%i == 0
	JB S2
	JA S2	;eax商，edx余数. k = k/i
	mov k,eax;k /= i;    //余数
	mov eax,esi
	call writedec
	call crlf
	mov esi,2;i = 2;    //令i重新等于2	
	ret
S2:
	inc esi;i++	
	ret
ifel ENDP
end  main
