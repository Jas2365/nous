; isr asm
[bits 32]

extern isr_handler 

%macro ISR_NOERR 1 
    global isr%1
    isr%1:
        cli
        push dword 0        ; push dummy error code for consistency
        push dword %1       ; push interrupt number
        jmp isr_common_stub
%endmacro

%macro ISR_ERR 1 
    global isr%1
    isr%1:
        cli
        push dword %1       ; interrupt number 
        jmp isr_common_stub
%endmacro

;===== Exceptions 0-31 =======
ISR_NOERR   0   ; Divide by zero
ISR_NOERR   1   ; Debug
ISR_NOERR   2   ; NMI
ISR_NOERR   3   ; Breakpoint
ISR_NOERR   4   ; Overflow
ISR_NOERR   5   ; Bound range exceeded
ISR_NOERR   6   ; invalid opcode
ISR_NOERR   7   ; Device not avaliable
ISR_ERR     8   ; Double fault
ISR_NOERR   9   ; Coprocessor segment overrun
ISR_ERR     10  ; Ivalid TSS
ISR_ERR     11  ; Segment not present
ISR_ERR     12  ; Stack-segment fault
ISR_ERR     13  ; General protection fault
ISR_ERR     14  ; Page fault
ISR_NOERR   15  ; Reserved
ISR_NOERR   16  ; x87 floating point exception
ISR_ERR     17  ; Alignment check
ISR_NOERR   18  ; Machine check
ISR_NOERR   19  ; SIMD floating-point exception
ISR_NOERR   20  ; Virtualization exception
ISR_NOERR   21  ; 
ISR_NOERR   22  ; 
ISR_NOERR   23  ; 
ISR_NOERR   24  ; 
ISR_NOERR   25  ; 
ISR_NOERR   26  ; 
ISR_NOERR   27  ; 
ISR_NOERR   28  ; 
ISR_NOERR   29  ; 
ISR_NOERR   30  ; 
ISR_NOERR   31  ; 

; ======== Common isr handler =======
global isr_common_stub
isr_common_stub:
    pusha 
    mov ax, ds 
    push eax            ; save data segment 
    mov ax, 0x10        ; load kernel data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp            ; pass pointer
    call isr_handler    ; call c handler
    add esp, 4          ; pop argument
    pop eax             ; restore data segment

    mov ds, ax 
    mov es, ax 
    mov fs, ax 
    mov gs, ax 

    popa

    add esp, 8          ; pop error code and int no
    sti
    iretd    