#include <stdio.h>

#include "py/mphal.h"
#include "py/builtin.h"

#include "mp_flipper_halport.h"

mp_obj_t mp_builtin_open(size_t n_args, const mp_obj_t* args, mp_map_t* kwargs) {
    return mp_const_none;
}

MP_DEFINE_CONST_FUN_OBJ_KW(mp_builtin_open_obj, 1, mp_builtin_open);

void mp_hal_stdout_tx_str(const char* str) {
    mp_flipper_stdout_tx_str(str);
}

void mp_hal_stdout_tx_strn_cooked(const char* str, size_t len) {
    mp_flipper_stdout_tx_strn_cooked(str, len);
}

mp_import_stat_t mp_import_stat(const char* path) {
    mp_flipper_import_stat_t stat = mp_flipper_import_stat(path);

    if(stat == MP_FLIPPER_IMPORT_STAT_FILE) {
        return MP_IMPORT_STAT_FILE;
    }

    if(stat == MP_FLIPPER_IMPORT_STAT_DIR) {
        return MP_IMPORT_STAT_DIR;
    }

    return MP_IMPORT_STAT_NO_EXIST;
}