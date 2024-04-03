#pragma once

#include <stdint.h>
#include <stdbool.h>

#define MP_FLIPPER_LED_RED (1 << 0)
#define MP_FLIPPER_LED_GREEN (1 << 1)
#define MP_FLIPPER_LED_BLUE (1 << 2)
#define MP_FLIPPER_LED_BACKLIGHT (1 << 3)

void mp_flipper_light_set(uint8_t raw_light, uint8_t brightness);
void mp_flipper_light_blink_start(uint8_t raw_light, uint8_t brightness, uint16_t on_time, uint16_t period);
void mp_flipper_light_blink_set_color(uint8_t raw_light);
void mp_flipper_light_blink_stop();

void mp_flipper_vibro(bool state);
