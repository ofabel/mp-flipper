#include <py/obj.h>
#include <py/runtime.h>

#include "_modflipperzero.h"

static mp_obj_t flipperzero_vibro(mp_obj_t state) {
    mp_flipper_vibro(state == mp_const_true);

    return mp_const_true;
}
static MP_DEFINE_CONST_FUN_OBJ_1(flipperzero_vibro_obj, flipperzero_vibro);

static const mp_rom_map_elem_t flipperzero_module_globals_table[] = {
    {MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_flipperzero)},
    {MP_ROM_QSTR(MP_QSTR_vibro), MP_ROM_PTR(&flipperzero_vibro_obj)},
};
static MP_DEFINE_CONST_DICT(flipperzero_module_globals, flipperzero_module_globals_table);

const mp_obj_module_t flipperzero_module = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t*)&flipperzero_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_flipperzero, flipperzero_module);
