#pragma once

#include <stddef.h>

#include "py/mperrno.h"

extern const char* mp_flipper_root_module_path;

void mp_flipper_set_root_module_path(const char* path);

void mp_flipper_init(void* memory, size_t memory_size, size_t stack_size, void* stack_top);
void mp_flipper_exec_str(const char* str);
void mp_flipper_exec_py_file(const char* file_path);
void mp_flipper_exec_mpy_file(const char* file_path);
void mp_flipper_compile_and_save_file(const char* py_file_path, const char* mpy_file_path);
void mp_flipper_save_file(const char* file_path, const char* data, size_t size);
void mp_flipper_deinit();
void mp_flipper_nlr_jump_fail(void* value);
void mp_flipper_assert(const char* file, int line, const char* func, const char* expr);
void mp_flipper_fatal_error(const char* msg);
void mp_flipper_raise_os_error(int errno);
void mp_flipper_raise_os_error_with_filename(int errno, const char* filename);
const char* mp_flipper_print_get_data(void* data);
size_t mp_flipper_print_get_data_length(void* data);
void* mp_flipper_print_data_alloc();
void mp_flipper_print_strn(void* data, const char* str, size_t length);
void mp_flipper_print_data_free(void* data);
