#include "../debug/debug.h"
#include "../flat_memory/flat_memory.h"
#include "../gdt/gdt.h"
#include "../idt/idt.h"
#include "../io/io.h"
#include "../keyboard/keyboard.h"
#include "../pic/pic.h"
#include "../pmm/pmm.h"
#include "../std/int.h"
#include "../timer/timer.h"
#include "../utils/slow.h"
#include "../vga/vga.h"

void init_everything() {
  vga_clear();

  // vga_print_info("Initialising GDT");
  gdt_init();
  // vga_print_info("GDT loaded successfully");

  // vga_print_info("Initialising IDT");
  idt_init();
  // vga_print_info("IDT loaded successfully");

  // vga_print_info("Remapping PIC");
  pic_remap(0x20, 0x28);
  // vga_print_info("PIC remapped");

  // vga_print_info("Initialising Keyboard");
  keyboard_init();
  // vga_print_info("Keyboard loaded successfully");

  // vga_print_info("Initialising Timer");
  timer_init(100);

  // vga_print_info("printing...");

  pmm_init(128 * 1024); // assume 128mb
  // mark first 1 mb as reserved (kernel + bios)

  pmm_mark_region_free(0x00100000, 127 * 1024 * 1024);

  // vga_print_info("before sti");
  asm volatile("sti");
  // vga_print_info("after sti");
}

void kernel_main() {

  init_everything();

  while (1) {
    asm volatile("hlt");
  }
}
