include irvine32.inc
.data
Hnum dd ? ;定义行数
Lnum dd ? ;定义列数
inx dd ? ;目前位置x
iny dd ? ;目前位置y
enx dd ? ;终点位置x
eny dd ? ;终点位置y
indextmp dd ? ;坐标临时转换数据
endd dd ? ;保存检查结果
map dd '1','1','0','0','0','1','1','1',
       '1','0','0','1','1','1','1','1',
       '1','0','1','0','1','1','1','1',
       '1','0','0','0','1','1','1','1',
       '1','1','1','0','1','1','1','1',
       '0','1','1','0','0','0','0','0'
.code
main proc
    mov Hnum,6
    mov Lnum,8 
    mov inx,4
    mov iny,0
    mov enx,7
    mov eny,5

    ;call ToRun
    ;call ToTest
    call ToGo
	exit
main endp

ToSet proc ;把走过的地方置为1 
    pushad
    mov eax,iny
    push eax
    mov eax,inx
    push eax
    call IndexC
    mov ebx,indextmp
    lea edi,map
    mov eax,'1'
    mov dword ptr [edi+ebx*4],eax
    popad
    ret
ToSet endp

ToGo proc
    pushad
TGL1:
    call crlf
    call ToTest
    call Pmap
    call ToSet   
    call ToRun
    mov eax,inx
    cmp eax,enx
    JB TGL1
    JA TGL1
    mov eax,iny
    cmp eax,eny
    JB TGL1
    JA TGL1  
    call ToSet
    call crlf
    call ToTest
    call Pmap
    popad
    ret
ToGo endp

ToRun proc
    pushad
    ;先检查左边
    mov eax,iny
    push eax
    mov eax,inx
    inc eax
    push eax
    call IndexC
    call ToCheck
    mov eax,endd
    cmp eax,1
    JAE TRL1 ;是0可以走
    call ToLeft
    popad 
    ret
TRL1:   ;开始检查下边
    mov eax,iny
    inc eax
    push eax
    mov eax,inx
    push eax
    call IndexC
    call ToCheck
    mov eax,endd
    cmp eax,1
    JAE TRL2   
    call ToDown
    popad
    ret
TRL2:   ;开始检查右边
    mov eax,iny
    push eax
    mov eax,inx
    dec eax
    push eax
    call IndexC
    call ToCheck
    mov eax,endd
    cmp eax,1
    JAE TRL3
    call ToRight
    popad
    ret
TRL3: ;开始检查上边
    mov eax,iny
    dec eax
    push eax
    mov eax,inx
    push eax
    call IndexC
    call ToCheck
    mov eax,endd
    cmp eax,1
    JAE TRL4
    call ToUp
    popad
    ret
TRL4:
    popad
    ret
ToRun endp

ToCheck proc
    pushad
    mov ebx,indextmp
    lea edi,map
    mov eax,[edi+ebx*4]
    cmp eax,'1'
    JB TCL1 ;eax<1
    mov endd,1
    popad
    ret
TCL1:
    mov endd,0
    popad
    ret
ToCheck endp

ToLeft proc
    pushad
    mov eax,inx
    inc eax
    mov inx,eax
    popad
    ret
ToLeft endp

ToRight proc
    pushad
    mov eax,inx
    dec eax
    mov inx,eax
    popad
    ret
ToRight endp

ToUp proc
    pushad
    mov eax,iny
    dec eax
    mov iny,eax
    popad
    ret
ToUp endp

ToDown proc
    pushad
    mov eax,iny
    inc eax
    mov iny,eax
    popad
    ret
ToDown endp

IndexC proc X,Y
    pushad
    mov eax,Y
    mov ebx,Lnum
    mul ebx
    add eax,X
    mov indextmp,eax
    popad
    ret
IndexC endp

Pmap proc
    pushad
    lea esi,map
    mov ecx,Hnum   ;控制行
    mov edi,0   ;控制列
S1:
    mov eax,Hnum
    sub eax,ecx
    mov ebx,Lnum
    mul ebx
    mov ebx,eax
    add ebx,edi
    mov eax,[esi+ebx*4]
    call writechar
    mov eax,' '
    call writechar
    inc edi
    cmp edi,Lnum
    JB S1
    mov edi,0
    call crlf
    loop S1
    popad
    ret
Pmap endp

ToTest proc
    pushad
    mov eax,'X'
    call writechar
    mov eax,':'
    call writechar
    mov eax,inx
    call writedec
    mov eax,' '
    call writechar
    mov eax,'Y'
    call writechar
    mov eax,':'
    call writechar
    mov eax,iny
    call writedec
    call crlf
    popad
    ret
ToTest endp
end  main
