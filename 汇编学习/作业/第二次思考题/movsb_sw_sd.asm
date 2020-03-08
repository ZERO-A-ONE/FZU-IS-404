;Code by 苏煜程，18级信息安全，福州大学，031803108
INCLUDE Irvine32.inc
.data
source  db 'helloworld',0
target  db 11 dup(?)
.code
main PROC
    cld                        ;清除方向标志位(CLD正/STD反）
    mov esi, OFFSET source     ; ESI 指向源串
    mov edi, OFFSET target     ; EDI 执行目的串
    mov ecx, LENGTHOF source   ;计数器赋值为11
    rep movsb                  
	mov edx,OFFSET target      
    call writestring
    exit
main ENDP
END main
;MOVSB传送（复制）字节,ESI和 EDI增加或减少1
;MOVSW传送（复制）字,ESI和 EDI增加或减少2
;MOVSD传送（复制）双字,,ESI和 EDI增加或减少4