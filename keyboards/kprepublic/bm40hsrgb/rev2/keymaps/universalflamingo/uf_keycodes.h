
#pragma once

// clang-format off

#include "config.h"
#include "uf_tapdances.h"

// clang-format on

#include "keycodes.h"

#ifdef VIAL_ENABLE
// See vial-gui/src/main/python/keycodes/keycodes_v6.py
// Map custom keycodes to vial's USER00 ...
#  define KB_SAFE_RANGE QK_KB_0
#else
#  define KB_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  UF_MJM_TG = KB_SAFE_RANGE,  // toggle mouse-jiggle mode

  UF_LLOWR,  // Lock Lower Layer
  UF_LUPPR,  // Lock Upper Layer

  UF_NLTOG,  // Toggle numlock (on lower layer)

  UF_UNDT,   // LGUI(KC_LBRC) -- Cmd-[       -- Undent
  UF_INDT,   // LGUI(KC_RBRC) -- Cmd-]       -- Indent

  UF_PTAB,   // S(G(KC_LBRC)) -- Shift-Cmd-[ -- Previous editor/browser/iTerm tab
  UF_NTAB,   // S(G(KC_RBRC)) -- Shift-Cmd-] -- Next editor/browser/iTerm tab

  UF_FOLD,   // Send Cmd-k OSM(MOD_LGUI)  Expects user to type a number (or "j") for the fold level.

  // B_RGBL_TG,           // rgblight_toggle_noeeprom   -- LEDs below the PCB (i.e. - underlight)
  // B_RGBM_TG,           // rgb_matrix_toggle_noeeprom -- per-key LEDs

  // underlight equivalents of the matrix keycodes.
  B_RGBL_TOG,
  B_RGBL_MOD,   // MODE_FORWARD,
  B_RGBL_RMOD,  // MODE_REVERSE,
  B_RGBL_HUI,
  B_RGBL_HUD,
  B_RGBL_SAI,
  B_RGBL_SAD,
  B_RGBL_VAI,
  B_RGBL_VAD,
  B_RGBL_SPI,
  B_RGBL_SPD,
  B_RGBL_M_P,  // MODE_PLAIN
  B_RGBL_M_B,  // MODE_BREATHE
  // B_RGBL_M_T,  // MODE_RGBTEST
};

// clang-format off

// Map some vanilla KC_* values that we override so that they stand out in the keymap.
// See uf_key_overrides.c


// _QWERTY
    // home row mods
    #define UF_TAB      LCTL_T(KC_TAB)
    #define UF_A        LOPT_T(KC_A)
    #define UF_S        LOPT_T(KC_S)
    #define UF_F        LCMD_T(KC_F)
    #define UF_J        RCMD_T(KC_J)
    #define UF_L        ROPT_T(KC_L)
    #define UF_SCLN     ROPT_T(KC_SCLN)
    #define UF_QUOT     RCTL_T(KC_QUOT)
    // I prefer shift on the next row
    #define UF_ENT      RSFT_T(KC_ENT)
    // Row 3
    #define UF_HOME     LCTL_T(KC_HOME)
    #define UF_PGDN     LOPT_T(KC_PGDN)
    #define UF_PGUP     LOPT_T(KC_PGUP)
    #define UF_END      LCMD_T(KC_END)
    #define UF_SPC      KC_SPACE
    #define UF_BSPC     KC_BSPC
    #define UF_LEFT     RCMD_T(KC_LEFT)
    #define UF_DOWN     ROPT_T(KC_DOWN)
    #define UF_UP       ROPT_T(KC_UP)
    #define UF_RIGHT    RCTL_T(KC_RIGHT)

// _LOWER
    // Row 0
    // Row 1
    #define UF_FMT      S(A(KC_F))      // Shift-Alt-F              -- Format code
    // Row 2
    // Row 3

// _RAISE
    // Row 0
    // Row 1
    #define UF_BSLS     RSFT_T(KC_BSLS)
    // Row 2
    // Row 3


// _ADJUST
    // Row 0
    #define UF_NAPP    LCMD(KC_GRV)   // Cmd-`       -- Next Window of App
    // Row 1
    #define UF_NWIN    LCMD(KC_TAB)   // Cmd-Tab     -- Prev app toggle
    // Row 2
    #define UF_SCAP    S(G(KC_4))     // Shift-Cmd-4 -- Capture a portion of the screen
    // Row 3
