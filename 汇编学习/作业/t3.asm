INCLUDE Irvine32.inc
.data?
a dd 1 dup(?)
b dd 1 dup(?)
.code
main PROC
    call readint
    mov a,eax
    call readint
    cmp a,eax
    jge L1
    jl L2
L1: 
    call readint
    cmp a,eax
    jge S1
    jl S2
S1: 
    mov eax,a
    call writeint
    exit
S2: 
    call writeint
    exit
L2: 
    mov b,eax
    call readint
    cmp b,eax
    jge T1
    jl S2
T1: 
    mov eax,b
    call writeint
    exit
main ENDP
END main