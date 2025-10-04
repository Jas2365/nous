#include "../io/io.h"
#include "../keyboard/keyboard.h"
#include "../ports/ports.h"
#include "../vga/vga.h"


void pic_send_eoi(uint8_t irq) {
  if (irq >= 8)
    outb(pic2_cmd_port, pic_eoi); // slave pic
  outb(pic1_cmd_port, pic_eoi);   // master pic
}

extern volatile uint32_t timer_ticks;

void irq_handler(uint32_t irq) {
  switch (irq) {
  case 0:
    timer_ticks++;
    break;

  case 1:
    keyboard_handler_c();
    break;

  default:
    break;
  }
  pic_send_eoi(irq);
}