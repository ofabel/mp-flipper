#include <furi.h>
#include <storage/storage.h>

#include <mp_flipper_runtime.h>
#include <mp_flipper_compiler.h>

#include "py_app.h"

#define PYTHON_SETTINGS_VERSION 0x01
#define PYTHON_SETTINGS_PATH INT_PATH(".python.settings")

int32_t py_app(void *arg)
{
    if (arg == NULL || strlen(arg) == 0)
    {
        return 0;
    }

    FuriString *file_path = furi_string_alloc_printf("%s", (const char *)arg);

    py_app_file_execute(file_path);

    furi_string_free(file_path);

    return 0;
}

void py_app_file_execute(FuriString *file)
{
    size_t stack;

    PyApp *app = py_app_alloc();
    const char *path = furi_string_get_cstr(file);
    FuriString *file_path = furi_string_alloc_printf("%s", path);

    do
    {
        FURI_LOG_I(TAG, "executing script %s", path);

        const size_t heap_size = memmgr_get_free_heap() * app->heap_size;
        const size_t stack_size = app->stack_size;
        uint8_t *heap = malloc(heap_size * sizeof(uint8_t));

        FURI_LOG_D(TAG, "allocated memory is %zu bytes", heap_size);
        FURI_LOG_D(TAG, "stack size is %zu bytes", stack_size);

        size_t index = furi_string_search_rchar(file_path, '/');

        furi_check(index != FURI_STRING_FAILURE);

        bool is_py_file = furi_string_end_with_str(file_path, ".py");

        furi_string_left(file_path, index);

        mp_flipper_set_root_module_path(furi_string_get_cstr(file_path));

        mp_flipper_init(heap, heap_size, stack_size, &stack);

        if (is_py_file)
        {
            mp_flipper_exec_py_file(path);
        }
        else
        {
            mp_flipper_exec_mpy_file(path);
        }

        mp_flipper_deinit();

        free(heap);
    } while (false);

    furi_string_free(file_path);

    py_app_free(app);
}

PyApp *py_app_load_settings()
{
    File *file = storage_file_alloc(furi_record_open(RECORD_STORAGE));

    PyApp *settings = malloc(sizeof(PyApp));

    const size_t settings_size = sizeof(PyApp);

    FURI_LOG_I(TAG, "loading settings from \"%s\"", PYTHON_SETTINGS_PATH);
    bool fs_result = storage_file_open(file, PYTHON_SETTINGS_PATH, FSAM_READ, FSOM_OPEN_EXISTING);

    if (fs_result)
    {
        size_t bytes_count = storage_file_read(file, settings, settings_size);

        fs_result = bytes_count == settings_size;
    }

    if (fs_result)
    {
        FURI_LOG_I(TAG, "load success");
    }
    else
    {
        FURI_LOG_E(TAG, "load failed, %s", storage_file_get_error_desc(file));

        settings->heap_size = 0.3;
        settings->stack_size = 1024;
        settings->version = PYTHON_SETTINGS_VERSION;
    }

    if (fs_result && settings->version != PYTHON_SETTINGS_VERSION)
    {
        FURI_LOG_E(TAG, "version(%d != %d) mismatch", settings->version, PYTHON_SETTINGS_VERSION);
    }

    storage_file_close(file);
    storage_file_free(file);

    furi_record_close(RECORD_STORAGE);

    return settings;
};

void py_app_save_settings(PyApp *settings)
{
    File *file = storage_file_alloc(furi_record_open(RECORD_STORAGE));

    const size_t settings_size = sizeof(PyApp);

    FURI_LOG_I(TAG, "saving settings to \"%s\"", PYTHON_SETTINGS_PATH);

    bool fs_result = storage_file_open(file, PYTHON_SETTINGS_PATH, FSAM_WRITE, FSOM_CREATE_ALWAYS);

    if (fs_result)
    {
        size_t bytes_count = storage_file_write(file, settings, settings_size);

        fs_result = bytes_count == settings_size;
    }

    if (fs_result)
    {
        FURI_LOG_I(TAG, "save success");
    }
    else
    {
        FURI_LOG_E(TAG, "save failed, %s", storage_file_get_error_desc(file));
    }

    storage_file_close(file);
    storage_file_free(file);

    furi_record_close(RECORD_STORAGE);
};

PyApp *py_app_alloc()
{
    return py_app_load_settings();
}

void py_app_free(PyApp *app)
{
    free(app);
}
