#include "keyboard.h"
#include "../idt/idt.h"
#include "../io/io.h"
#include "../vga/vga.h"

const char keymap[128] = {
    0,
    27,
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    '\b', // backspace
    '\t' /* Tab */,
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '[',
    ']',
    '\n', // Enter
    0,    /* Control */
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    '\'',
    '`',
    0, /* Left Shift */
    '\\',
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    ',',
    '.',
    '/',
    0, /* Right Shift */
    '*',
    0,   /* Alt */
    ' ', /* Spacebar */
    0,   /* Caps lock */
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,

};

static int e0_flag = 0;
void keyboard_init() {
  uint8_t mask = inb(pic1_data_port);
  mask &= ~(1 << keyboard_irq); // clear bit 1 enable irq
  outb(pic1_data_port, mask);
}

uint8_t keyboard_read_scan() { return inb(keyboard_data_port); }

void keyboard_handler_c(void) {
  uint8_t scancode = keyboard_read_scan();

  if (scancode == 0xe0) {
    e0_flag = 1;
  }
  if (e0_flag) {
    switch (scancode) {
    case 0x4b:
      vga_move_cursor_left();
      break;

    case 0x4D:
      vga_move_cursor_right();
      break;
    case 0x48:
      vga_move_cursor_up();
      break;
    case 0x50:
      vga_move_cursor_down();
      break;

    default:
      break;
    }
  }

  if (!(scancode & 0x80)) // key is pressed not released
  {
    // vga_print("scancode: ");
    // vga_print_hex(scancode);
    // vga_newline();
    char c = keymap[scancode];

    if (c) {
      vga_putc(c);
    }
  }
}