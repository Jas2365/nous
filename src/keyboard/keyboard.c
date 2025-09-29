#include "keyboard.h"
#include "../idt/idt.h"
#include "../vga/vga.h"
#include "../io/io.h"

const char scancode_map[128] = {
    0, 27, '1', '2', '3', '4'
};

void keyboard_init()
{
    uint8_t mask = inb(pic1_data_port);
    mask &= ~(1 << keyboard_irq); // clear bit 1 enable irq
    outb(pic1_data_port, mask);
}

uint8_t keyboard_read_scan()
{
    return inb(keyboard_data_port);
}

void keyboard_handler_c(uint32_t int_no)
{
    uint8_t scancode = keyboard_read_scan();

    vga_print_info("key pressed");
    if(scancode & 0x80)
     return;
    
    char c = scancode_map[scancode];
    if(c){
        vga_putc(c);
    }

    outb(pic1_cmd_port, pic_eoi);
}