/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

// Custom behaviors.
// #define ENABLE_RGB_MATRIX_NUMLOCK
#define MOUSEJIGGLER_ENABLE

#ifdef VIAL_ENABLE

#  define VIAL_KEYBOARD_UID \
    { 0x55, 0x53, 0xE7, 0xBC, 0x9D, 0x8E, 0x02, 0x7B }

#  define VIAL_KEY_OVERRIDE_ENTRIES 10

#  define DYNAMIC_KEYMAP_LAYER_COUNT 4
#  define DYNAMIC_KEYMAP_MACRO_COUNT 4

#  define LAYER_STATE_8BIT


// Locking

/* top-left and bottom-right */
#  define VIAL_UNLOCK_COMBO_ROWS \
    { 0, 3 }
#  define VIAL_UNLOCK_COMBO_COLS \
    { 0, 11 }

#  undef LOCKING_SUPPORT_ENABLE
#  undef LOCKING_RESYNC_ENABLE

#endif  // VIAL_ENABLE

// Lighting effects

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

#undef BACKLIGHT_BREATHING
#undef RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 0

// #define RGBLIGHT_ENABLE // Enabled in info.json
// #define RGB_MATRIX_ENABLE // Enabled in info.json

// Disable the core underlight & matrix keycode handling.
// We will use uf_process_rgb_keycodes.* so that we can control them separately.
#define RGBLIGHT_DISABLE_KEYCODES
#define RGB_MATRIX_DISABLE_KEYCODES

// Remove some things to reduce the binary size.

#ifndef NO_DEBUG
#  define NO_DEBUG
#endif
#ifndef NO_MUSIC_MODE
#  define NO_MUSIC_MODE
#endif
#ifndef NO_PRINT
#  define NO_PRINT
#endif

// #define UF_TAP_DANCE_ENABLE
#define UF_KEY_OVERRIDE_ENABLE
