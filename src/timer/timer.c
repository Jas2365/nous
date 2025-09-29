#include "../constants/ports.h"
#include "../io/io.h"
#include "../std/int.h"

void timer_init(uint32_t frequency) {
  uint32_t divisor = 1193180 / frequency;    // pit input clock is 1.19318 MHz
  outb(pit_command, 0x36);                   // Channel 0, lobyte/hibyte, mode 3
  outb(pit_channel0, divisor & 0xff);        // low byte
  outb(pit_channel0, (divisor >> 8) & 0xff); // high byte
}