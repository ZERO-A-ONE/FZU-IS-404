INCLUDE Irvine32.inc
.data
    arr dd 1,23,43,534,654,123,10,23,2
    cnt dd ($-arr)/4
.data?
    ii dd ?
    jj dd ?
    basenum dd ?
.code
QuickSortRecursion PROC USES eax ebx ecx esi edi,
        pArray : PTR SDWORD,
        headIndex : SDWORD,
        tailIndex : SDWORD
         
    mov EAX,pArray      
    mov ESI,headIndex
    mov EDI,tailIndex
    mov EBX,[EAX+4*ESI]
     
    ;ESI = left pointer, EDI = right pointer, EBX= middle number 
    L1:
    CMP ESI,EDI
    jge L4
        L2:
        cmp ESI,EDI
        jge L4  
        cmp EBX,[EAX+4*EDI]
        jg E1
        dec EDI
        jmp L2
        E1:
        mov ECX,[EAX+4*EDI]
        mov [EAX+4*ESI],ECX
        inc ESI
         
        L3:
        cmp ESI,EDI
        jge L4
        cmp EBX,[EAX+4*ESI]
        jl E2
        inc ESI
        jmp L3
        E2:
        mov ECX,[EAX+4*ESI]
        mov [EAX+4*EDI],ECX
        dec EDI
    jmp L1
     
    L4:
    mov [EAX+4*ESI],EBX
    dec ESI
    inc EDI
    cmp ESI,headIndex
    jle L5
    INVOKE QuickSortRecursion,pArray,headIndex,ESI
    L5:
    cmp EDI,tailIndex
    jge END1
    INVOKE QuickSortRecursion,pArray,EDI,tailIndex
    END1:
     
    ret
QuickSortRecursion ENDP

QuickSort PROC USES eax ,
        pArray:PTR SDWORD,
        len : SDWORD
    mov eax,len
    dec eax
    INVOKE QuickSortRecursion,pArray,0,eax
    ret
QuickSort ENDP

main proc
    INVOKE QuickSort,offset arr,cnt

    lea edx,arr ;edx = a[0] , edx = i
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