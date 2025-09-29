#include "gdt.h"
#include "../utils/bitmask.h"

struct gdt_entry gdt[gdt_entries];
struct gdt_ptr   gp;

extern void gdt_flush(uint32_t gdt_ptr);

static void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
    gdt[num].base_low       = (base & _16low);
    gdt[num].base_middle    = (base >> 16) & _8low;
    gdt[num].base_high      = (base >> 24) & _8low;
    
    gdt[num].limit_low      = (limit & _16low);
    gdt[num].granularity    = ((limit >> 16) & _4low);

    gdt[num].granularity   |= (gran & _4high);
    gdt[num].access         = access;
}


void gdt_init(void) {
    gp.limit = (sizeof(struct gdt_entry) * gdt_entries);
    gp.base = (uint32_t)&gdt;


    gdt_set_gate(0, 0, 0, 0, 0); // Null segment
    gdt_set_gate(1, 0, 0xffffffff, 0x9a, 0xcf); // Code segment
    gdt_set_gate(2, 0, 0xffffffff, 0x92, 0xcf); // Data segment

    gdt_flush((uint32_t)&gp);
}