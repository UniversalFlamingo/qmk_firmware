#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "action.h"

#ifndef UF_AUTOCORRECT_DELAY
#  define UF_AUTOCORRECT_DELAY 20  // ms
#endif

bool uf_autocorrect_process_record(uint16_t keycode, keyrecord_t *record);

void uf_autocorrect_post_process_record(uint16_t keycode, keyrecord_t *record);
