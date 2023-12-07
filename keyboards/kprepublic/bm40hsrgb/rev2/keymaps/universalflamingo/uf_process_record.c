
#include QMK_KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

// clang-format off

#include "config.h"
#include "uf_keycodes.h"
#include "uf_mousejiggler.h"
#include "uf_numlock.h"
#include "uf_process_rgb_keycodes.h"
#include "uf_autocorrect.h"

// clang-format on

#include "action_util.h"
#include "process_tri_layer.h"
#include "quantum.h"
#include "quantum_keycodes.h"

void matrix_scan_user(void) {
#ifdef MOUSEJIGGLER_ENABLE
  uf_mousejiggler_task();
#endif
}

void uf_magic_backspace(uint16_t trigger_keycode, uint16_t on_tap_keycode, keyrecord_t *record) {
  uint8_t mods = get_mods();
  uint8_t weak_mods = get_weak_mods();
  uint8_t effective_mods = mods | weak_mods;
  uint8_t shifted = effective_mods & MOD_MASK_SHIFT;

  if (!record->event.pressed) {
    return;
  }

  if (trigger_keycode != KC_NO) {
    unregister_code(trigger_keycode);
  }

  if (shifted == MOD_MASK_SHIFT) {
    // l_shift + r_shift + tap sends delete with shift enabled (i.e. -- delete line)
    tap_code(KC_DELETE);
  } else if (shifted) {
    // one shift key + tap sends delete without shift enabled (i.e. -- regular delete)
    del_mods(MOD_MASK_SHIFT);
    tap_code(KC_DELETE);
    set_mods(mods);
    set_weak_mods(weak_mods);
  } else {
    // tap sends keycode
    tap_code(on_tap_keycode);
  }
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) { uf_autocorrect_post_process_record(keycode, record); }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  //

  // Handle some common typos
  if (record->event.pressed && uf_autocorrect_process_record(keycode, record)) {
    return false;
  }

  if (!uf_process_rgb_keycodes(keycode, record)) {
    return false;
  }

  switch (keycode) {
      //

    case UF_NLTOG:
      // UF_NLTOG is on _LOWER so we can only get here if UF_LOWR is pressed
      if (record->event.pressed) {
        uf_numlock_toggle();
      }
      return false;

    case UF_LOWR:
      unregister_code(keycode);
      if (record->tap.count) {
        // On tap
        uf_magic_backspace(KC_NO, KC_BSPC, record);
      } else if (record->event.pressed) {
        // on hold press
        process_tri_layer(QK_TRI_LAYER_LOWER, record);
        if (uf_is_numlock_off()) {
          //   tap_code(KC_NUM_LOCK);
        }
      } else if (uf_is_numlock_off()) {
        // on hold release
        process_tri_layer(QK_TRI_LAYER_LOWER, record);
        // tap_code(KC_NUM_LOCK);
      } else {
      }
      return false;

    case UF_UPPR:
      unregister_code(keycode);
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code(KC_TAB);
        }
      } else {
        process_tri_layer(QK_TRI_LAYER_UPPER, record);
      }
      return false;

    case UF_MJM_TG:
      if (record->event.pressed) {
        uf_mousejiggler_toggle();
      }
      return false;

    case UF_BSPC:
      uf_magic_backspace(keycode, keycode, record);
      return false;

    case UF_SPC:
      uf_magic_backspace(keycode, keycode, record);
      return false;

    case UF_FOLD:
      // Send Cmd-K then hold Cmd until a character is typed.
      tap_code16(LGUI(KC_K));
      set_oneshot_mods(MOD_BIT(KC_LGUI));
      return false;

    case UF_UNDT:  // undent, shift + undent sends indent
      if (record->event.pressed) {
        if ((get_mods() | get_weak_mods()) & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT);
          tap_code16(LGUI(KC_RBRC));  // indent
        } else {
          tap_code16(LGUI(KC_LBRC));  // undent
        }
      }
      return false;
    case UF_INDT:  // indent
      if (record->event.pressed) {
        tap_code16(LGUI(KC_RBRC));
      }
      return false;

    case UF_PTAB:  // previous tab, shift + previuos tab sends next tab
      if (record->event.pressed) {
        if ((get_mods() | get_weak_mods()) & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT);
          tap_code16(S(G(KC_LBRC)));  // next tab
        } else {
          tap_code16(S(G(KC_RBRC)));  // previous tab
        }
      }
      return false;
    case UF_NTAB:  // next tab
      if (record->event.pressed) {
        tap_code16(S(G(KC_RBRC)));
      }
      return false;
  }

  return true;
}
