#include <malloc.h>

#include <furi.h>
#include <dialogs/dialogs.h>
#include <storage/storage.h>

#include <port/micropython_embed.h>

#include "mp_flipper_app.h"

const char* root_module_path;

uint32_t* mp_flipper_canvas;
ViewPort* mp_flipper_view_port;
FuriMessageQueue* mp_flipper_event_queue;

static void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);

    uint8_t x = 0, y = 0;
    size_t i = 0;
    uint32_t mask = 1;
    Color color = ColorBlack;

    for(size_t index = 0; index < (SCREEN_WIDTH * SCREEN_HEIGHT) / SCREEN_PIXEL_PER_ITEM; index++) {
        for(i = 0, mask = 1; i < SCREEN_PIXEL_PER_ITEM; i++, mask <<= 1) {
            color = (mp_flipper_canvas[index] & mask) > 0 ? ColorBlack : ColorWhite;

            canvas_set_color(canvas, color);
            canvas_draw_dot(canvas, x, y);

            if(++x % SCREEN_WIDTH == 0) {
                x = 0;
                y++;
            }
        }
    }
}

static void load_python_file(FuriString* file_path, FuriString* code) {
    Storage* storage = furi_record_open(RECORD_STORAGE);
    DialogsApp* dialogs = furi_record_open(RECORD_DIALOGS);

    File* file = storage_file_alloc(storage);
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
}

int32_t mp_flipper_app(void* p) {
    UNUSED(p);

    mp_flipper_canvas = malloc(((SCREEN_WIDTH * SCREEN_HEIGHT) / SCREEN_PIXEL_PER_ITEM) * sizeof(uint32_t));

    const size_t memory_size = memmgr_get_free_heap() * 0.5;
    const size_t stack_size = 2 * 1024;
    uint8_t* memory = malloc(memory_size * sizeof(uint8_t));

    FuriString* file_path = furi_string_alloc();
    FuriString* code = furi_string_alloc();

    load_python_file(file_path, code);

    FURI_LOG_I(TAG, "allocated memory is %zu bytes", memory_size);
    FURI_LOG_I(TAG, "stack size is %zu bytes", stack_size);
    FURI_LOG_I(TAG, "executing python script %s", furi_string_get_cstr(file_path));

    size_t index = furi_string_search_rchar(file_path, '/');

    furi_check(index != FURI_STRING_FAILURE);

    furi_string_left(file_path, index);

    root_module_path = furi_string_get_cstr(file_path);

    // initialize view port
    mp_flipper_view_port = view_port_alloc();
    view_port_draw_callback_set(mp_flipper_view_port, draw_callback, NULL);

    // initialize GUI
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, mp_flipper_view_port, GuiLayerFullscreen);

    mp_embed_init(memory + stack_size, memory_size - stack_size, memory);
    mp_embed_exec_str(furi_string_get_cstr(code));
    mp_embed_deinit();

    // destroy GUI and view port
    gui_remove_view_port(gui, mp_flipper_view_port);
    view_port_free(mp_flipper_view_port);
    furi_record_close(RECORD_GUI);

    furi_string_free(file_path);
    furi_string_free(code);
    free(memory);

    free(mp_flipper_canvas);

    return 0;
}
