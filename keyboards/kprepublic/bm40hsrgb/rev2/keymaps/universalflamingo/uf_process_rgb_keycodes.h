
#pragma once

#include <stdbool.h>
#include <stdint.h>

// clang-format on

#include "config.h"

// clang-format off

#include "action.h"


bool uf_process_rgb_keycodes(const uint16_t keycode, const keyrecord_t *record);
