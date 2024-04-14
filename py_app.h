#pragma once

#include <furi.h>

#define TAG "uPython"

typedef struct {
    size_t stack_size;
    float heap_size;
    uint8_t version;
} PyApp;

int32_t py_app(void* arg);

void py_app_file_execute(FuriString* file);

PyApp* py_app_load_settings();
void py_app_save_settings(PyApp* settings);

PyApp* py_app_alloc();
void py_app_free(PyApp* app);
