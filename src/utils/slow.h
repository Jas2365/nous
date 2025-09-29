#pragma once

static inline void slow_down() {
  for (volatile int j = 0; j < 1000000 / 2; j++)
    ;
  for (volatile int k = 0; k < 1000000 / 2; k++)
    ;
}