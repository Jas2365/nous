; isr asm
[bits 32]

extern isr_handler 

%macro ISR 1 
global isr%1
isr%1:
    cli
    push dword 0
    push dword %1
    pusha 
    mov ax, ds 
    ; push eax            ; save data segment 
    mov ax, 0x10        ; load kernel data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; push esp            ; pass pointer
    call isr_handler    ; call c handler
    ; add esp, 4            ; pop argument
    ; pop eax             ; restore data segment

    ; mov ds, ax 
    ; mov es, ax 
    ; mov fs, ax 
    ; mov gs, ax 

    popa

    add esp, 8          ; pop error code and int no
    sti
    iretd    
%endmacro

;===== Exceptions 0-31 =======
ISR  0   ; Divide by zero
ISR  1   ; Debug
ISR  2   ; Non Maskable Interrupt
ISR  3   ; Breakpoint
ISR  4   ; Overflow
ISR  5   ; Bound range exceeded
ISR  6   ; invalid opcode
ISR  7   ; Device not avaliable
ISR  8   ; Double fault
ISR  9   ; Coprocessor segment overrun
ISR  10  ; Ivalid TSS
ISR  11  ; Segment not present
ISR  12  ; Stack-segment fault
ISR  13  ; General protection fault
ISR  14  ; Page fault
ISR  15  ; Reserved
ISR  16  ; x87 floating point exception
ISR  17  ; Alignment check
ISR  18  ; Machine check
ISR  19  ; SIMD floating-point exception
ISR  20  ; Virtualization exception
ISR  21  ; 
ISR  22  ; 
ISR  23  ; 
ISR  24  ; 
ISR  25  ; 
ISR  26  ; 
ISR  27  ; 
ISR  28  ; 
ISR  29  ; 
ISR  30  ; 
ISR  31  ; 

; ======== Common isr handler =======
