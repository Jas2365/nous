#include "../io/io.h"
#include "../keyboard/keyboard.h"
#include "../ports/ports.h"
#include "../regs/regs.h"
#include "../vga/vga.h"

enum IRQ { TIMER = 0, KEYBOARD = 1, PAGE_FAULT = 14 };

void pic_send_eoi(uint8_t irq) {
  if (irq >= 8)
    outb(pic2_cmd_port, pic_eoi); // slave pic
  outb(pic1_cmd_port, pic_eoi);   // master pic
}

extern volatile uint32_t timer_ticks;

static inline uint32_t read_cr2(void) {
  uint32_t val;
  asm volatile("mov %%cr2, %0" : "=r"(val));
  return val;
}

void irq_handler(struct registers *r) {
  uint32_t irq = r->int_no;
  switch (irq) {
  case TIMER: // timer
    timer_ticks++;
    break;

  case KEYBOARD: // keyboard
    keyboard_handler_c();
    break;

  case PAGE_FAULT:
    uint32_t cr2 = read_cr2();
    vga_print_error("[PAGE FAULT] addr = ");
    vga_print_hex(cr2);
    vga_print(", err = ");
    vga_print_hex(r->err_code);
    vga_newline();
    vga_print_info("Halting");
    for (;;)
      asm volatile("hlt");
    break;

  default:
    break;
  }
  pic_send_eoi(irq);
}