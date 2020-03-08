;Code by 苏煜程，18级信息安全，福州大学，031803108
INCLUDE Irvine32.inc
.data
source DWORD 1000h
target DWORD 5678h
.const
str1 db "source > target",0
str2 db "source <= target",0
.code
main PROC
    mov esi,OFFSET source
    mov edi,OFFSET target
    cmpsd                 ;比较双字
    ja L1                 ;若 source > target 则跳转
    mov edx,OFFSET str2
    call writestring
    exit
L1:
    mov edx,OFFSET str1
    call writestring
    exit
main ENDP
END main
;CMPSB比较字节
;CMPSW比较字
;CMPSD比较双字