#pragma once

#include "../constants/ports.h"
#include "../io/io.h"
#include "../vga/vga.h"

static inline void test_run() { vga_print_info("Running"); }

static inline void unmask_timer_irq(void) {
  outb(pic1_data_port, 0xfe);
  outb(pic2_data_port, 0xff);
}

static inline void enable_interrupts(void) { __asm__ volatile("sti"); }
