#include <stdio.h>

#include <furi.h>
#include <storage/storage.h>

#include <py/mphal.h>
#include <py/builtin.h>

#include "state.h"

const mp_obj_fun_builtin_var_t mp_builtin_open_obj;

void mp_hal_stdout_tx_str(const char* str) {
    printf("%s", str);
}

mp_import_stat_t mp_import_stat(const char* path) {
    Storage* storage = furi_record_open(RECORD_STORAGE);
    FuriString* file_path = furi_string_alloc();
    mp_import_stat_t stat = MP_IMPORT_STAT_NO_EXIST;

    furi_string_printf(file_path, "%s/%s", root_module_path, path);

    FileInfo* info = NULL;

    if(storage_common_stat(storage, furi_string_get_cstr(file_path), info) == FSE_OK) {
        stat = (info && info->flags & FSF_DIRECTORY) == FSF_DIRECTORY ? MP_IMPORT_STAT_DIR : MP_IMPORT_STAT_FILE;
    }

    furi_string_free(file_path);
    furi_record_close(RECORD_STORAGE);

    return stat;
}
