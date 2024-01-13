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
 * |           |          !|          @|          #|          $|          %|          ^| &        &| *        *| (        (| _        )|     del   |
 * |   gesc    |     q     |     w     |     e     |     r     |     t     |     y     |     u     |     i     |     o     |     p     |    bsp    |
 * |~        ` |(        1 |)        2 |         3 |         4 |term     5 |fold     6 |7        7 |8        8 |9        9 |-        0 |<-       ->|
 * |   cmd-`   |    rgb    |   mode+   |   hue +   |   sat +   |  bright+  |           | underglow |   mode+   |   hue +   |   sat +   |  bright+  |
 * +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
 * |           |           |           |           |           |           |           | $         | %         | ^        {|      :   }| +    "    |
 * |    tab    |     a     |     s     |     d     |     f     |     g     |     h     |     j     |     k     |     l     |     ;     |     '     |
 * |           |[        F1| ]       F2|         F3|fmt      F4|<<<      F5|>>>      F6|4          |5          |6        [ |*        ] |=        | |
 * |  cmd-tab  |           |   mode-   |   hue -   |   sat -   |  bright-  |           |           |   mode-   |   hue -   |   sat -   |  bright-  |
 * +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
 * |           |           |           |           |           |           |           | !         | @    <    | #    >    |      ?    |          ||
 * |           |     z     |     x     |     c     |     v     |     b     |     n     |     m     |     ,     |     .     |     /     |    ent    |
 * |    sft    |{        F7|}        F8|         F9|         Fa|<<t      Fb|>>t      Fc|1          |2          |3        { |         } |    sft  \ |
 * |  caplock  |  numlock  |    ins    |           |   mjig    |    win    |    mac    |           |           |    up     |           |           |
 * +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
 * |           |           |           |           |           |                       |           | )         |           |           |           |
 * |   home    |   pgdn    |   pgup    |    end    |           |         space         |           |      lft  |      dwn  |       up  |      rgt  |
 * |    ctl    |    opt    |    opt    |    cmd    |   lower   |                       |   raise   | 0  cmd    | .  opt    | +  opt    |    ctl    |
 * |   reset   |           |           |           |           |                       |           |    lft    |    dwn    |    rgt    |  scrncap  |
 * +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
 *
 * +-----------+                              +--------------------------------+---------------------------------+---------------------------------+
 * | LS   S  RS|                              | fmt = shift-alt-f              | fold = Cmd-k Cmd-<n>            | mjig = keep awake / mouse jig.  |
 * |    tap    |                              | tap = tap on layer 0           | hold = on key hold              | S = shift on layer 0            |
 * |L    H   R |                              | L = Lower, LS = Lower + Shift  | R = Raise, RS = Raise + Shift   | adj = Adjust (Lower + Raise)    |
 * |    adj    |                              | <<< / >>> = undent / indent    | <<t / >>t = prev / next tab     | term = vscode terminal          |
 * +-----------+                              | ls(rs(bsp)) = delete line      | <-  /  -> = normal bsp / del    |                                 |
 *                                            +--------------------------------+---------------------------------+---------------------------------+
 *         ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,
 *  ctrl   , opt    , opt    ,        , cmd    ,        ,        , cmd    ,        , opt    , opt    , ctrl   ,
 *  shift  ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        , shift  ,
 *  ctrl   , opt    , opt    , cmd    ,        ,                 ,        , cmd    , opt    , opt    , ctrl   ,
 */

[_QWERTY] = LAYOUT_ortho_4x12_1x2uC(
    QK_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    UF_BSPC,
    KC_TAB , KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, UF_ENT,
    UF_HOME, UF_PGDN, UF_PGUP, UF_END,  TL_LOWR, KC_SPC,           TL_UPPR, UF_LEFT, UF_DOWN, UF_UP  , UF_RIGHT
),
[_LOWER] = LAYOUT_ortho_4x12_1x2uC(
    KC_TILD, KC_LPRN, KC_RPRN, KC_NO  , KC_NO  , UF_TERM, UF_FOLD, KC_7,    KC_8,    KC_9,    KC_MINS, KC_BSPC,
    _______, KC_LBRC, KC_RBRC, KC_NO  , UF_FMT , UF_UNDT, UF_INDT, KC_4,    KC_5,    KC_6,    KC_ASTR, KC_EQL,
    _______, KC_LCBR, KC_RCBR, KC_NO  , UF_FOLD, UF_PTAB, UF_NTAB, KC_1,    KC_2,    KC_3,    KC_SLSH, _______,
    _______, _______, _______, _______, _______, _______,          _______, KC_0,    KC_DOT,  KC_PLUS, _______
),
[_RAISE] = LAYOUT_ortho_4x12_1x2uC(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DELETE,
    _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_NO  , KC_NO  , KC_LBRC, KC_RBRC, KC_PIPE,
    _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_NO  , KC_NO  , KC_LCBR, KC_RCBR, UF_BSLS,
    _______, _______, _______, _______, _______, _______,          _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_UP
),
[_ADJUST] = LAYOUT_ortho_4x12_1x2uC(
    UF_NAPP, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_M_P, B_RGBL_TOG, B_RGBL_MOD,  B_RGBL_HUI, B_RGBL_SAI, B_RGBL_VAI,
    UF_NWIN, KC_NO  , RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, RGB_M_B, KC_NO  ,    B_RGBL_RMOD, B_RGBL_HUD, B_RGBL_SAD, B_RGBL_VAD,
    KC_CAPS, UF_NUM , KC_INS , KC_NO  , UF_MJIG, UF_WIN , UF_MAC , KC_NO  ,    KC_NO  ,     KC_UP  ,    _______,    _______,
    QK_BOOT, _______, _______, _______, _______, _______,          _______,    KC_LEFT,     KC_DOWN,    KC_RGHT,    UF_SCAP
)

};

// clang-format on
