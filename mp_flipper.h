#pragma once

#include <stddef.h>

extern const char* mp_flipper_root_module_path;

void mp_flipper_set_root_module_path(const char* path);

void mp_flipper_init(void* gc_heap, size_t gc_heap_size, void* stack_top);
void mp_flipper_exec_str(const char* str);
void mp_flipper_deinit();
