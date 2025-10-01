#pragma once

#include "../std/int.h"
#include "../timer/timer.h"
#include "../vga/vga.h"

#define frames_size 11
static const char *loading_bar[frames_size] = {
    "[          ]", "[=         ]", "[==        ]", "[===       ]",
    "[====      ]", "[=====     ]", "[======    ]", "[=======   ]",
    "[========  ]", "[========= ]", "[==========]",
};

inline static void loading(uint16_t frame) {
  if (frame > frames_size)
    frame = 0;
  vga_print(loading_bar[frame]);
}
