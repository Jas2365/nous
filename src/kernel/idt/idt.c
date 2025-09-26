#include "idt.h"
#include "../io/io.h"
#include "../utils/bitmask.h"
#include "../vga/vga.h"

static struct idt_entry idt[idt_total_entries];
static struct idt_ptr idt_descriptor;

extern void idt_load();

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt[num].offset_high = base & _16low;
    idt[num].selector = sel;
    idt[num].zero = 0;
    idt[num].type_attr = flags;
    idt[num].offset_high = (base >> 16) & _16low;
}

void idt_init()
{
    idt_descriptor.limit - sizeof(struct idt_entry) * idt_total_entries - 1;
    idt_descriptor.base = (uint32_t)&idt;

    for (int i = 0; i < idt_total_entries - 1; i++)
    {
        idt_set_gate(i, 0, 0, 0);
    }

    // cpu exceptions 0-31
    idt_set_gate(0, (uint32_t)isr0, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(1, (uint32_t)isr1, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(2, (uint32_t)isr2, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(3, (uint32_t)isr3, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(4, (uint32_t)isr4, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(5, (uint32_t)isr5, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(6, (uint32_t)isr6, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(7, (uint32_t)isr7, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(8, (uint32_t)isr8, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(9, (uint32_t)isr9, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(10, (uint32_t)isr10, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(11, (uint32_t)isr11, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(12, (uint32_t)isr12, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(13, (uint32_t)isr13, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(14, (uint32_t)isr14, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(15, (uint32_t)isr15, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(16, (uint32_t)isr16, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(17, (uint32_t)isr17, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(18, (uint32_t)isr18, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(19, (uint32_t)isr19, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(20, (uint32_t)isr20, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(21, (uint32_t)isr21, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(22, (uint32_t)isr22, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(23, (uint32_t)isr23, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(24, (uint32_t)isr24, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(25, (uint32_t)isr25, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(26, (uint32_t)isr26, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(27, (uint32_t)isr27, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(28, (uint32_t)isr28, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(30, (uint32_t)isr30, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(31, (uint32_t)isr31, kernel_code_segment, idt_flag_kernel);

    // iqr 32 - 47
    idt_set_gate(0, (uint32_t)irq0, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(1, (uint32_t)irq1, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(2, (uint32_t)irq2, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(3, (uint32_t)irq3, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(4, (uint32_t)irq4, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(5, (uint32_t)irq5, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(6, (uint32_t)irq6, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(7, (uint32_t)irq7, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(8, (uint32_t)irq8, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(9, (uint32_t)irq9, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(10, (uint32_t)irq10, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(11, (uint32_t)irq11, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(12, (uint32_t)irq12, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(13, (uint32_t)irq13, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(14, (uint32_t)irq14, kernel_code_segment, idt_flag_kernel);
    idt_set_gate(15, (uint32_t)irq15, kernel_code_segment, idt_flag_kernel);

    idt_load((uint32_t)&idt_descriptor);
}
