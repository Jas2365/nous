#include "../debug/debug.h"
#include "../gdt/gdt.h"
#include "../idt/idt.h"
#include "../io/io.h"
#include "../keyboard/keyboard.h"
#include "../pic/pic.h"
#include "../std/int.h"
#include "../timer/timer.h"
#include "../utils/slow.h"
#include "../vga/vga.h"

void kernel_main() {
  vga_clear();

  vga_print_info("Initialising GDT");
  gdt_init();
  // vga_print_info("GDT loaded successfully");

  vga_print_info("Initialising IDT");
  idt_init();
  // vga_print_info("IDT loaded successfully");

  vga_print_info("Remapping PIC");
  pic_remap(0x20, 0x28);
  // vga_print_info("PIC remapped");

  vga_print_info("Initialising Keyboard");
  keyboard_init();
  // vga_print_info("Keyboard loaded successfully");

  vga_print_info("Initialising Timer");
  timer_init(100);
  // vga_print_info("printing...");

  // __asm__ volatile ("int $0x20");

  // vga_print_info("before sti");
  asm volatile("sti");
  // vga_print_info("after sti");

  vga_print_info("Kernel running with timer irq0.");

  while (1) {
    if (get_ticks() % 100 == 0) {
      vga_print("=>");
    }
    asm volatile("hlt");
  }

  // vga_print("irq1: ");
  // vga_print_hex((uint32_t)irq1);
  // vga_newline();

  // vga_print("idt 33 h:");
  // vga_print_hex(idt[33].offset_high);
  // vga_newline();
  // vga_print("idt 33 l:");
  // vga_print_hex(idt[33].offset_low);
  // vga_newline();

  // while(1){
  // isr_handler_c(keyboard_int);
  // }

  //   vga_newline();

  //   vga_print("keyboard port deciman 60: ");
  //   sc = inb(0x64);
  //   vga_print_hex(sc);

  // outb(pic1_data_port, 0xff);
  // outb(pic2_data_port, 0xff);

  // vga_print_hex(0x3);
  // vga_newline();
  // vga_print_hex(0x23);
  // vga_newline();
  // vga_print_hex(0x233);
  // vga_newline();
  // vga_print_hex(0x2333);
  // vga_newline();
  // vga_print_hex(0x23443);
  // vga_newline();

  // vga_print_info("Nous Os kernel started");
  // vga_print_warn("Keyboard not initialized yet");
  // vga_print_error("Disk driver missing");

  // vga_newline();
  // vga_print("All systems nominal.");
  // vga_newline();

  // uint32_t test = 0xbeef;

  // vga_print_hex8(test);
  // vga_newline();
  // vga_print_hex16(test);
  // vga_newline();
  // vga_print_hex32(test);
  // vga_newline();
}