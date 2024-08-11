
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

enum {
    WIN_MODE = 0,
    MAC_MODE
};
static unsigned char uf_os_mode = MAC_MODE;

const unsigned short uf_os_keys[][UF_SHORTCUTS] = {
    [WIN_MODE] = {
        LCTL(KC_LBRC),  // UF_UNDT
        LCTL(KC_RBRC),  // UF_INDT
        LCTL(KC_PGUP),  // UF_PTAB
        LCTL(KC_PGDN),  // UF_NTAB
        KC_PSCR         // UF_SCAP
    },
    [MAC_MODE] = {
        LGUI(KC_LBRC),  // UF_UNDT
        LGUI(KC_RBRC),  // UF_INDT
        LGUI(KC_LCBR),  // UF_PTAB
        LGUI(KC_RCBR),  // UF_NTAB
        S(G(KC_4)),     // UF_SCAP
    },
};

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

  if (record->event.pressed) {

    // Reset the timer when a key is pressed.
    if(uf_is_mousejiggler_on()) {
        uf_mousejiggler_reset_idle_timer();
    }

    // Handle some common typos
    if(uf_autocorrect_process_record(keycode, record)) {
        return false;
    }
  }

  if (!uf_process_rgb_keycodes(keycode, record)) {
    return false;
  }

  switch (keycode) {
      //

    case UF_NUM:
      // UF_NUM is on _LOWER so we can only get here if UF_LOWR is pressed
      if (record->event.pressed) {
        uf_numlock_toggle();
      }
      return false;

    /*
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
    */

    case UF_RRST:   // Reset RGB to preferred defaults.
        #ifdef RGB_MATRIX_ENABLE
            rgb_matrix_enable_noeeprom();
            rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        #endif
        #ifdef RGBLIGHT_ENABLE
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_YELLOW);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        #endif
      return false;

    case UF_MJIG:
      if (record->event.pressed) {
        uf_mousejiggler_toggle();
      }
      return false;

    case UF_BSPC:
      uf_magic_backspace(keycode, KC_BSPC, record);
      return false;

    // case UF_SPC:
    //   uf_magic_backspace(keycode, keycode, record);
    //   return false;

    case UF_FOLD:
      // Send Cmd-K then hold Cmd until a character is typed.
      if( uf_os_mode == MAC_MODE ) {
        tap_code16(LGUI(KC_K));
        set_oneshot_mods(MOD_BIT(KC_LGUI));
      }
      else {
        tap_code16(LCTL(KC_K));
        set_oneshot_mods(MOD_BIT(KC_LCTL));
      }
      return false;

    case UF_UNDT:  // undent -- Cmd-[
      if (record->event.pressed) {
        if ((get_mods() | get_weak_mods()) & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT);
          tap_code16(UF_SHORTCUT_KEYCODE(UF_INDT));  // indent -- Cmd-]
        } else {
          tap_code16(UF_SHORTCUT_KEYCODE(keycode));  // undent -- Cmd-[
        }
      }
      return false;
    case UF_INDT:  // indent -- Cmd-]
    if (record->event.pressed) {
        if ((get_mods() | get_weak_mods()) & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT);
          tap_code16(UF_SHORTCUT_KEYCODE(UF_UNDT));  // undent -- Cmd-[
        } else {
          tap_code16(UF_SHORTCUT_KEYCODE(keycode));  // indent -- Cmd-]
        }
      }
      return false;

    case UF_PTAB:  // previous tab
      if (record->event.pressed) {
        if ((get_mods() | get_weak_mods()) & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT);
          tap_code16(UF_SHORTCUT_KEYCODE(UF_NTAB));  // indent -- Cmd-]
        } else {
          tap_code16(UF_SHORTCUT_KEYCODE(keycode));  // undent -- Cmd-[
        }
      }
      return false;
    case UF_NTAB:  // next tab
      if (record->event.pressed) {
        if ((get_mods() | get_weak_mods()) & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT);
          tap_code16(UF_SHORTCUT_KEYCODE(UF_PTAB));  // undent -- Cmd-[
        } else {
          tap_code16(UF_SHORTCUT_KEYCODE(keycode));  // indent -- Cmd-]
        }
      }
      return false;

    case UF_SCAP:  // screen capture
      if (record->event.pressed) {
          tap_code16(UF_SHORTCUT_KEYCODE(keycode));
      }
      return false;

    case UF_TERM: // Open/Show VSCode Terminal -- Ctrl-`
      if (record->event.pressed) {
        tap_code16(LCTL(KC_GRV));
      }
      return false;

    case UF_WIN:
      if (record->event.pressed) {
        uf_os_mode = WIN_MODE;
      }
      return false;
    case UF_MAC:
      if (record->event.pressed) {
        uf_os_mode = MAC_MODE;
      }
      return false;
  }

  return true;
}
