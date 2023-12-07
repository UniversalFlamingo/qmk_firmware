
#include QMK_KEYBOARD_H

// clang-format off

#include "config.h"
#include "uf_autocorrect.h"

// clang-format on

#include "quantum.h"
#include "timer.h"

static uint16_t uf_last_keycode = KC_NO;
static uint16_t uf_autocorrect_timer = 0;

static uint16_t uf_typos[][2] = {
    {KC_C, KC_V},
    {KC_B, KC_LBRC},
};
static uint16_t uf_typos_count = sizeof(uf_typos) / sizeof(uf_typos[0]);

void uf_autocorrect_post_process_record(uint16_t keycode, keyrecord_t *record) {
  uf_autocorrect_timer = timer_read() + UF_AUTOCORRECT_DELAY;
  uf_last_keycode = keycode;
}

bool uf_autocorrect_process_record(uint16_t keycode, keyrecord_t *record) {
  //

  if (timer_expired(timer_read(), uf_autocorrect_timer)) {
    // Nothing to correct if the timer has expired.
    return false;
  }

  for (int i = 0; i < uf_typos_count; ++i) {
    if (uf_last_keycode == uf_typos[i][0] && keycode == uf_typos[i][1]) {
      unregister_code16(keycode);
      return true;  // typo corrected
    }
  }

  return false;
}
