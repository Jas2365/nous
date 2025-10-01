#include "../debug/debug.h"
#include "../gdt/gdt.h"
#include "../idt/idt.h"
#include "../io/io.h"
#include "../keyboard/keyboard.h"
#include "../pic/pic.h"
#include "../pmm/pmm.h"
#include "../std/int.h"
#include "../timer/timer.h"
#include "../utils/loading.h"
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

  pmm_init(128 * 1024); // assume 128mb
  // mark first 1 mb as reserved (kernel + bios)

  pmm_mark_region_free(0x00100000, 127 * 1024 * 1024);

  // vga_print_info("before sti");
  asm volatile("sti");
  // vga_print_info("after sti");

  void *a = pmm_alloc_page();
  void *b = pmm_alloc_page();
  void *c = pmm_alloc_page();
  void *d = pmm_alloc_page();

  vga_print_info("Allocated Pages");
  vga_print_hex((uint32_t)a);
  vga_newline();
  vga_print_hex((uint32_t)b);
  vga_newline();
  vga_print_hex((uint32_t)c);
  vga_newline();
  vga_print_hex((uint32_t)d);
  vga_newline();

  while (1) {

    asm volatile("hlt");
  }
}

// uint32_t seconds = 0;
// uint32_t frame = 0;
// uint32_t last_tick = 0;
// uint32_t last_anim_tick = 0;

// uint32_t current_ticks = get_ticks();

// // update seconds every 1000 ms
// if (current_ticks - last_tick >= 100) {
//   last_tick = current_ticks;
//   seconds++;

//   vga_clear();
//   vga_print_info("TIME");
//   vga_print("Time in seconds: ");
//   vga_print_dec(seconds);
//   vga_print("  "); // overwrite old digits
//                    // }
//                    // // -- update loading every 100 ms
//                    // if (current_ticks - last_tick >= 10) {
//   last_anim_tick = current_ticks;
//   loading(frame);
//   frame = (frame + 1) % frames_size;
// }