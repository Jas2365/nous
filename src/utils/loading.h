#pragma once

#include "../std/int.h"
#include "../timer/timer.h"
#include "../vga/vga.h"

inline static void loading(uint32_t percentage) {
  const int boar_width = 50;

  int filled = (percentage * boar_width) / 100;
  vga_putc('[');
  for (int i = 0; i < boar_width; i++) {
    vga_putc(i < filled ? 219 : ' ');
  }
  vga_putc(']');
  vga_putc(' ');
  vga_print_dec(percentage);
  vga_putc('%');
  vga_newline();
}
