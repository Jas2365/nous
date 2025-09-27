#include "../std/int.h"
#include "../vga/vga.h"
#include "../idt/idt.h"

void kernel_main()
{

  vga_clear();
  vga_print_info("Initialising IDT...");
  idt_init();

  vga_print_info("IDT loaded successfully");

  vga_print_info("Nous Os kernel started");
  vga_print_warn("Keyboard not initialized yet");
  vga_print_error("Disk driver missing");

  vga_newline();
  vga_print("All systems nominal.");
  vga_newline();

  while (1)
  {
  }
}