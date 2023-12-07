
#include QMK_KEYBOARD_H

// clang-format off

#include "config.h"
#include "uf_numlock.h"

// clang-format on

#include "color.h"
#include "rgb_matrix.h"
#include "rgblight.h"

#ifdef VIAL_ENABLE
#  include "vial.h"
#  if defined(VIAL_KEY_OVERRIDE_ENABLE) && defined(UF_KEY_OVERRIDE_ENABLE)
#    include "dynamic_keymap.h"
#    include "uf_key_overrides.h"
#  endif
#  if defined(VIAL_TAP_DANCE_ENABLE) && defined(UF_TAP_DANCE_ENABLE)
#    include "dynamic_keymap.h"
#    include "uf_tapdances.h"
#  endif
#endif

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
  rgb_matrix_enable_noeeprom();
  rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
  rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#endif

#ifdef RGBLIGHT_ENABLE
  rgblight_enable_noeeprom();  // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_YELLOW);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#endif

#if defined(VIAL_ENABLE) && defined(VIAL_KEY_OVERRIDE_ENABLE) && defined(UF_KEY_OVERRIDE_ENABLE)
  for (size_t i = 0; uf_key_overrides[i] && i < VIAL_KEY_OVERRIDE_ENTRIES; ++i) {
    key_overrides[i] = uf_key_overrides[i];
    vial_key_override_entry_t entry = {
        uf_key_overrides[i]->trigger,           uf_key_overrides[i]->replacement,     uf_key_overrides[i]->layers,  uf_key_overrides[i]->trigger_mods,
        uf_key_overrides[i]->negative_mod_mask, uf_key_overrides[i]->suppressed_mods, uf_key_overrides[i]->options,
    };
    dynamic_keymap_set_key_override(i, &entry);
  }
#endif

#if defined(VIAL_ENABLE) && defined(VIAL_TAP_DANCE_ENABLE) && defined(UF_TAP_DANCE_ENABLE)
  for (size_t i = 0; i < UF_TAP_DANCE_ENTRIES && i < VIAL_TAP_DANCE_ENTRIES; ++i) {
    dynamic_keymap_set_tap_dance(i, &uf_tap_dances[i]);
  }
#endif

  uf_numlock_init();
}
