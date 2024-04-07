#include "port/micropython_embed.h"
#include "py/runtime.h"
#include "py/gc.h"
#include "py/stackctrl.h"
#include "shared/runtime/gchelper.h"
#include "mp_flipper.h"

const char* mp_flipper_root_module_path;

void mp_flipper_set_root_module_path(const char* path) {
    mp_flipper_root_module_path = path;
}

void mp_flipper_init(void* heap, size_t heap_size, size_t stack_size, void* stack_top) {
    mp_stack_set_top(stack_top);
    mp_stack_set_limit(stack_size);

    gc_init(heap, (uint8_t*)heap + heap_size);

    mp_init();
}

void mp_flipper_exec_str(const char* str) {
    mp_embed_exec_str(str);
}

void mp_flipper_deinit() {
    mp_embed_deinit();
}
