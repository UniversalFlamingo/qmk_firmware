/*
 * This is modeled after quantum/caps_word.{c,h}
 */

#pragma once

#include <stdbool.h>

/** @brief Initialize numlock state. */
void uf_numlock_init(void);

/** @brief Checks OS numlock state. */
bool uf_check_os_numlock_state(void);

/** @brief Activates numlock. */
// void uf_numlock_on(void);

/** @brief Deactivates numlock. */
// void uf_numlock_off(void);

/** @brief Toggles numlock. */
void uf_numlock_toggle(void);

/** @brief Gets whether currently active. */
bool uf_is_numlock_on(void);

#define uf_is_numlock_off() !uf_is_numlock_on()
