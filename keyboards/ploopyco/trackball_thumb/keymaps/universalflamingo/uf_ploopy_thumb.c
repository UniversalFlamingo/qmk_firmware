
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

#include "uf_ploopy_thumb.h"

bool is_precision_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    bool set_dpi = false;

#ifdef CONSOLE_ENABLE
    xprintf("process_record_user: %d : %d.\n", keycode, record->event.pressed);
#endif

    if (keycode == DPI_CONFIG) {
        is_precision_active = false;
        return true;
    }

    if (keycode == UF_PRECISION_MODE) {
        if (!record->event.pressed) {
            return false;
        }

        is_precision_active = !is_precision_active;

        if (is_precision_active) {
            // Precision was off, we are turning it on.
            // Set CPI to half the current value.
            current_precision = pointing_device_get_cpi();
            pointing_device_set_cpi(current_precision / 2);
            return false;
        }

        // Precision was on, we are turning it off.
        // Because of rounding during division we cannot simply do:
        //      pointing_device_set_cpi(pointing_device_get_cpi() * 2)
        set_dpi = true;
    }

    switch (keycode) {
        // Select specific DPI from dpi_array.
        case UF_DPI_0 ... UF_DPI_2:
            set_dpi                    = true;
            keyboard_config.dpi_config = keycode - UF_DPI_0;
            break;
    }

    if (set_dpi) {
        if (!record->event.pressed) {
            return false;
        }

        is_precision_active = false;

        keyboard_config.dpi_config = keyboard_config.dpi_config % dpi_array_size;
        eeconfig_update_kb(keyboard_config.raw);
        pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);

        return false;
    }

    return true;
}
