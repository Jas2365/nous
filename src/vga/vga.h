#pragma once
#include "../std/int.h"
#include "../constants/ports.h"

// VGA text mode constants
#define vga_address 0xb8000
#define vga_width 80
#define vga_height 25

// VGA cursor registers
#define vga_cursor_start_reg 0x0a
#define vga_cursor_end_reg 0x0b
#define vga_cursor_high 0x0e
#define vga_cursor_low 0x0f

#define vga_cursor_disable 0x20 // bit 5 = 1 disables cursor
#define vga_mask_top2_bits 0xc0 // 1100 0000
#define vga_mask_top3_bits 0xe0 // 1110 0000

enum VGA_COLOR
{
  VGA_BLACK = 0,
  VGA_BLUE = 1,
  VGA_GREEN = 2,
  VGA_CYAN = 3,
  VGA_RED = 4,
  VGA_MAGENTA = 5,
  VGA_BROWN = 6,
  VGA_LIGHT_GREY = 7,
  VGA_DARK_GREY = 8,
  VGA_LIGHT_BLUE = 9,
  VGA_LIGHT_GREEN = 10,
  VGA_LIGHT_CYAN = 11,
  VGA_LIGHT_RED = 12,
  VGA_LIGHT_MAGENTA = 13,
  VGA_LIGHT_BROWN = 14,
  VGA_WHITE = 15
};

#define info_color VGA_LIGHT_GREEN
#define warn_color VGA_LIGHT_BROWN
#define error_color VGA_LIGHT_RED

#define black_color VGA_BLACK

// function prototypes
void vga_clear();
void vga_set_color(uint8_t fg, uint8_t bg);
void vga_putc(char c);
void vga_print(const char *str);
void vga_newline();
char hex_digit(uint8_t nibble);
void vga_print_hex_width(uint32_t val, uint8_t width);
static inline void vga_print_hex8(uint8_t val) { vga_print_hex_width(val, 2); }
static inline void vga_print_hex16(uint16_t val) { vga_print_hex_width(val, 4); }
static inline void vga_print_hex32(uint32_t val) { vga_print_hex_width(val, 8); }
void vga_print_hex(uint32_t val);
void vga_update_cursor(size_t row, size_t col);
void vga_disable_cursor();
void vga_enable_cursor(uint8_t start, uint8_t end);

void vga_scroll();
void vga_set_cursor(size_t row, size_t col);
void vga_print_info(const char *msg);
void vga_print_warn(const char *msg);
void vga_print_error(const char *msg);
