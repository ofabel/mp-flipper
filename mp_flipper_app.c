#include <furi.h>

#include <port/micropython_embed.h>

int32_t mp_flipper_app(void* p) {
    UNUSED(p);

    const size_t memory_size = memmgr_get_free_heap() * 0.5;
    const size_t stack_size = 2 * 1024;
    uint8_t* memory = malloc(memory_size * sizeof(uint8_t));

    mp_embed_init(memory + stack_size, memory_size - stack_size, memory);
    mp_embed_exec_str("print('hello world!');");
    mp_embed_deinit();

    free(memory);

    return 0;
}
