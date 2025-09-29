;assume假设某一段寄存器和程序中的某一个用segment-ends定义的段相对应
;标号指代一个内存地址
assume cs:codesg        
      
;segment和ends成对使用的伪指令，定义一个段
;段名 segment
;段名 ends
;汇编程序中至少有一个段
codesg segment   
s:mov ax,bx     ;mov ax,bx的机器码占2个字节
    mov si,offset s
    mov di,offset s0
    mov ax,cs:si



codesg ends
end
;end汇编程序的结束标志
