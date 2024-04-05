#pragma once

#include <stddef.h>
#include <stdint.h>

void* mp_flipper_file_reader_context_alloc(const char* filename);

void mp_flipper_file_reader_context_free(void* data);

uint32_t mp_flipper_file_reader_read(void* data);

void mp_flipper_file_reader_close(void* data);
