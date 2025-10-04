#include "pic.h"
#include "../idt/idt.h"
#include "../io/io.h"
#include "../ports/ports.h"


void pic_remap(uint8_t offset1, uint8_t offset2) {
  uint8_t mask1, mask2;

  // save mask
  mask1 = inb(pic1_data_port);
  mask2 = inb(pic2_data_port);

  // start initialisation sequenc
  outb(pic1_cmd_port, pic_cmd_init);
  outb(pic2_cmd_port, pic_cmd_init);

  // set vector offset
  outb(pic1_data_port, offset1);
  outb(pic2_data_port, offset2);

  // tell master pic about slave at irq2 (0000 0100)
  outb(pic1_data_port, 4);
  // tell slave pic its cascade identity (irq2)
  outb(pic2_data_port, 2);

  // set 8086 mode
  outb(pic1_data_port, pic_mode_8086);
  outb(pic2_data_port, pic_mode_8086);

  // restore save mask
  outb(pic1_data_port, mask1);
  outb(pic2_data_port, mask2);
}