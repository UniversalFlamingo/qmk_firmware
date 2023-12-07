/* Copyright 2019
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

// Copied from vial-qmk/quantum/process_keycodes/process_rgb.c

#include QMK_KEYBOARD_H

#include <stdint.h>

// clang-format off

#include "config.h"
#include "uf_keycodes.h"

// clang-format on

#include "action.h"
#include "action_util.h"
#include "rgb_matrix.h"
#include "rgblight/rgblight.h"

#if !defined(RGBLIGHT_DISABLE_KEYCODES) || !defined(RGB_MATRIX_DISABLE_KEYCODES)
#  error "Please define RGBLIGHT_DISABLE_KEYCODES & RGB_MATRIX_DISABLE_KEYCODES"
#endif

typedef void (*rgb_func_pointer)(void);

/**
 * Wrapper for inc/dec rgb keycode
 *
 * noinline to optimise for firmware size not speed (not in hot path)
 */
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
static void __attribute__((noinline)) handleKeycodeRGB(const uint8_t is_shifted, const rgb_func_pointer inc_func, const rgb_func_pointer dec_func) {
  if (is_shifted) {
    dec_func();
  } else {
    inc_func();
  }
}
#endif

/**
 * Wrapper for animation mode
 *   - if not in animation family -> jump to that animation
 *   - otherwise -> wrap round animation speed
 *
 * noinline to optimise for firmware size not speed (not in hot path)
 */
static void __attribute__((noinline, unused)) handleKeycodeRGBMode(const uint8_t start, const uint8_t end) {
  if ((start <= rgblight_get_mode()) && (rgblight_get_mode() < end)) {
    rgblight_step();
  } else {
    rgblight_mode(start);
  }
}

/**
 * Handle keycodes for both rgblight and rgbmatrix
 */
bool uf_process_rgb_keycodes(const uint16_t keycode, const keyrecord_t *record) {
  // need to trigger on key-up for edge-case issue
#ifndef RGB_TRIGGER_ON_KEYDOWN
  if (!record->event.pressed) {
#else
  if (record->event.pressed) {
#endif
#if (defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES)) || (defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES))
    uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
#endif
    switch (keycode) {
      case B_RGBL_TOG:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES)
        rgblight_toggle();
#endif
        return false;
      case RGB_TOG:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES)
        rgb_matrix_toggle();
#endif
        return false;

      case B_RGBL_MOD:  // B_RGBL_MODE_FORWARD:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgblight_step, rgblight_step_reverse);
#endif
        return false;
      case RGB_MODE_FORWARD:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgb_matrix_step, rgb_matrix_step_reverse);
#endif
        return false;

      case B_RGBL_RMOD:  // B_RGBL_MODE_REVERSE:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgblight_step_reverse, rgblight_step);
#endif
        return false;
      case RGB_MODE_REVERSE:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgb_matrix_step_reverse, rgb_matrix_step);
#endif
        return false;

      case B_RGBL_HUI:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgblight_increase_hue, rgblight_decrease_hue);
#endif
        return false;
      case RGB_HUI:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgb_matrix_increase_hue, rgb_matrix_decrease_hue);
#endif
        return false;

      case B_RGBL_HUD:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgblight_decrease_hue, rgblight_increase_hue);
#endif
        return false;
      case RGB_HUD:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgb_matrix_decrease_hue, rgb_matrix_increase_hue);
#endif
        return false;

      case B_RGBL_SAI:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgblight_increase_sat, rgblight_decrease_sat);
#endif
        return false;
      case RGB_SAI:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgb_matrix_increase_sat, rgb_matrix_decrease_sat);
#endif
        return false;

      case B_RGBL_SAD:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgblight_decrease_sat, rgblight_increase_sat);
#endif
        return false;
      case RGB_SAD:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgb_matrix_decrease_sat, rgb_matrix_increase_sat);
#endif
        return false;

      case B_RGBL_VAI:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgblight_increase_val, rgblight_decrease_val);
#endif
        return false;
      case RGB_VAI:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgb_matrix_increase_val, rgb_matrix_decrease_val);
#endif
        return false;

      case B_RGBL_VAD:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgblight_decrease_val, rgblight_increase_val);
#endif
        return false;
      case RGB_VAD:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgb_matrix_decrease_val, rgb_matrix_increase_val);
