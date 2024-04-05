#include <stdio.h>

#include "py/mphal.h"
#include "py/builtin.h"

#include "mp_flipper_halport.h"

const mp_obj_fun_builtin_var_t mp_builtin_open_obj;

void mp_hal_stdout_tx_str(const char* str) {
    mp_flipper_stdout_tx_str(str);
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
