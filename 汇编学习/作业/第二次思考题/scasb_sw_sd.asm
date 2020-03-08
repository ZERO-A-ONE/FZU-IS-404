;Code by 苏煜程，18级信息安全，福州大学，031803108
INCLUDE Irvine32.inc
.data
source  BYTE "ABCDEFGH",0
.const
str1 db "NO This Char!",0
str2 db "Found!",0
.code
main PROC
    mov edi,OFFSET source       ;EDI指向字符串
    mov al, 'F'                 ;检索字符F
    mov ecx,LENGTHOF source     ;设置检索计数器
    cld                         ;方向为正向
    repne scasb                 ;不相等则重复
    jnz quit                    ;若未发现字符则退出
    mov edx,OFFSET str2
    call writestring
    exit
quit:
    mov edx,OFFSET str1
    call writestring
    exit
main ENDP
END main
;SCASB将AL中的值与EDI寻址的一个字节进行比较
;SCASW将AX中的值与EDI寻址的一个字进行比较
;SCASD将EAX中的值与EDI寻址的一个双字进行比较
;REPNE前缀也能实现扫描，直到 AL/AX/EAX 与某个内存数值相等或者 ECX = 0