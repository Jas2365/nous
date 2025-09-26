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
