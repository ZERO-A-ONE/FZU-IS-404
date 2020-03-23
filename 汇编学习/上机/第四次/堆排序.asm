include irvine32.inc
.data
arr dd 1,23,43,534,654,123,10,23,2
cnt dd ($-arr)/4
.code
AdjustHeap PROC USES eax ebx ecx edx esi edi,
		pArray : PTR SDWORD,
		len : SDWORD,
		rootIndex : SDWORD			
	mov edx,rootIndex
	mov eax,pArray		
	L1:
	mov esi,edx
	shl esi,1
	inc esi
	cmp esi,len
	jge END1
	mov edi,esi
	inc edi
	cmp edi,len
	jge Exchange
	mov ebx,[eax+4*esi]
	mov ecx,[eax+4*edi]
	cmp ebx,ecx
	jge Exchange
	mov esi,edi
	Exchange:
	mov edi,edx
	mov ebx,[eax+4*esi]
	mov ecx,[eax+4*edi]
	cmp ebx,ecx
	jle END1
	mov [eax+4*esi],ecx
	mov [eax+4*edi],ebx	
	mov edx,esi 
	jmp L1			
	END1:
	ret
AdjustHeap ENDP

HeapSort PROC USES eax ebx ecx edx esi edi,
		pArray : PTR SDWORD,
		len : SDWORD			
	mov eax,len
	sub eax,2
	shr eax,1	
	L1:
	INVOKE AdjustHeap,pArray,len,eax
	DEC eax
	CMP eax,0
	jge L1
	mov eax,pArray
	mov ebx,len
	mov ecx,ebx
	dec ecx
	L2:
	cmp ebx,2
	jl  END1
	mov esi,[eax+4*ecx]
	mov edi,[eax]
	mov [eax+4*ecx],edi
	mov [eax],esi
	dec ebx
	dec ecx
	INVOKE AdjustHeap,pArray,ebx,0
	jmp L2			
	END1:			
	ret
HeapSort ENDP

main proc
	INVOKE HeapSort,offset arr,cnt
	lea edx,arr 
    mov ecx,cnt
@@:
    mov eax,[edx]
    call writedec
    add edx,4
    mov eax,' '
    call writechar
    loop @B
    exit
	exit
main endp

end  main
