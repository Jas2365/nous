#include "../constants/ports.h"
#include "../io/io.h"
#include "../vga/vga.h"

void pic_send_eoi(uint8_t irq) {
  if (irq >= 8)
    outb(pic2_cmd_port, pic_eoi); // slave pic
  outb(pic1_cmd_port, pic_eoi);   // master pic
}

void irq_handler(uint32_t irq_num) {
  if (irq_num == 1) {
    vga_print_info("KEYBOARD IRQ FIRED");
  }
}