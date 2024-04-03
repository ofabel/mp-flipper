#include <furi_hal.h>

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
