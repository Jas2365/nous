#pragma once

#include "../ports/ports.h"
#include "../std/int.h"

typedef struct {
  uint64_t base_addr;
  uint64_t length;
  uint32_t type; // 1 = useable, other = reserved
} __attribute__((packed)) mem_map_entry_t;

static uint8_t bitmap[total_pages / 8];

static inline void set_bit(size_t idx) { bitmap[idx / 8] |= (1 << (idx % 8)); }
static inline void clear_bit(size_t idx) {
  bitmap[idx / 8] &= ~(1 << (idx % 8));
}
static inline int test_bit(size_t idx) {
  return bitmap[idx / 8] & (1 << (idx % 8));
}

void pmm_init(uint32_t mem_size_kb);
void pmm_mark_region_free(uint64_t base, uint64_t length);
void *pmm_alloc_page();
void pmm_free_page(void *addr);
