INCLUDE Irvine32.inc
.data
    arr dd 1,23,43,534,654,123,10,23,2
    cnt dd ($-arr)/4
.data?
    ii dd ?
    jj dd ?
    basenum dd ?
.code
AdjustArray proc USES eax ebx ecx esi edi, 
    Array : ptr sdword,
    headIndex : sdword,
    tailIndex : sdword
    mov eax,Array
    mov esi,headIndex;ESI = left pointer
    mov edi,tailIndex;EDI = right pointer
    mov ebx,[eax+4*esi];EBX= middle number
L1:
    cmp esi,edi
    jge L4  
L2:
    cmp esi,edi
    jge L4
    cmp ebx,[eax+4*edi]
    jg E1
    dec edi
    jmp L2
E1:     ;
    mov ecx,[eax+4*edi]
    mov [eax+4*esi],ecx
    inc esi
L3:
    cmp esi,edi 
    jge L4 
    cmp ebx,[eax+4*esi]
    jl E2
    inc esi
    jmp L3 
E2: 
    mov ecx,[eax+4*esi]
    mov [eax+4*edi],ecx
    dec edi 
    jmp L1
L4:;quick_sort1(s, l, i - 1)
    mov [eax+4*esi],ebx
    dec esi
    inc edi 
    cmp esi,headIndex
    jle L5
    INVOKE AdjustArray,Array,headIndex,esi
L5:;quick_sort1(s, i + 1, r)
    cmp edi,tailIndex
    jge END1
    INVOKE AdjustArray,Array,EDI,tailIndex
END1:
    ret
AdjustArray endp

QuickSort proc uses eax,
    Array:ptr sdword,
    len:sdword
    mov eax,len
    dec eax
    INVOKE AdjustArray,Array,0,eax
    ret
QuickSort endp

main proc
    INVOKE QuickSort,offset arr,cnt
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
main endp
end main