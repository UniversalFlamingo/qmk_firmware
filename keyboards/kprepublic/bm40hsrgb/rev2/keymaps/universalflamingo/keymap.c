/* Copyright 2020 tominabox1
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// https://docs.qmk.fm/#/feature_layouts?id=tips-for-making-layouts-keyboard-agnostic

#include <stddef.h>
#include <stdint.h>

// clang-format off

#include "config.h"
#include "uf_keycodes.h"
#include "uf_keymap.h"

// clang-format on

#include "default_keyboard.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "process_key_override.h"
#include "quantum_keycodes.h"

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *
 * +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
 * |      Q    |      W    |      E    |      R    |     T     | ~    )    |     _     | &    Y    | *   U     | (   I  {  |      O  } | |   P   | |
 * |     q     |     w     |     e     |     r     |    t      |     (     |    -      |     y     |    u      |    i      |     o     |    p      |
 * |esc     esc|         ! |         @ |         # |         $ | `       % |fmt      ^ | 7       & | 8       * | 9      (  | -       ) | \       \ |
 * |   cmd-`   |    rgb    |   mode+   |   hue +   |   sat +   |  bright+  |           | underglow |   mode+   |   hue +   |   sat +   |  bright+  |
 * +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
 * |      A    |      S    |      D    |      F    |     G     |      ]    |      "    | $    H    | %    J    | ^   K   [ |      L  ] | "    :  " |
 * |     a     |     s     |     d     |     f     |    g      |     [     |     '     |     h     |     j     |    k      |     l     |     ;     |
 * |tab     tab|    opt  1 |         2 |    cmd  3 |         4 |cmd-`    5 |fold     6 | 4       7 | 5  cmd  8 | 6       9 | *  opt  0 | '       ' |
 * |  cmd-tab  |           |   mode-   |   hue -   |   sat -   |  bright-  |           |           |   mode-   |   hue -   |   sat -   |  bright-  |
 * +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
 * |      Z    |      X    |      C    |     V     |     B     |      }    |del  +     | !    N    | @    M    | #    <    |      >    | +    ?    |
 * |     z     |     x     |     c     |    v      |    b      |     {     |    =      |     n     |     m     |     ,     |     .     |     /     |
 * |    sft  F1|         F2|         F3|         F4|         F5|cmd-tab  F6|bsp      F7| 1       F8| 2       F9| 3       Fa| /       Fb| =  sft  Fc|
 * |  caplock  |  numlock  |    ins    |           |           |           |           |           |           |    up     |   kpawk   |  scrncap  |
 * +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
 * |           |           |           |           |   del     |          del          |  backtab  | )         |           |           |           |
 * |    esc    |    hme    |    pdn    |    end    |   bsp     |         space         |    tab    |    lft    |    dwn    |    rgt    |    ent    |
 * |    ctl    |    opt    |        pup|    cmd    |  lower    |                       |   raise   | 0  cmd    | .      up | +  opt    |    ctl    |
 * |           |           |           |           |           |                       |           |    lft    |    dwn    |    rgt    |   reset   |
 * +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
 *
 * +-----------+                              +--------------------------------+---------------------------------+---------------------------------+
 * | LS   S RS |                              | fmt = shift-alt-f              | fold = Cmd-k Cmd-<n>            | kpawk = keep awake / mouse jig. |
 * |    tap    |                              | tap = tap on layer 0           | hold = on key hold              | S = shift on layer 0            |
 * | L   H   R |                              | L = Lower, LS = Lower + Shift  | R = Raise, RS = Raise + Shift   | adj = Adjust (Lower + Raise)    |
 * |    adj    |                              |                                |                                 |                                 |
 * +-----------+                              +--------------------------------+---------------------------------+---------------------------------+
 *
 */

[_QWERTY] = LAYOUT_ortho_4x12_1x2uC(
    KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,    UF_LPRN, KC_MINS, KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,
    KC_A,    UF_S,    KC_D,    UF_F,   KC_G,    UF_LBRC, KC_QUOT, KC_H,    UF_J,    KC_K,    UF_L,     KC_SCLN,
    UF_Z,    KC_X,    KC_C,    KC_V,   KC_B,    UF_LCBR, KC_EQL,  KC_N,    KC_M,    KC_COMM, KC_DOT,   UF_SLSH,
    UF_ESC,  UF_HOME, UF_PGDN, UF_END, UF_LOWR, UF_SPC,               UF_UPPR, UF_LEFT, UF_DOWN, UF_RIGHT, UF_ENT
),
[_LOWER] = LAYOUT_ortho_4x12_1x2uC(
    KC_ESC , _______, _______, _______, _______, KC_GRV , UF_FMT , KC_7,    KC_8,  KC_9,    KC_MINS,   KC_BSLS,
    KC_TAB , _______, _______, _______, _______, UF_NAPP, UF_FOLD, KC_4,    KC_5,  KC_6,    KC_ASTR,   KC_QUOT,
    KC_LSFT, _______, _______, _______, _______, UF_NWIN, UF_BSPC, KC_1,    KC_2,  KC_3,    KC_SLSH,   KC_EQL ,
    _______, _______, _______, _______, _______, _______,              _______, KC_0,  KC_DOT,  KC_PLUS,   _______
),
[_RAISE] = LAYOUT_ortho_4x12_1x2uC(
    KC_ESC , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, UF_LPCB, UF_RPCB, KC_BSLS,
    KC_TAB , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , UF_9   , UF_0   , KC_QUOT,
    UF_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , UF_F12 ,
    _______, _______, KC_PGUP, _______, _______, _______,              _______, _______, KC_UP  , _______, _______
),
[_ADJUST] = LAYOUT_ortho_4x12_1x2uC(
    UF_NAPP, RGB_TOG,  RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, RGB_M_P, B_RGBL_TOG, B_RGBL_MOD,  B_RGBL_HUI, B_RGBL_SAI, B_RGBL_VAI,
    UF_NWIN, _______,  RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_M_B, _______,    B_RGBL_RMOD, B_RGBL_HUD, B_RGBL_SAD, B_RGBL_VAD,
    KC_CAPS, UF_NLTOG, KC_INS,   _______, _______, _______, _______, _______,    _______,     KC_UP  ,    UF_MJM_TG,  UF_SCAP,
    _______, _______,  _______,  _______, _______, _______,              _______,    KC_LEFT,     KC_DOWN,    KC_RIGHT,    QK_BOOT
)

};

// clang-format on
