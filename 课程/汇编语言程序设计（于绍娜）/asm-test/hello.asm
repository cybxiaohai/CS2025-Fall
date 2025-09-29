;hello.asm -Windows 控制台输出 "Hello, World!"
bits 64

extern ExitProcess
extern GetStdHandle
extern WriteConsoleA

section .data
    msg db 'Hello,World!',10,0  ; 输出字符串，10 是换行符;  0 是字符串结束符
    msg_len equ $ - msg -1        ; 计算字符串长度 (不包括结束符)

section .bss
    written resd 1               ; 用于存储写入的字符数 

section .text
    global main

main:
    ;获取标准输出句柄（STD_OUTPUT_HANDLE = -11）
    mov rcx, -11
    call GetStdHandle

    ;调用 WriteConsoleA 输出字符串
    mov rcx,rax          ; hConsoleOutput
    mov rdx, msg         ; lpBuffer
    mov r8,msg_len     ; nNumberOfCharsToWrite
    mov r9, written      ; lpNumberOfCharsWritten
    sub rsp,32        ; 为调用保留栈空间
    mov qword[rsp],0 ; 第五个参数，保留为 NULL
    call WriteConsoleA

    ;调用 ExitProcess 退出程序
    mov rcx,0
    call ExitProcess
