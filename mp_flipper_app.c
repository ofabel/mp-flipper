#include <malloc.h>

#include <furi.h>
#include <dialogs/dialogs.h>
#include <storage/storage.h>

#include <mp_flipper_runtime.h>
#include <mp_flipper_compiler.h>

#define TAG "uPython"

static void execute_file(FuriString* file) {
    size_t stack;

    const char* path = furi_string_get_cstr(file);
    FuriString* file_path = furi_string_alloc_printf("%s", path);

    do {
        FURI_LOG_I(TAG, "executing script %s", path);

        const size_t heap_size = memmgr_get_free_heap() * 0.1;
        const size_t stack_size = 2 * 1024;
        uint8_t* heap = malloc(heap_size * sizeof(uint8_t));

        FURI_LOG_D(TAG, "initial heap size is %zu bytes", heap_size);
        FURI_LOG_D(TAG, "stack size is %zu bytes", stack_size);

        size_t index = furi_string_search_rchar(file_path, '/');

        furi_check(index != FURI_STRING_FAILURE);

        bool is_py_file = furi_string_end_with_str(file_path, ".py");

        furi_string_left(file_path, index);

        mp_flipper_set_root_module_path(furi_string_get_cstr(file_path));

        mp_flipper_init(heap, heap_size, stack_size, &stack);

        if(is_py_file) {
            mp_flipper_exec_py_file(path);
        } else {
            mp_flipper_exec_mpy_file(path);
        }

        mp_flipper_deinit();

        free(heap);
    } while(false);

    furi_string_free(file_path);
}

static bool select_python_file(FuriString* file_path) {
    DialogsApp* dialogs = furi_record_open(RECORD_DIALOGS);

    DialogsFileBrowserOptions browser_options;

    dialog_file_browser_set_basic_options(&browser_options, "py", NULL);

    browser_options.hide_ext = false;
    browser_options.base_path = STORAGE_APP_DATA_PATH_PREFIX;

    bool result = dialog_file_browser_show(dialogs, file_path, file_path, &browser_options);

    furi_record_close(RECORD_DIALOGS);

    return result;
}

int32_t mp_flipper_app(void* p) {
    UNUSED(p);

    FuriString* file_path = furi_string_alloc();

    if(select_python_file(file_path)) {
        execute_file(file_path);
    }

    furi_string_free(file_path);

    return 0;
}
