
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

#define UF_LPRN     KC_LPRN     // Shift ( is ) (qwerty) or { (raise)
#define UF_LBRC     KC_LBRC     // Shift [ is ] (qwerty)
#define UF_LCBR     KC_LCBR     // Shift { is } (qwerty)
#define UF_RPRN     KC_RPRN     // Shift ) is } (raise)


// _QWERTY
    // home row mods
    #define UF_S        LOPT_T(KC_S)
    #define UF_F        LCMD_T(KC_F)
    #define UF_J        RCMD_T(KC_J)
    #define UF_L        ROPT_T(KC_L)
    // I prefer shift on the next row
    #define UF_Z        LSFT_T(KC_Z)
    #define UF_SLSH     RSFT_T(KC_SLSH)
    // Row 3
    #define UF_ESC      LCTL_T(KC_ESCAPE)
    #define UF_HOME     LOPT_T(KC_HOME)
    #define UF_PGDN     KC_PGDN
    #define UF_END      LCMD_T(KC_END)
    #define UF_LOWR     LT(0,KC_DOWN)  // Send Backspace on tap, Delete on shift-tap, TL_LOWR on hold
    #define UF_SPC      KC_SPACE
    #define UF_BSPC     KC_BSPC
    #define UF_UPPR     LT(0,KC_UP)    // Send Tab on tap, TL_UPPR on hold
    #define UF_LEFT     RCMD_T(KC_LEFT)
    #define UF_DOWN     KC_DOWN
    #define UF_RIGHT    ROPT_T(KC_RIGHT)
    #define UF_ENT      RCTL_T(KC_ENTER)

// _LOWER
    // Row 0
    #define UF_FMT      S(A(KC_F))      // Shift-Alt-F              -- Format code
    #define UF_PMNS     KC_PMNS         // Shift numpad - is |      -- See uf_key_overrides.c
    // Row 1
    #define UF_PAST     KC_PAST         // Shift numpad * is "      -- See uf_key_overrides.c
    // Row 2
    #define UF_PSLS     RSFT_T(KC_PSLS)
    // Row 3
    #define UF_PENT     RCMD_T(KC_PENT)
    #define UF_P0       KC_P0
    #define UF_PDOT     ROPT_T(KC_PDOT)
    #define UF_PPLS     RCTL_T(KC_PPLS)

// _RAISE
    // Row 0
    #define UF_LPCB     KC_LPRN         // Shift ( is {     -- See uf_key_overrides.c
    #define UF_RPCB     KC_RPRN         // Shift ) is }     -- See uf_key_overrides.c
    // Row 1
    #define UF_9        KC_9            // Shift 9 is [     -- See uf_key_overrides.c
    #define UF_0        KC_0            // Shift 0 is ]     -- See uf_key_overrides.c
    // Row 2
    #define UF_F1       LSFT_T(KC_F1)
    #define UF_F12      RSFT_T(KC_F12)
    // Row 3
    #define UF_PGUP     KC_PGUP
    #define UF_UP       KC_UP


// _ADJUST
    // Row 0
    #define UF_NAPP    LCMD(KC_GRV)   // Cmd-`       -- Next Window of App
    // Row 1
    #define UF_NWIN    LCMD(KC_TAB)   // Cmd-Tab     -- Prev app toggle
    // Row 2
    #define UF_SCAP    S(G(KC_4))     // Shift-Cmd-4 -- Capture a portion of the screen
    // Row 3
