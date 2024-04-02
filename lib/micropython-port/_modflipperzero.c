#include <stdbool.h>

#include <furi_hal.h>

void mp_flipper_vibro(bool state) {
    furi_hal_vibro_on(state);
}
