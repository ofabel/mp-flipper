#pragma once

#include <stddef.h>

extern const char* mp_flipper_root_module_path;

void mp_flipper_set_root_module_path(const char* path);

void mp_flipper_init(void* memory, size_t memory_size, size_t stack_size, void* stack_top);
void mp_flipper_exec_str(const char* str);
void mp_flipper_exec_file(const char* file_path);
void mp_flipper_deinit();
void mp_flipper_nlr_jump_fail(void* val);
void mp_flipper_assert(const char* file, int line, const char* func, const char* expr);
void mp_flipper_fatal_error(const char* msg);
