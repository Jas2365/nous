#include "../constants/ports.h"
#include "../io/io.h"
#include "../keyboard/keyboard.h"
#include "../vga/vga.h"

void pic_send_eoi(uint8_t irq) {
  if (irq >= 8)
    outb(pic2_cmd_port, pic_eoi); // slave pic
  outb(pic1_cmd_port, pic_eoi);   // master pic
}

extern volatile uint32_t timer_ticks;

<<<<<<< HEAD
=======
static inline uint32_t read_cr2(void) {
  uint32_t val;
  asm volatile("mov %%cr2, %0" : "=r"(val));
  return val;
}

>>>>>>> 22dc1bd (working irq and isr)
void irq_handler(uint32_t irq) {
  switch (irq) {
  case 0:
    timer_ticks++;
    break;

  case 1:
    keyboard_handler_c();
    break;

<<<<<<< HEAD
=======
  case PAGE_FAULT:
    uint32_t cr2 = read_cr2();
    vga_print_error("[PAGE FAULT] addr = ");
    vga_print_hex(cr2);
    vga_newline();
    vga_print_info("Halting");
    for (;;)
      asm volatile("hlt");
    break;

>>>>>>> 22dc1bd (working irq and isr)
  default:
    break;
  }
  pic_send_eoi(irq);
}