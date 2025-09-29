#include "vga.h"
#include "../io/io.h"
#include "../utils/slow.h"

static volatile uint16_t *vga_buffer = (uint16_t *)vga_address;
static size_t vga_row = 0;
static size_t vga_col = 0;
static uint8_t vga_color = 0x07; // light grey on black

// combine character + attribute byte

static inline uint16_t vga_entry(uint8_t c, uint8_t color) {
  return ((uint16_t)c | ((uint16_t)color << 8));
}

void vga_clear() {
  for (size_t y = 0; y < vga_height; y++) {
    for (size_t x = 0; x < vga_width; x++) {
      const size_t index = y * vga_width + x;
      vga_buffer[index] = vga_entry(' ', vga_color);
    }
  }
  vga_row = 0;
  vga_col = 0;
}

void vga_set_color(uint8_t fg, uint8_t bg) { vga_color = fg | bg << 4; }

void vga_putc(char c) {
  if (c == '\n') {
    vga_col = 0;
    vga_row++;

    if (vga_row == vga_height)
      vga_scroll();
    vga_update_cursor(vga_row, vga_col);
    return;
  } else if (c == '\t') {

    vga_col = (vga_col + 4) & ~(4 - 1);
    if (vga_col >= 80) {
      vga_col = 0;
      vga_row++;
    }
    if (vga_row == vga_height)
      vga_scroll();
    vga_update_cursor(vga_row, vga_col);
    return;
  } else if (c == '\b') {
    if (vga_col > 0)
      vga_col--;
    else if (vga_row > 0) {
      vga_row--;
      vga_col = 5;
    }
    vga_buffer[vga_row * 80 + vga_col] = (0x0f << 8) | ' '; // erase char
    if (vga_row == vga_height)
      vga_scroll();
    vga_update_cursor(vga_row, vga_col);
    return;
  }

  const size_t index = vga_row * vga_width + vga_col;
  vga_buffer[index] = vga_entry(c, vga_color);

  slow_down();

  if (++vga_col == vga_width) {
    vga_col = 0;
    if (++vga_row == vga_height)
      vga_scroll();
  }
  vga_update_cursor(vga_row, vga_col);
}

void vga_print(const char *str) {
  for (size_t i = 0; str[i] != '\0'; i++)
    vga_putc(str[i]);
}
void vga_newline() { vga_putc('\n'); }

char hex_digit(uint8_t nibble) {
  if (nibble < 10)
    return '0' + nibble;
  return 'A' + (nibble - 10);
}

void vga_print_hex_width(uint32_t val, uint8_t width) {
  vga_print("0x"); // prefix
  // print each nibble (4bits) from highest to lowest
  for (int i = (width - 1) * 4; i >= 0; i -= 4) {
    uint8_t nibble = (val >> i) & 0xf;
    vga_putc(hex_digit(nibble));
  }
}

void vga_print_hex(uint32_t val) {
  if (val < 0xf)
    vga_print_hex_width(val, 1);
  else if (val < 0xff)
    vga_print_hex_width(val, 2);

  else if (val < 0xfff)
    vga_print_hex_width(val, 3);

  else if (val < 0xffff)
    vga_print_hex_width(val, 4);

  else if (val < 0xfffff)
    vga_print_hex_width(val, 5);

  else if (val < 0xffffff)
    vga_print_hex_width(val, 6);
  else if (val < 0xfffffff)
    vga_print_hex_width(val, 7);
  else
    vga_print_hex_width(val, 8);
}

void vga_update_cursor(size_t row, size_t col) {
  uint16_t pos = row * vga_width + col;

  outb(vga_port_cmd, vga_cursor_low);
  outb(vga_port_data, (uint8_t)(pos & 0xff));
  outb(vga_port_cmd, vga_cursor_high);
  outb(vga_port_data, (uint8_t)((pos >> 8) & 0xff));
}

void vga_disable_cursor() {
  outb(vga_port_cmd, vga_cursor_start_reg);
  outb(vga_port_data, vga_cursor_disable);
}

void vga_enable_cursor(uint8_t start, uint8_t end) {
  outb(vga_port_cmd, vga_cursor_start_reg);
  outb(vga_port_data, (inb(vga_port_data) & vga_mask_top2_bits) | start);

  outb(vga_port_cmd, vga_cursor_end_reg);
  outb(vga_port_data, (inb(vga_port_data) & vga_mask_top3_bits) | end);
}

void vga_scroll() {
  // move each line up
  for (size_t y = 1; y < vga_height; y++) {
    for (size_t x = 0; x < vga_width; x++) {
      vga_buffer[(y - 1) * vga_width + x] = vga_buffer[y * vga_width + x];
    }
  }
  // clear last line
  for (size_t x = 0; x < vga_width; x++) {
    vga_buffer[(vga_height - 1) * vga_width + x] = vga_entry(' ', vga_color);
  }
  vga_row = vga_height - 1;
}

void vga_set_cursor(size_t row, size_t col) {
  if (row >= vga_height || col >= vga_width)
    return;
  vga_row = row;
  vga_col = col;
}

void vga_print_info(const char *msg) {
  uint8_t old_color = vga_color;
  vga_set_color(info_color, black_color);
  vga_print("[INFO]   ");
  vga_set_color(old_color & 0x0f, old_color >> 4);
  vga_print(msg);
  vga_newline();
}

void vga_print_warn(const char *msg) {
  uint8_t old_color = vga_color;
  vga_set_color(warn_color, black_color);
  vga_print("[WARN]   ");
  vga_set_color(old_color & 0x0f, old_color >> 4);
  vga_print(msg);
  vga_newline();
}

void vga_print_error(const char *msg) {
  uint8_t old_color = vga_color;
  vga_set_color(error_color, black_color);
  vga_print("[ERROR]  ");
  vga_set_color(old_color & 0x0f, old_color >> 4);
  vga_print(msg);
  vga_newline();
}
