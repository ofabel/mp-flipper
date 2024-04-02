#include <furi.h>
#include <furi_hal.h>

#include <py/mphal.h>

mp_uint_t mp_time_time_get(void) {
    return furi_hal_rtc_get_timestamp();
}

uint64_t mp_hal_time_ns(void) {
    return furi_hal_rtc_get_timestamp() * 1000;
}

mp_uint_t mp_hal_ticks_ms(void) {
    return furi_kernel_get_tick_frequency() / 1000;
}

mp_uint_t mp_hal_ticks_us(void) {
    return furi_kernel_get_tick_frequency() / 1000000;
}

mp_uint_t mp_hal_ticks_cpu(void) {
    return furi_get_tick();
}

void mp_hal_delay_ms(mp_uint_t ms) {
    furi_delay_ms(ms);
}

void mp_hal_delay_us(mp_uint_t us) {
    furi_delay_us(us);
}
