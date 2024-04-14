#include <malloc.h>

#include <furi.h>
#include <dialogs/dialogs.h>
#include <storage/storage.h>

#include <mp_flipper_runtime.h>

#include "mp_flipper_app.h"
#include "py_app.h"

const char* root_module_path;

ViewPort* mp_flipper_view_port;
FuriMessageQueue* mp_flipper_event_queue;

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
        py_app_file_execute(file_path);
    }

    furi_string_free(file_path);

    return 0;
}
