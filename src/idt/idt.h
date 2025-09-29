#pragma once

#include "../std/int.h"
#include "../constants/ports.h"

// Packed structure (no paddings)
struct idt_entry
{
    uint16_t offset_low;  // lower 16 bits of isr address
    uint16_t selector;    // code segment
    uint8_t zero;         // always 0
    uint8_t type_attr;    // flags
    uint16_t offset_high; // upper 16 bits of isr address
}__attribute__((packed));

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

extern struct idt_entry idt[idt_total_entries];
extern struct idt_ptr idt_descriptor;

// static inline void idt_load(void* base, uint16_t size){
//     struct idt_ptr idt_desc;
//     idt_desc.limit = size -1;
//     idt_desc.base = (uint32_t)base;
//     __asm__ volatile ("lidt %0" : : "m"(idt_desc));
// }

void idt_init();
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void isr_handler_c(uint32_t int_no);