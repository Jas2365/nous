#pragma once

static inline void slow_down()
{
    for (volatile int j = 0; j < 10000000 / 6; j++)
        ;
    for (volatile int k = 0; k < 10000000 / 6; k++)
        ;
}