; section .note.GNU-stack,"",@progbits
section .multiboot
align 4
magic equ 0x1badb002
flags equ 0x00000000 
checksum equ -(magic + flags)

dd magic 
dd flags 
dd checksum

section .text
global start 
extern kernel_main
start:
	call kernel_main

.hang:
	cli 
	hlt 
	jmp .hang

; section .text
; [bits 16]
; [org 0x7c00]
; start:
; 	cli
; 	xor ax, ax 
; 	mov ds, ax
; 	mov es, ax
; 	mov ss, ax
; 	mov sp, 0x7c00 

; 	lgdt [gdt_descriptor]
; 	mov eax, cr0
; 	or eax, 1 
; 	mov cr0, eax 
; 	jmp code_seg:init_pm 
	
; [bits 32]

; init_pm:
; 	mov ax, data_seg 
; 	mov ds, ax 
; 	mov es, ax 
; 	mov ss, ax 
; 	mov esp, 0x90000

; 	extern kernel_main
; 	call kernel_main
	
; .hang:
; 	hlt
; 	jmp .hang

; gdt_start:
; gdt_null: dq 0
; gdt_code: dq 0x00cf9a000000ffff
; gdt_data: dq 0x00cf92000000ffff
; gdt_end:

; gdt_descriptor:
; 	dw gdt_end - gdt_start -1
; 	dd gdt_start

; code_seg equ 0x08
; data_seg equ 0x10

; times 510-($-$$) db 0
; dw 0xaa55