# Universal Flamingo's custom keycodes and keymap for Ploopyco Thumb Trackball

See [uf_ploopy_thumb.h](uf_ploopy_thumb.h) for the custom keycodes and their intended uses.

Implements process_record_user() for UF_* keycodes defined in [uf_ploopy_thumb.h](uf_ploopy_thumb.h)

- UF_PRECISION_MODE - Toggle DPI/CPI precision mode on/off. When on, current DPI/CPI is divided in half.
- UF_DPI_0 ... UF_DPI_2 - Set DPI/CPI to dpi_array entry 0 ... 2
- DPI_CONFIG - Disable precision mode and pass through to process_record_kb()
