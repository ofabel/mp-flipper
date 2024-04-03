#pragma once

#include <stdint.h>
#include <stdbool.h>

void mp_flipper_vibro(bool state);

#define MP_FLIPPER_LED_RED (1 << 0)
#define MP_FLIPPER_LED_GREEN (1 << 1)
#define MP_FLIPPER_LED_BLUE (1 << 2)
#define MP_FLIPPER_LED_BACKLIGHT (1 << 3)

void mp_flipper_light_set(uint8_t raw_light, uint8_t brightness);
