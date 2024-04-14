#include <malloc.h>

#include <furi.h>
#include <dialogs/dialogs.h>
#include <storage/storage.h>

#include <mp_flipper_runtime.h>

#include "mp_flipper_app.h"
#include "py_app.h"

const char *root_module_path;

ViewPort *mp_flipper_view_port;
FuriMessageQueue *mp_flipper_event_queue;

static void load_python_file(FuriString *file_path, FuriString *code)
{
    Storage *storage = furi_record_open(RECORD_STORAGE);
    DialogsApp *dialogs = furi_record_open(RECORD_DIALOGS);

    File *file = storage_file_alloc(storage);
    DialogsFileBrowserOptions browser_options;

    dialog_file_browser_set_basic_options(&browser_options, "py", NULL);

    browser_options.hide_ext = false;
    browser_options.base_path = STORAGE_APP_DATA_PATH_PREFIX;

    bool result = dialog_file_browser_show(dialogs, file_path, file_path, &browser_options);

    if (result)
    {
        result = storage_file_open(file, furi_string_get_cstr(file_path), FSAM_READ, FSOM_OPEN_EXISTING);
    }

    if (result)
    {
        size_t read = 0;
        do
        {
            uint8_t buffer[64] = {'\0'};

            read = storage_file_read(file, buffer, sizeof(buffer) - 1);

            for (size_t i = 0; i < read; i++)
            {
                furi_string_push_back(code, buffer[i]);
            }
        } while (read > 0);

        furi_string_trim(code);
    }
    else
    {
        furi_string_set(code, "print('it works!')");
    }

    storage_file_free(file);
    furi_record_close(RECORD_DIALOGS);
    furi_record_close(RECORD_STORAGE);
}

int32_t mp_flipper_app(void *p)
{
    UNUSED(p);

    FuriString *file_path = furi_string_alloc();
    FuriString *code = furi_string_alloc();

    load_python_file(file_path, code);

    py_app((void *)furi_string_get_cstr(file_path));

    furi_string_free(file_path);
    furi_string_free(code);

    return 0;
}
