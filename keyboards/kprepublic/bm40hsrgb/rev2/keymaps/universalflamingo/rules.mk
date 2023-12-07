
CONSOLE_ENABLE = no

LTO_ENABLE = yes

# Below-PCB solid color lights.
# RGBLIGHT_ENABLE = yes  # Enabled in info.json
# Per-key RGB lights.
# RGB_MATRIX_ENABLE = yes  # Enabled in info.json

VIA_ENABLE = yes
VIAL_ENABLE = yes

TAP_DANCE_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes


RGB_MATRIX_CUSTOM_USER = yes
RGB_MATRIX_ENABLE = yes

AUTO_SHIFT_ENABLE = no
COMBO_ENABLE = no
DEBUG_ENABLE = no
DYNAMIC_MACRO_ENABLE = no
ENCODER_ENABLE = no
MAGIC_ENABLE = no
MOUSEKEYS_ENABLE = no
MUSIC_ENABLE = no
POINTING_DEVICE_ENABLE = no
QMK_SETTINGS = no
SECURE_ENABLE = no
# I can do what I need with mod-tap or tap-dance.
# e.g. -- RSFT_T(KC_ENTER)
SPACE_CADET_ENABLE = no

SRC += uf_init.c
SRC += uf_autocorrect.c
SRC += uf_key_overrides.c
SRC += uf_mousejiggler.c
SRC += uf_numlock.c
SRC += uf_process_record.c
SRC += uf_process_rgb_keycodes.c
# SRC += uf_tapdances.c
