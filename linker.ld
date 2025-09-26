OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

SECTIONS {
  . = 0x100000;
  .multiboot : {
    KEEP(*(.multiboot))
  }
  .text : { *(.text) }
  .rodata : { *(.rodata) }
  .data : { *(.data) }
  .bss : {
    __bss_start = .; 
    *(.bss) 
    __bss_end = .;
    *(COMMON) 
    }
}