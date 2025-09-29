#include "../constants/ports.h"
#include "../idt/idt.h"
#include "../io/io.h"
#include "../keyboard/keyboard.h"
#include "../vga/vga.h"

struct _registers {
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, usersp, ss;
};

void isr_handler(struct _registers *r) {

  vga_print_info("Received interrupt: ");
  vga_print_hex32(r->int_no);
  vga_newline();

  // if its a hardware IRQ, send EOI
  if (r->int_no < 32) {
    vga_print_error("CPU exception haliting.");
    for (;;)
      asm volatile("hlt");
  }
}
