#pragma once

#include "../ports/ports.h"
#include "../std/int.h"

// Packed structure (no paddings)
struct idt_entry {
  uint16_t offset_low;  // lower 16 bits of isr address
  uint16_t selector;    // code segment
  uint8_t zero;         // always 0
  uint8_t type_attr;    // flags
  uint16_t offset_high; // upper 16 bits of isr address
} __attribute__((packed));

struct idt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

extern struct idt_entry idt[idt_total_entries];
extern struct idt_ptr idt_descriptor;

void idt_init();
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);