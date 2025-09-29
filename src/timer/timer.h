#pragma once

#include "../std/int.h"

volatile uint32_t timer_ticks;
static uint32_t tick_count = 0;

void timer_init(uint32_t frequency);
inline static uint32_t get_ticks(void) { return timer_ticks; }