;Code by 苏煜程，18级信息安全，福州大学，031803108
INCLUDE Irvine32.inc
.data
source dd 1,2,3,4,5,6,7,8,9,10
mug    dd 10
.code
main PROC
    cld                             ;方向为正向
    mov esi,OFFSET source            ;源数组索引
    call show
    mov edi,esi                    ;目标数组索引
    mov ecx,LENGTHOF source          ;循环计数器
@@: 
    lodsw                           ;将 [ESI] 加载到 EAX
    mul mug                  ;与常数相乘
    stosw                           ;将 EAX 保存到［EDI］
    loop @B
    call crlf
    call show
    exit
main ENDP

show PROC
    mov ebx,offset source
    mov ecx,10
@@:
    mov eax,[ebx]
    call writedec
    add ebx,4
    loop @B
    ret
show ENDP
END main
;LODSB从ESI指向的内存地址加载一个字节到AL
;LODSW从ESI指向的内存地址加载一个字到AX
;LODSD从ESI指向的内存地址加载一个双字到EAX