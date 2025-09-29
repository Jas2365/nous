#include "pic.h"
#include "../idt/idt.h"
#include "../io/io.h"
#include "../constants/ports.h"

void pic_remap()
{
    uint8_t a1, a2;

    // save mask
    // a1 = inb(pic1_data_port);
    // a2 = inb(pic2_data_port);

    // start initialisation sequenc
    outb(pic1_cmd_port, pic_cmd_init);
    outb(pic2_cmd_port, pic_cmd_init);

    // set vector offset
    outb(pic1_data_port, pic_irq_base);
    outb(pic2_data_port, pic_irq_base + 8);

    // tell master pic about slave at irq2 (0000 0100)
    outb(pic1_data_port, 0x04);
    // tell slave pic its cascade identity (irq2)
    outb(pic2_data_port, 0x02);

    // set 8086 mode
    outb(pic1_data_port, pic_mode_8086);
    outb(pic2_data_port, pic_mode_8086);

    // restore save mask
    // outb(pic1_data_port, 0x0);
    // outb(pic2_data_port, 0x0);
    // // restore save mask
    outb(pic1_data_port, a1);
    outb(pic2_data_port, a2);
}