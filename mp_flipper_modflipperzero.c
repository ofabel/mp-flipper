#include <stdio.h>

#include "py/objint.h"
#include "py/objfun.h"
#include "py/obj.h"
#include "py/runtime.h"

#include "mp_flipper_modflipperzero.h"

static void* mp_flipper_on_draw = NULL;

static mp_obj_t flipperzero_light_set(mp_obj_t light_obj, mp_obj_t brightness_obj) {
    mp_int_t light = mp_obj_get_int(light_obj);
    mp_int_t brightness = mp_obj_get_int(brightness_obj);

    mp_flipper_light_set(light, brightness);

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(flipperzero_light_set_obj, flipperzero_light_set);

static mp_obj_t flipperzero_light_blink_start(size_t n_args, const mp_obj_t* args) {
    if(n_args != 4) {
        return mp_const_none;
    }

    mp_int_t light = mp_obj_get_int(args[0]);
    mp_int_t brightness = mp_obj_get_int(args[1]);
    mp_int_t on_time = mp_obj_get_int(args[2]);
    mp_int_t period = mp_obj_get_int(args[3]);

    mp_flipper_light_blink_start(light, brightness, on_time, period);

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(flipperzero_light_blink_start_obj, 4, 4, flipperzero_light_blink_start);

static mp_obj_t flipperzero_light_blink_stop() {
    mp_flipper_light_blink_stop();

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(flipperzero_light_blink_stop_obj, flipperzero_light_blink_stop);

static mp_obj_t flipperzero_light_blink_set_color(mp_obj_t light_obj) {
    mp_int_t light = mp_obj_get_int(light_obj);

    mp_flipper_light_blink_set_color(light);

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(flipperzero_light_blink_set_color_obj, flipperzero_light_blink_set_color);

static mp_obj_t flipperzero_vibro_set(mp_obj_t state) {
    bool state_bool = mp_obj_is_true(state);

    mp_flipper_vibro(state_bool);

    return state_bool ? mp_const_true : mp_const_false;
}
static MP_DEFINE_CONST_FUN_OBJ_1(flipperzero_vibro_set_obj, flipperzero_vibro_set);

static mp_obj_t flipperzero_speaker_start(mp_obj_t frequency_obj, mp_obj_t volume_obj) {
    mp_float_t frequency = mp_obj_get_float(frequency_obj);
    mp_float_t volume = mp_obj_get_float(volume_obj);

    return mp_flipper_speaker_start(frequency, volume) ? mp_const_true : mp_const_false;
}
static MP_DEFINE_CONST_FUN_OBJ_2(flipperzero_speaker_start_obj, flipperzero_speaker_start);

static mp_obj_t flipperzero_speaker_set_volume(mp_obj_t volume_obj) {
    mp_float_t volume = mp_obj_get_float(volume_obj);

    return mp_flipper_speaker_set_volume(volume) ? mp_const_true : mp_const_false;
}
static MP_DEFINE_CONST_FUN_OBJ_1(flipperzero_speaker_set_volume_obj, flipperzero_speaker_set_volume);

static mp_obj_t flipperzero_speaker_stop() {
    mp_flipper_speaker_stop();

    return mp_flipper_speaker_stop() ? mp_const_true : mp_const_false;
}
static MP_DEFINE_CONST_FUN_OBJ_0(flipperzero_speaker_stop_obj, flipperzero_speaker_stop);

static mp_obj_t flipperzero_canvas_draw_dot(mp_obj_t x_obj, mp_obj_t y_obj, mp_obj_t color_obj) {
    mp_int_t x = mp_obj_get_int(x_obj);
    mp_int_t y = mp_obj_get_int(y_obj);
    bool color = mp_obj_is_true(color_obj);

    mp_flipper_canvas_draw_dot(x, y, color);

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_3(flipperzero_canvas_draw_dot_obj, flipperzero_canvas_draw_dot);

static mp_obj_t flipperzero_canvas_update() {
    mp_flipper_canvas_update();

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(flipperzero_canvas_update_obj, flipperzero_canvas_update);

static mp_obj_t flipperzero_on_draw(mp_obj_t on_draw_obj) {
    mp_flipper_on_draw = on_draw_obj;

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(flipperzero_on_draw_obj, flipperzero_on_draw);

void mp_flipper_canvas_on_draw() {
    if(mp_flipper_on_draw != NULL) {
        mp_sched_schedule(mp_flipper_on_draw, mp_const_none);
    }
}

static const mp_rom_map_elem_t flipperzero_module_globals_table[] = {
    {MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_flipperzero)},
    {MP_ROM_QSTR(MP_QSTR_LIGHT_RED), MP_ROM_INT(MP_FLIPPER_LED_RED)},
    {MP_ROM_QSTR(MP_QSTR_LIGHT_GREEN), MP_ROM_INT(MP_FLIPPER_LED_GREEN)},
    {MP_ROM_QSTR(MP_QSTR_LIGHT_BLUE), MP_ROM_INT(MP_FLIPPER_LED_BLUE)},
    {MP_ROM_QSTR(MP_QSTR_LIGHT_BACKLIGHT), MP_ROM_INT(MP_FLIPPER_LED_BACKLIGHT)},
    {MP_ROM_QSTR(MP_QSTR_light_set), MP_ROM_PTR(&flipperzero_light_set_obj)},
    {MP_ROM_QSTR(MP_QSTR_light_blink_start), MP_ROM_PTR(&flipperzero_light_blink_start_obj)},
    {MP_ROM_QSTR(MP_QSTR_light_blink_set_color), MP_ROM_PTR(&flipperzero_light_blink_set_color_obj)},
    {MP_ROM_QSTR(MP_QSTR_light_blink_stop), MP_ROM_PTR(&flipperzero_light_blink_stop_obj)},
    {MP_ROM_QSTR(MP_QSTR_vibro_set), MP_ROM_PTR(&flipperzero_vibro_set_obj)},
    {MP_ROM_QSTR(MP_QSTR_speaker_start), MP_ROM_PTR(&flipperzero_speaker_start_obj)},
    {MP_ROM_QSTR(MP_QSTR_speaker_set_volume), MP_ROM_PTR(&flipperzero_speaker_set_volume_obj)},
    {MP_ROM_QSTR(MP_QSTR_speaker_stop), MP_ROM_PTR(&flipperzero_speaker_stop_obj)},
    {MP_ROM_QSTR(MP_QSTR_canvas_draw_dot), MP_ROM_PTR(&flipperzero_canvas_draw_dot_obj)},
    {MP_ROM_QSTR(MP_QSTR_canvas_update), MP_ROM_PTR(&flipperzero_canvas_update_obj)},
    {MP_ROM_QSTR(MP_QSTR_on_draw), MP_ROM_PTR(&flipperzero_on_draw_obj)},
};
static MP_DEFINE_CONST_DICT(flipperzero_module_globals, flipperzero_module_globals_table);

const mp_obj_module_t flipperzero_module = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t*)&flipperzero_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_flipperzero, flipperzero_module);
