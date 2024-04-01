#include <furi.h>
#include <dialogs/dialogs.h>
#include <storage/storage.h>

#include <port/micropython_embed.h>

static void load_python_file(FuriString* code) {
    Storage* storage = furi_record_open(RECORD_STORAGE);
    DialogsApp* dialogs = furi_record_open(RECORD_DIALOGS);

    File* file = storage_file_alloc(storage);
    FuriString* file_path = furi_string_alloc();
    DialogsFileBrowserOptions browser_options;

    dialog_file_browser_set_basic_options(&browser_options, "py", NULL);

    browser_options.hide_ext = false;
    browser_options.base_path = STORAGE_APP_DATA_PATH_PREFIX;

    bool result = dialog_file_browser_show(dialogs, file_path, file_path, &browser_options);

    furi_record_close(RECORD_DIALOGS);

    if(result) {
        result = storage_file_open(file, furi_string_get_cstr(file_path), FSAM_READ, FSOM_OPEN_EXISTING);
    }

    if(result) {
        size_t read = 0;
        do {
            uint8_t buffer[64] = {'\0'};

            read = storage_file_read(file, buffer, sizeof(buffer) - 1);

            for(size_t i = 0; i < read; i++) {
                furi_string_push_back(code, buffer[i]);
            }
        } while(read > 0);

        furi_string_trim(code);
    } else {
        furi_string_set(code, "print('it works!')");
    }

    storage_file_free(file);
    furi_record_close(RECORD_STORAGE);
    furi_string_free(file_path);
}

int32_t mp_flipper_app(void* p) {
    UNUSED(p);

    const size_t memory_size = memmgr_get_free_heap() * 0.5;
    const size_t stack_size = 2 * 1024;
    uint8_t* memory = malloc(memory_size * sizeof(uint8_t));

    FuriString* code = furi_string_alloc();
    load_python_file(code);

    mp_embed_init(memory + stack_size, memory_size - stack_size, memory);
    mp_embed_exec_str(furi_string_get_cstr(code));
    mp_embed_deinit();

    furi_string_free(code);
    free(memory);

    return 0;
}
