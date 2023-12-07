/*
 * This is modeled after quantum/caps_word.{c,h}
 */

#include QMK_KEYBOARD_H

#include <stdint.h>
#include <util/delay.h>

// clang-format off

#include "config.h"
#include "uf_mousejiggler.h"

// clang-format on

#include "action.h"
#include "action_util.h"
#include "rgblight/rgblight.h"
#include "timer.h"

/** @brief True when MouseJiggler is active. */
static bool uf_mousejiggler_active = false;

#if MOUSEJIGGLER_TIMEOUT > 0
#  if MOUSEJIGGLER_TIMEOUT < 100 || MOUSEJIGGLER_TIMEOUT > 30000
#    error "MOUSEJIGGLER_TIMEOUT must be between 100 and 60000 ms"
#  endif
#  if MOUSEJIGGLER_MULTIPLIER < 1 || MOUSEJIGGLER_MULTIPLIER > 60
#    error "MOUSEJIGGLER_MULTIPLIER must be between 1 and 60"
#  endif

/** @brief Deadline for idle timeout. */
static uint16_t uf_idle_timer = 0;
static uint8_t uf_multiplier = 0;

static void uf_mousejiggler_send_keepalive(void) {
  // Turn on underglow LEDs.
  rgblight_enable_noeeprom();

  tap_code(KC_CAPS);
  tap_code(KC_NUM);
  _delay_ms(TAP_HOLD_CAPS_DELAY);
  tap_code(KC_CAPS);
  tap_code(KC_NUM);
}

void uf_mousejiggler_task(void) {
  if (uf_mousejiggler_active && timer_expired(timer_read(), uf_idle_timer)) {
    if (!uf_multiplier) {
      uf_mousejiggler_send_keepalive();
    }
    uf_mousejiggler_reset_idle_timer();
  }
}

#else
void uf_mousejiggler_task(void) {}
#endif  // MOUSEJIGGLER_TIMEOUT > 0

void uf_mousejiggler_reset_idle_timer(void) {
  if (uf_multiplier) {
    uf_multiplier -= 1;
  } else {
    uf_multiplier = MOUSEJIGGLER_MULTIPLIER - 1;
  }
  uf_idle_timer = (timer_read() + MOUSEJIGGLER_TIMEOUT) | 1;
}

void uf_mousejiggler_on(void) {
#if MOUSEJIGGLER_TIMEOUT > 0
  rgblight_enable_noeeprom();
  if (!uf_mousejiggler_active) {
    uf_multiplier = MOUSEJIGGLER_MULTIPLIER - 1;
    uf_mousejiggler_reset_idle_timer();
  }
#endif  // MOUSEJIGGLER_TIMEOUT > 0
  uf_mousejiggler_active = true;
}

void uf_mousejiggler_off(void) {
#if MOUSEJIGGLER_TIMEOUT > 0
  rgblight_disable_noeeprom();
#endif  // MOUSEJIGGLER_TIMEOUT > 0
  uf_mousejiggler_active = false;
}

void uf_mousejiggler_toggle(void) {
  if (uf_mousejiggler_active) {
    uf_mousejiggler_off();
  } else {
    uf_mousejiggler_on();
  }
}

bool uf_is_mousejiggler_on(void) { return uf_mousejiggler_active; }
