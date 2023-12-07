
#pragma once

#ifdef UF_TAP_DANCE_ENABLE

#  ifdef VIAL_ENABLE
#    include "vial.h"
extern vial_tap_dance_entry_t uf_tap_dances[];
#  endif

enum {
  UF_TD_EQUAL,
  UF_TD_MINUS,
  UF_TD_GRAVE,
  UF_TD_LOWR,
  UF_TD_UPPR,
//   UF_TD_BSPC,
#  if defined(VIAL_ENABLE) && defined(VIAL_TAP_DANCE_ENABLE)
  UF_TAP_DANCE_ENTRIES,
#  endif
};

#endif  // UF_TAP_DANCE_ENABLE
