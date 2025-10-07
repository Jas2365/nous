#include "flat_memory.h"

static uint32_t heap_ptr = heap_start;
void *kmalloc(uint32_t size) {
  uint32_t addr = heap_ptr;

  heap_ptr += size;
  if (heap_ptr > heap_start + heap_size)
    return 0;
  return (void *)addr;
}