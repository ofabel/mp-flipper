#include <furi_hal.h>

#include "modrandom.h"

uint32_t mp_flipper_seed_init() {
    furi_hal_random_init();

    return furi_hal_random_get();
}
