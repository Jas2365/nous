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

const char *exception_message[] = {
    "Divide by zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound range exceeded",
    "invalid opcode",
    "Device not avaliable",
    "Double fault",
    "Coprocessor segment overrun",
    "Ivalid TSS",
    "Segment not present",
    "Stack-segment fault",
    "General protection fault",
    "Page fault",
    "Reserved",
    "x87 floating point exception",
    "Alignment check",
    "Machine check",
    "SIMD floating-point exception",
    "Virtualization exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};
void isr_handler(uint32_t isr) {

  vga_print_info("Received interrupt: ");
  vga_print_hex(isr);
  vga_newline();

  // if its a hardware IRQ, send EOI
  if (isr < 32) {
    vga_print_error(exception_message[isr]);
  } else {
    vga_print_error("Unknown Exception");
  }
  vga_print_info("System Halted");
  for (;;)
    asm volatile("hlt");
}
