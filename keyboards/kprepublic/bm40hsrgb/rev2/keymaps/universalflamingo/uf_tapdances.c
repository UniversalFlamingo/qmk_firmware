

#include QMK_KEYBOARD_H

#include <stddef.h>
#include <stdint.h>

// clang-format off

#include "config.h"
#include "uf_tapdances.h"

// clang-format on

#include "action.h"
#include "action_tapping.h"
#include "dynamic_keymap.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "process_tap_dance.h"
#include "quantum_keycodes.h"
#include "tri_layer.h"

#if defined(VIAL_ENABLE) && defined(VIAL_TAP_DANCE_ENABLE) && defined(UF_TAP_DANCE_ENABLE)
#  include "vial.h"
// clang-format off
vial_tap_dance_entry_t uf_tap_dances[] = {
    [UF_TD_EQUAL] = {KC_EQUAL, KC_NO,   KC_PIPE,     KC_NO, TAPPING_TERM},
    [UF_TD_MINUS] = {KC_MINUS, KC_NO,   S(KC_QUOTE), KC_NO, TAPPING_TERM},
    [UF_TD_GRAVE] = {KC_GRAVE, KC_NO,   KC_QUOTE,    KC_NO, TAPPING_TERM},
    [UF_TD_LOWR]  = {KC_BSPC,  TL_LOWR, KC_NO,       KC_NO, TAPPING_TERM},
    [UF_TD_UPPR]  = {KC_ENTER, TL_UPPR, KC_NO,       KC_NO, TAPPING_TERM},
    // [UF_TD_BSPC] = {KC_BSPC, KC_DELETE, KC_NO, KC_NO, TAPPING_TERM},
};
// clang-format on
#elif defined(UF_TAP_DANCE_ENABLE)
tap_dance_action_t tap_dance_actions[] = {
    [UF_TD_EQUAL] = ACTION_TAP_DANCE_DOUBLE(KC_EQUAL, KC_PIPE),
    [UF_TD_MINUS] = ACTION_TAP_DANCE_DOUBLE(KC_MINUS, KC_DOUBLE_QUOTE),
    [UF_TD_GRAVE] = ACTION_TAP_DANCE_DOUBLE(KC_GRAVE, KC_QUOTE),
    // [UF_TD_LOWR] = ...
    // [UF_TD_UPPR] = ...
    // [UF_TD_BSPC] = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, KC_DELETE),
};
#endif
