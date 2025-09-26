

global idt_load
idt_load:
    lidt [eax]
    ret
    
[bits 32]

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr30
global isr31

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

extern isr_handler_c ; c handler

; generic isr macro to save state and call c
%macro isr_stub 1
global %1
%1:
    pusha
    push ds
    push es 
    push fs 
    push gs 
    
    mov ax, 0x10                ; kernel data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push %1                     ; Push interrypt number 
    call isr_handler_c           ; call c handler

    add esp, 4                  ; clean up pushed interrupt number
    
    pop gs 
    pop fs 
    pop es 
    pop ds 
    popa 

    iretd                       ; return from interrupt 
%endmacro 

isr_stub isr0
isr_stub isr1
isr_stub isr2
isr_stub isr3
isr_stub isr4
isr_stub isr5
isr_stub isr6
isr_stub isr7
isr_stub isr8
isr_stub isr9
isr_stub isr10
isr_stub isr11
isr_stub isr12
isr_stub isr13
isr_stub isr14
isr_stub isr15
isr_stub isr16
isr_stub isr17
isr_stub isr18
isr_stub isr19
isr_stub isr20
isr_stub isr21
isr_stub isr22
isr_stub isr23
isr_stub isr24
isr_stub isr25
isr_stub isr26
isr_stub isr27
isr_stub isr28
isr_stub isr30
isr_stub isr31

isr_stub irq0
isr_stub irq1
isr_stub irq2
isr_stub irq3
isr_stub irq4
isr_stub irq5
isr_stub irq6
isr_stub irq7
isr_stub irq8
isr_stub irq9
isr_stub irq10
isr_stub irq11
isr_stub irq12
isr_stub irq13
isr_stub irq14
isr_stub irq15