#endif
        return false;

      case B_RGBL_SPI:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgblight_increase_speed, rgblight_decrease_speed);
#endif
        return false;
      case RGB_SPI:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgb_matrix_increase_speed, rgb_matrix_decrease_speed);
#endif
        return false;

      case B_RGBL_SPD:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgblight_decrease_speed, rgblight_increase_speed);
#endif
        return false;
      case RGB_SPD:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES)
        handleKeycodeRGB(shifted, rgb_matrix_decrease_speed, rgb_matrix_increase_speed);
#endif
        return false;

      case B_RGBL_M_P:  // B_RGBL_MODE_PLAIN:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES)
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
#endif
        return false;
      case RGB_MODE_PLAIN:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES)
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
#endif
        return false;

      case B_RGBL_M_B:  // B_RGBL_MODE_BREATHE:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES) && defined(RGBLIGHT_EFFECT_BREATHING)
        handleKeycodeRGBMode(RGBLIGHT_MODE_BREATHING, RGBLIGHT_MODE_BREATHING_end);
#endif
        return false;
      case RGB_MODE_BREATHE:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES) && defined(ENABLE_RGB_MATRIX_BREATHING)
        rgb_matrix_mode(RGB_MATRIX_BREATHING);
#endif
        return false;
        /*
                    case B_RGBL_MODE_RAINBOW:
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES) && defined(RGBLIGHT_EFFECT_RAINBOW_MOOD)
                        handleKeycodeRGBMode(RGBLIGHT_MODE_RAINBOW_MOOD, RGBLIGHT_MODE_RAINBOW_MOOD_end);
        #endif
        #if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES) && defined(ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT)
                        rgb_matrix_mode(RGB_MATRIX_CYCLE_LEFT_RIGHT);
        #endif
                        return false;

                    case B_RGBL_MODE_SWIRL:
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES) && defined(RGBLIGHT_EFFECT_RAINBOW_SWIRL)
                        handleKeycodeRGBMode(RGBLIGHT_MODE_RAINBOW_SWIRL, RGBLIGHT_MODE_RAINBOW_SWIRL_end);
        #endif
        #if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DISABLE_KEYCODES) && defined(ENABLE_RGB_MATRIX_CYCLE_PINWHEEL)
                        rgb_matrix_mode(RGB_MATRIX_CYCLE_PINWHEEL);
        #endif
                        return false;

                    case B_RGBL_MODE_SNAKE:
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES) && defined(RGBLIGHT_EFFECT_SNAKE)
                        handleKeycodeRGBMode(RGBLIGHT_MODE_SNAKE, RGBLIGHT_MODE_SNAKE_end);
        #endif
                        return false;

                    case B_RGBL_MODE_KNIGHT:
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES) && defined(RGBLIGHT_EFFECT_KNIGHT)
                        handleKeycodeRGBMode(RGBLIGHT_MODE_KNIGHT, RGBLIGHT_MODE_KNIGHT_end);
        #endif
                        return false;

                    case B_RGBL_MODE_XMAS:
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES) && defined(RGBLIGHT_EFFECT_CHRISTMAS)
                        rgblight_mode(RGBLIGHT_MODE_CHRISTMAS);
        #endif
                        return false;

                    case B_RGBL_MODE_GRADIENT:
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES) && defined(RGBLIGHT_EFFECT_STATIC_GRADIENT)
                        handleKeycodeRGBMode(RGBLIGHT_MODE_STATIC_GRADIENT, RGBLIGHT_MODE_STATIC_GRADIENT_end);
        #endif
                        return false;
        */
      // case B_RGBL_M_T:  // B_RGBL_MODE_RGBTEST:
      case RGB_MODE_RGBTEST:
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES) && defined(RGBLIGHT_EFFECT_RGB_TEST)
        rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
#endif
        return false;
        /*
                    case B_RGBL_MODE_TWINKLE:
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_DISABLE_KEYCODES) && defined(RGBLIGHT_EFFECT_TWINKLE)
                        handleKeycodeRGBMode(RGBLIGHT_MODE_TWINKLE, RGBLIGHT_MODE_TWINKLE_end);
        #endif
                        return false;
        */
    }
  }

  return true;
}
