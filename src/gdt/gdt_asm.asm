; gdt.asm
[bits 32]

global gdt_flush
gdt_flush:
    lgdt [eax]  ; load gdt pointer

    mov ax, 0x10 ; data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush_done

.flush_done:
    ret
