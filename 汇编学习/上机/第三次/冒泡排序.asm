INCLUDE Irvine32.inc
.data
    arr dd 1,23,43,534,654,123,10,23,2
    cnt dd ($-arr)/4
.code
main proc
    lea edx,arr
    mov ecx,cnt
    call outPut
    call crlf
    call bubbleSort
    call outPut
    exit
main endp

bubbleSort proc
;edx:arr; ecx:cnt;esi:i;edi:j
;ebx:n-1-i
    pushad
    dec ecx; ecx=cnt- - 1
    mov esi, 0;esi: i
again_outer:
    cmp esi, ecx
    jae final_outer
    mov edi, 0
    mov ebx, ecx
    sub ebx, esi
again_inner:
    cmp edi,ebx
    jae final_inner
    mov eax,[edx+4*edi]
    cmp eax,[edx+4*edi+4]
    jle next
    push eax
    mov eax,[edx+4*edi+4]
    mov [edx+4*edi],eax
    pop [edx+4*edi+4]
next:
    inc edi
    jmp again_inner
final_inner:
    inc esi
    jmp again_outer
final_outer:
    popad
    ret
bubbleSort endp

outPut proc
    pushad 
    mov esi,0
again:
    cmp esi,ecx
    jae final

    mov eax,[edx+4*esi]
    call writeint
    mov al,','
    call writechar

    inc esi
    jmp again
final:
    popad
    ret
outPut endp
end main