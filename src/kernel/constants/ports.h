#pragma once

// VGA i/o ports
#define vga_port_cmd 0x03d4
#define vga_port_data 0x03d5

// PIC ports
#define pic1_cmd_port 0x20
#define pic1_data_port 0x21

#define pic2_cmd_port 0xa0
#define pic2_data_port 0xa1

#define pic_cmd_init 0x11
#define pic_mode_8086 0x01

#define pic_eoi 0x20
#define pic_irq_base 0x20 // remapped irq based address