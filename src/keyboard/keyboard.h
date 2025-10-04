_Pragma("once");

#include "../ports/ports.h"
#include "../std/int.h"

void keyboard_init();
uint8_t keyboard_read_scan();
void keyboard_handler_c(void);