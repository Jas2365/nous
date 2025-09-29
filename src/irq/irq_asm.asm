; irq asm
[bits 32]

extern irq_handler          ; C handler
extern pic_send_eoi         ; function to send eoi to pic
%macro IRQ 1 
    global irq%1
    irq%1:
        cli 
        pusha 
        mov ax, 0x10        ; kernel data segment
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        push dword %1       ; push irq number 
        call irq_handler 
            
        add esp, 4
        call pic_send_eoi

        popa 
        sti 
        iretd
%endmacro

; ==== Define IRQ0 - IRQ15 ======
IRQ 0   ; Timer
IRQ 1   ; Keyboard
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
IRQ 8
IRQ 9
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15