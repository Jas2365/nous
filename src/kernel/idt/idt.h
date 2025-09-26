#pragma once

#include "../std/int.h"
#include "../constants/ports.h"

#define idt_total_entries 256    // size
#define kernel_code_segment 0x08 // segment selector
#define idt_flag_present 0x80    // bit 7: set if the entry is valid
#define idt_flag_ring0 0x00      // bits 6-5: privilege level ( 00 = kernel )
#define idt_flag_ring3 0x60      // gits 6-5: privilege level ( 11 = user )
#define idt_flag_int_gate 0x0e   // bits 3-0: 32-bit interrupt gate

// combine flags
#define idt_flag_kernel (idt_flag_present | idt_flag_ring0 | idt_flag_int_gate)

// Packed structure (no paddings)
struct __attribute__((packed)) idt_entry
{
    uint16_t offset_low;  // lower 16 bits of isr address
    uint16_t selector;    // code segment
    uint8_t zero;         // always 0
    uint8_t type_attr;    // flags
    uint16_t offset_high; // upper 16 bits of isr address
};

struct __attribute__((packed)) idt_ptr
{
    uint16_t limit;
    uint32_t base;
};

void idt_init();
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void isr_handler_c(uint32_t int_no);