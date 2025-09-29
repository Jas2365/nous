#include "../idt/idt.h"
#include "../vga/vga.h"
#include "../io/io.h"
#include "../constants/ports.h"
#include "../keyboard/keyboard.h"

void isr_handler_c(uint32_t int_no)
{
    if (int_no == keyboard_int)
    {
        keyboard_handler_c(int_no);
        return;
    }

    vga_print_info("Received interrupt: ");
    vga_print_hex32(int_no);
    vga_newline();

    // if its a hardware IRQ, send EOI
    if (int_no >= pic_irq_base && int_no < pic_irq_base + 16)
    {
        if (int_no >= pic_irq_base + 8)
        {
            outb(pic2_cmd_port, pic_eoi);
        }
        outb(pic1_cmd_port, pic_eoi);
    }
}
