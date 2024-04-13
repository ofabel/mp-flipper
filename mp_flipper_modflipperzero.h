#pragma once

#include <stdint.h>
#include <stdbool.h>

#define MP_FLIPPER_LED_RED (1 << 0)
#define MP_FLIPPER_LED_GREEN (1 << 1)
#define MP_FLIPPER_LED_BLUE (1 << 2)
#define MP_FLIPPER_LED_BACKLIGHT (1 << 3)

#define MP_FLIPPER_COLOR_BLACK (1 << 0)
#define MP_FLIPPER_COLOR_WHITE (1 << 1)

#define MP_FLIPPER_INPUT_BUTTON_OK (1 << 0)
#define MP_FLIPPER_INPUT_BUTTON_BACK (1 << 1)
#define MP_FLIPPER_INPUT_BUTTON_LEFT (1 << 2)
#define MP_FLIPPER_INPUT_BUTTON_RIGHT (1 << 3)
#define MP_FLIPPER_INPUT_BUTTON_UP (1 << 4)
#define MP_FLIPPER_INPUT_BUTTON_DOWN (1 << 5)
#define MP_FLIPPER_INPUT_BUTTON ((1 << 6) - 1)

#define MP_FLIPPER_INPUT_TYPE_PRESS (1 << 6)
#define MP_FLIPPER_INPUT_TYPE_RELEASE (1 << 7)
#define MP_FLIPPER_INPUT_TYPE_LONG (1 << 8)
#define MP_FLIPPER_INPUT_TYPE_SHORT (1 << 9)
#define MP_FLIPPER_INPUT_TYPE ((1 << 10) - 1 - MP_FLIPPER_INPUT_BUTTON)

void mp_flipper_light_set(uint8_t raw_light, uint8_t brightness);
void mp_flipper_light_blink_start(uint8_t raw_light, uint8_t brightness, uint16_t on_time, uint16_t period);
void mp_flipper_light_blink_set_color(uint8_t raw_light);
void mp_flipper_light_blink_stop();

void mp_flipper_vibro(bool state);

bool mp_flipper_speaker_start(float frequency, float volume);
bool mp_flipper_speaker_set_volume(float volume);
bool mp_flipper_speaker_stop();

void mp_flipper_canvas_draw_dot(uint8_t x, uint8_t y);
void mp_flipper_canvas_set_color(uint8_t color);
void mp_flipper_canvas_set_text(uint8_t x, uint8_t y, const char* text);
void mp_flipper_canvas_update();
void mp_flipper_canvas_clear();

void mp_flipper_on_input(uint16_t button, uint16_t type);
