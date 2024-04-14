#pragma once

#include <stdbool.h>

#include <gui/gui.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_PIXEL_PER_ITEM 32

extern ViewPort* mp_flipper_view_port;
extern FuriMessageQueue* mp_flipper_event_queue;

extern const char* root_module_path;
