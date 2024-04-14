#include <gui/gui.h>
#include <gui/modules/variable_item_list.h>
#include <gui/view_dispatcher.h>
#include <lib/toolbox/value_index.h>

#include "py_app.h"

typedef struct {
    Gui* gui;
    PyApp* settings;
    ViewDispatcher* view_dispatcher;
    VariableItemList* items;
} PyAppSettings;

#define STACK_SIZE 3
const char* const stack_size_text[STACK_SIZE] = {
    "512",
    "1024",
    "2048",
};
const int32_t stack_size[STACK_SIZE] = {
    512,
    1024,
    2048,
};

#define HEAP_SIZE 5
const char* const heap_size_text[HEAP_SIZE] = {
    "10%",
    "20%",
    "30%",
    "40%",
    "50%",
};
const float heap_size[HEAP_SIZE] = {
    0.1,
    0.2,
    0.3,
    0.4,
    0.5,
};

static void set_stack_size(VariableItem* item) {
    PyAppSettings* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);

    variable_item_set_current_value_text(item, stack_size_text[index]);
    app->settings->stack_size = stack_size[index];
}

static void set_heap_size(VariableItem* item) {
    PyAppSettings* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);

    variable_item_set_current_value_text(item, heap_size_text[index]);
    app->settings->heap_size = heap_size[index];
}

static uint32_t py_app_settings_exit(void* context) {
    UNUSED(context);
    return VIEW_NONE;
}

static PyAppSettings* alloc_settings(void) {
    PyAppSettings* app = malloc(sizeof(PyAppSettings));

    app->gui = furi_record_open(RECORD_GUI);
    app->settings = py_app_load_settings();
    app->items = variable_item_list_alloc();

    View* view = variable_item_list_get_view(app->items);

    view_set_previous_callback(view, py_app_settings_exit);

    VariableItem* item;
    uint8_t value_index;

    item = variable_item_list_add(app->items, "Stack Size", STACK_SIZE, set_stack_size, app);
    value_index = value_index_int32(app->settings->stack_size, stack_size, STACK_SIZE);
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, stack_size_text[value_index]);

    item = variable_item_list_add(app->items, "Heap Size", HEAP_SIZE, set_heap_size, app);
    value_index = value_index_float(app->settings->heap_size, heap_size, HEAP_SIZE);
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, heap_size_text[value_index]);

    app->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(app->view_dispatcher);
    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);
    view_dispatcher_add_view(app->view_dispatcher, 0, view);
    view_dispatcher_switch_to_view(app->view_dispatcher, 0);

    return app;
}

static void free_settings(PyAppSettings* app) {
    view_dispatcher_remove_view(app->view_dispatcher, 0);
    variable_item_list_free(app->items);
    view_dispatcher_free(app->view_dispatcher);

    free(app->settings);

    furi_record_close(RECORD_GUI);
    free(app);
}

int32_t py_app_settings_app(void* p) {
    UNUSED(p);
    PyAppSettings* app = alloc_settings();
    view_dispatcher_run(app->view_dispatcher);
    py_app_save_settings(app->settings);
    free_settings(app);
    return 0;
}
