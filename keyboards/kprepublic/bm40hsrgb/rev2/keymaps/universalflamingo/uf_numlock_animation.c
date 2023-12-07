
#ifdef ENABLE_RGB_MATRIX_NUMLOCK
#  if !defined(RGB_MATRIX_CUSTOM_EFFECT_IMPLS)
#    include <stdbool.h>
#    include <stdint.h>

#    include "rgb_matrix.h"
#    include "rgb_matrix_types.h"
#    include "uf_numlock.h"
#  endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool numlock_lights_on = false;

static bool numlock(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  if (params->init) {
    numlock_lights_on = false;
  }

  if (numlock_lights_on) {
    return rgb_matrix_check_finished_leds(led_max);
  }

  numlock_lights_on = true;

  //   const uint8_t max_cols = MATRIX_COLS - 4;
  //   const uint8_t max_intensity = rgb_matrix_config.hsv.v;
  //   const uint8_t low_intensity = rgb_matrix_config.hsv.v >> 2;

  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      if (((row == 3) && ((col == 7) || (col > 8))) || ((row < 3) && (col > 7))) {
        continue;
      }
      //   g_rgb_frame_buffer[row][col] = low_intensity;
      uint8_t led[LED_HITS_TO_REMEMBER];
      uint8_t led_count = rgb_matrix_map_row_column_to_led(row, col, led);
      while (led_count > 0) {
        // Semi-dark grey.
        rgb_matrix_set_color(led[--led_count], 8, 8, 8);
      }
    }
  }

  return rgb_matrix_check_finished_leds(led_max);
}

#endif  // ENABLE_RGB_MATRIX_NUMLOCK
