
#include QMK_KEYBOARD_H

#pragma once

// Additional keycodes for use in process_record_user()
enum universal_flamingo_keycodes {
    // UF_DPI_* can be used to set DPI to a specific dpi_array entry.
    UF_DPI_0 = PLOOPY_SAFE_RANGE,
    UF_DPI_1,
    UF_DPI_2,
    // UF_PRECISION_MODE intended to divide current DPI by some factor
    // (typically 2) to increase pointer precision.
    UF_PRECISION_MODE,
    UF_SAFE_RANGE,
};
