/*
 * This is modeled after quantum/caps_word.{c,h}
 */

#include QMK_KEYBOARD_H

// clang-format off

#include "config.h"
#include "uf_numlock.h"

// clang-format on

#include "action_layer.h"
#include "keycodes.h"
#include "rgb_matrix/rgb_matrix.h"
#include "rgblight.h"
#include "tri_layer.h"
#include "vial_ensure_keycode.h"

/** @brief True when numlock is active. */
static bool uf_numlock_active = false;

#ifdef ENABLE_RGB_MATRIX_NUMLOCK
static uint8_t uf_numlock_animation = RGB_MATRIX_CUSTOM_numlock;
static uint8_t uf_previous_animation = 0;
#  define SAVE_CURRENT_ANIMATION uf_previous_animation = rgb_matrix_get_mode();
#  define ACTIVATE_NUMLOCK_ANIMATION rgb_matrix_mode_noeeprom(uf_numlock_animation);
#  define RESTORE_PREVIOUS_ANIMATION rgb_matrix_mode_noeeprom(uf_previous_animation);
#else
#  define SAVE_CURRENT_ANIMATION
#  define ACTIVATE_NUMLOCK_ANIMATION
#  define RESTORE_PREVIOUS_ANIMATION
#endif

void uf_numlock_init(void) {
  SAVE_CURRENT_ANIMATION
  if (uf_check_os_numlock_state()) {
    // tap_code(KC_NUM_LOCK);
  }
}

bool uf_check_os_numlock_state(void) {
  led_t led_state = host_keyboard_led_state();
  return led_state.num_lock;
}

bool uf_is_numlock_on(void) { return uf_numlock_active; }

void uf_numlock_toggle(void) {
  uf_numlock_active = !uf_numlock_active;
  /*
    if (uf_numlock_active) {
      uf_numlock_off();
    } else {
      uf_numlock_on();
    }
  */
}

/*
void uf_numlock_on(void) {
  if (uf_numlock_active) {
    return;
  }

//   tap_code(KC_NUM_LOCK);

  SAVE_CURRENT_ANIMATION

  //   rgb_matrix_disable_noeeprom();
  //   rgblight_disable_noeeprom();

  ACTIVATE_NUMLOCK_ANIMATION

  layer_on(get_tri_layer_lower_layer());
  uf_numlock_active = true;
}
*/
/*
void uf_numlock_off(void) {
  if (!uf_numlock_active) {
    return;
  }

//   tap_code(KC_NUM_LOCK);

  //   rgb_matrix_enable_noeeprom();
  //   rgblight_enable_noeeprom();
  layer_off(get_tri_layer_lower_layer());

  RESTORE_PREVIOUS_ANIMATION

  uf_numlock_active = false;
}
*/
