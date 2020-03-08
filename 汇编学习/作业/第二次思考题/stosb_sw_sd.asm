;Code by 苏煜程，18级信息安全，福州大学，031803108
INCLUDE Irvine32.inc
.data
Count = 100
string1 BYTE Count DUP(?)
.code
main PROC
    mov al, 0ffh            ;要保存的数值
    mov edi,OFFSET string1  ;EDI指向目标字符串
    mov ecx,Count           ;字符计数器
    cld                     ;方向为正向
    rep stosb               ;用 AL 的内容实现填充
    exit
main ENDP
END main
;STOSB将AL中的内容存入由EDI中偏移量指向的内存位置
;STOSW将AX中的内容存入由EDI中偏移量指向的内存位置
;STOSD将EAX中的内容存入由EDI中偏移量指向的内存位置
;与REP前缀组合使用时，这些指令实现用同一个值填充字符串或数组的全部元素