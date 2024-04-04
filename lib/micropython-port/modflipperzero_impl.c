#include <stdint.h>

#include <furi_hal.h>

#include <mp_flipper_app.h>

#include "modflipperzero.h"

static Light decode_light(uint8_t value) {
    Light light = 0;

    light += value & MP_FLIPPER_LED_RED ? LightRed : 0;
    light += value & MP_FLIPPER_LED_GREEN ? LightGreen : 0;
    light += value & MP_FLIPPER_LED_BLUE ? LightBlue : 0;
    light += value & MP_FLIPPER_LED_BACKLIGHT ? LightBacklight : 0;

    return light;
}

inline void mp_flipper_light_set(uint8_t raw_light, uint8_t brightness) {
    Light light = decode_light(raw_light);

    furi_hal_light_set(light, brightness);
}

inline void mp_flipper_light_blink_start(uint8_t raw_light, uint8_t brightness, uint16_t on_time, uint16_t period) {
    Light light = decode_light(raw_light);

    furi_hal_light_blink_start(light, brightness, on_time, period);
}

inline void mp_flipper_light_blink_set_color(uint8_t raw_light) {
    Light light = decode_light(raw_light);

    furi_hal_light_blink_set_color(light);
}

inline void mp_flipper_light_blink_stop() {
    furi_hal_light_blink_stop();
}

inline void mp_flipper_vibro(bool state) {
    furi_hal_vibro_on(state);
}

inline bool mp_flipper_speaker_start(float frequency, float volume) {
    if(furi_hal_speaker_acquire(100)) {
        furi_hal_speaker_start(frequency, volume);

        return true;
    }

    return false;
}

inline bool mp_flipper_speaker_set_volume(float volume) {
    if(furi_hal_speaker_is_mine()) {
        furi_hal_speaker_set_volume(volume);

        return true;
    }
    return false;
}

inline bool mp_flipper_speaker_stop() {
    if(furi_hal_speaker_is_mine()) {
        furi_hal_speaker_stop();

        furi_hal_speaker_release();

        return true;
    }

    return false;
}

inline void mp_flipper_canvas_draw_dot(uint8_t x, uint8_t y, bool color) {
    size_t index = x / SCREEN_PIXEL_PER_ITEM + y * (SCREEN_WIDTH / SCREEN_PIXEL_PER_ITEM);
    const uint32_t mask = 1 << (x % SCREEN_PIXEL_PER_ITEM);

    mp_flipper_canvas[index] |= color ? (UINT32_MAX & mask) : 0;
}

inline void mp_flipper_canvas_update() {
    view_port_update(mp_flipper_view_port);
}
