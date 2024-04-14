#include <furi.h>
#include <gui/gui.h>

typedef struct {
    Gui* gui;
    ViewPort* view_port;
    Canvas* canvas;
    FuriPubSub* input_event_queue;
    FuriPubSubSubscription* input_event;
} mp_flipper_context_t;
