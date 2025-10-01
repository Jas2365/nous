#include "pmm.h"
#include "../std/def.h"

void pmm_init(uint32_t mem_size_kb) {
  size_t total_ps = (mem_size_kb * 1024) / page_size;
  for (size_t i = 0; i < total_ps / 8; i++)
    bitmap[i] = 0xff;
}
void pmm_mark_region_free(uint64_t base, uint64_t length) {
  size_t start = base / page_size;
  size_t end = (base + length) / page_size;

  for (size_t i = start; i < end; i++)
    clear_bit(i);
}
void *pmm_alloc_page() {
  for (size_t i = 0; i < total_pages; i++) {
    if (!test_bit(i)) {
      set_bit(i);
      return (void *)(i * page_size);
    }
  }
  return NULL; // out of memory
}

void pmm_free_page(void *addr) {
  size_t idx = (size_t)addr / page_size;
  clear_bit(idx);
}