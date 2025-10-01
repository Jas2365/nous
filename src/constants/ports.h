#pragma once

// VGA i/o ports
#define vga_port_cmd 0x03d4
#define vga_port_data 0x03d5

// idt
#define idt_total_entries 256    // size
#define kernel_code_segment 0x08 // segment selector
#define idt_flag_present 0x80    // bit 7: set if the entry is valid
#define idt_flag_ring0 0x00      // bits 6-5: privilege level ( 00 = kernel )
#define idt_flag_ring3 0x60      // gits 6-5: privilege level ( 11 = user )
#define idt_flag_int_gate 0x0e   // bits 3-0: 32-bit interrupt gate

// combine flags
#define idt_flag_kernel (idt_flag_present | idt_flag_ring0 | idt_flag_int_gate)

// PIC ports
#define pic1_cmd_port 0x20
#define pic1_data_port 0x21

#define pic2_cmd_port 0xa0
#define pic2_data_port 0xa1

#define pic_eoi 0x20
#define pic_irq_base 0x20 // remapped irq based address

#define icw1_init 0x10
#define icw1_icw4 0x01
#define icw1_8086 0x01

#define pic_cmd_init (icw1_init | icw1_icw4)
#define pic_mode_8086 icw1_8086

// Keyboard ports
#define keyboard_data_port 0x60
#define keyboard_status_port 0x64
#define keyboard_irq 1
#define keyboard_int (pic_irq_base + keyboard_irq)

// Timer
#define pit_channel0 0x40
#define pit_command 0x43

// Memory
#define page_size 4096
#define max_memory 0x10000000
#define total_pages (max_memory / page_size)
