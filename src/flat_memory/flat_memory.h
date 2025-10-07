_Pragma("once");

#include "../std/int.h"
#include "../vga/vga.h"

#define heap_start 0x01000000
#define heap_size 0x01000000

void *kmalloc(uint32_t size);
