#include <stdbool.h>

#include <furi_hal.h>

#include "_modflipperzero.h"

inline void mp_flipper_vibro(bool state) {
    furi_hal_vibro_on(state);
}

inline void mp_flipper_light_set(uint8_t raw_light, uint8_t brightness) {
    Light light = 0;

    light += raw_light & MP_FLIPPER_LED_RED ? LightRed : 0;
    light += raw_light & MP_FLIPPER_LED_GREEN ? LightGreen : 0;
    light += raw_light & MP_FLIPPER_LED_BLUE ? LightBlue : 0;
    light += raw_light & MP_FLIPPER_LED_BACKLIGHT ? LightBacklight : 0;

    furi_hal_light_set(light, brightness);
}
