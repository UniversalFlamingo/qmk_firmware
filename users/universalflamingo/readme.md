# User space for Universal Flamingo

Customizations for my devices.

## [thumb_trackball.c](thumb_trackball.c)

Implements process_record_user() for UF_* keycodes defined in [keyboards/ploopyco/trackball_thumb/keymaps/universalflamingo/uf_ploopy_thumb.h](../../keyboards/ploopyco/trackball_thumb/keymaps/universalflamingo/uf_ploopy_thumb.h)

- UF_PRECISION_MODE - Toggle DPI/CPI precision mode on/off. When on, current DPI/CPI is divided in half.
- UF_DPI_0 ... UF_DPI_2 - Set DPI/CPI to dpi_array entry 0 ... 2
- DPI_CONFIG - Disable precision mode and pass through to process_record_kb()
