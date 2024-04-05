#include "port/micropython_embed.h"
#include "mp_flipper.h"

const char* mp_flipper_root_module_path;

void mp_flipper_set_root_module_path(const char* path) {
    mp_flipper_root_module_path = path;
}

void mp_flipper_init(void* gc_heap, size_t gc_heap_size, void* stack_top) {
    mp_embed_init(gc_heap, gc_heap_size, stack_top);
}

void mp_flipper_exec_str(const char* str) {
    mp_embed_exec_str(str);
}

void mp_flipper_deinit() {
    mp_embed_deinit();
}
