// Automatically generated by makemoduledefs.py.

extern const struct _mp_obj_module_t mp_module_array;
#undef MODULE_DEF_ARRAY
#define MODULE_DEF_ARRAY { MP_ROM_QSTR(MP_QSTR_array), MP_ROM_PTR(&mp_module_array) },

extern const struct _mp_obj_module_t mp_module_json;
#undef MODULE_DEF_JSON
#define MODULE_DEF_JSON { MP_ROM_QSTR(MP_QSTR_json), MP_ROM_PTR(&mp_module_json) },

extern const struct _mp_obj_module_t mp_module_random;
#undef MODULE_DEF_RANDOM
#define MODULE_DEF_RANDOM { MP_ROM_QSTR(MP_QSTR_random), MP_ROM_PTR(&mp_module_random) },

extern const struct _mp_obj_module_t mp_module_time;
#undef MODULE_DEF_TIME
#define MODULE_DEF_TIME { MP_ROM_QSTR(MP_QSTR_time), MP_ROM_PTR(&mp_module_time) },

extern const struct _mp_obj_module_t mp_module___main__;
#undef MODULE_DEF___MAIN__
#define MODULE_DEF___MAIN__ { MP_ROM_QSTR(MP_QSTR___main__), MP_ROM_PTR(&mp_module___main__) },

extern const struct _mp_obj_module_t mp_module_builtins;
#undef MODULE_DEF_BUILTINS
#define MODULE_DEF_BUILTINS { MP_ROM_QSTR(MP_QSTR_builtins), MP_ROM_PTR(&mp_module_builtins) },

extern const struct _mp_obj_module_t flipperzero_module;
#undef MODULE_DEF_FLIPPERZERO
#define MODULE_DEF_FLIPPERZERO { MP_ROM_QSTR(MP_QSTR_flipperzero), MP_ROM_PTR(&flipperzero_module) },

extern const struct _mp_obj_module_t mp_module_gc;
#undef MODULE_DEF_GC
#define MODULE_DEF_GC { MP_ROM_QSTR(MP_QSTR_gc), MP_ROM_PTR(&mp_module_gc) },

extern const struct _mp_obj_module_t mp_module_micropython;
#undef MODULE_DEF_MICROPYTHON
#define MODULE_DEF_MICROPYTHON { MP_ROM_QSTR(MP_QSTR_micropython), MP_ROM_PTR(&mp_module_micropython) },


#define MICROPY_REGISTERED_MODULES \
    MODULE_DEF_BUILTINS \
    MODULE_DEF_FLIPPERZERO \
    MODULE_DEF_GC \
    MODULE_DEF_MICROPYTHON \
    MODULE_DEF___MAIN__ \
// MICROPY_REGISTERED_MODULES

#define MICROPY_REGISTERED_EXTENSIBLE_MODULES \
    MODULE_DEF_ARRAY \
    MODULE_DEF_JSON \
    MODULE_DEF_RANDOM \
    MODULE_DEF_TIME \
// MICROPY_REGISTERED_EXTENSIBLE_MODULES
