#include <string.h>

#include "py/compile.h"
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

void mp_flipper_exec_str(const char* code) {
    nlr_buf_t nlr;

    if(nlr_push(&nlr) == 0) {
        // Compile, parse and execute the given string.
        mp_lexer_t* lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, code, strlen(code), 0);
        qstr source_name = lex->source_name;
        mp_store_global(MP_QSTR___file__, MP_OBJ_NEW_QSTR(source_name));
        mp_parse_tree_t parse_tree = mp_parse(lex, MP_PARSE_FILE_INPUT);
        mp_obj_t module_fun = mp_compile(&parse_tree, source_name, true);
        mp_call_function_0(module_fun);
        nlr_pop();
    } else {
        // Uncaught exception: print it out.
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
    }
}

void mp_flipper_exec_file(const char* file_path) {
    nlr_buf_t nlr;

    if(nlr_push(&nlr) == 0) {
        // Compile, parse and execute the given string.
        mp_lexer_t* lex = mp_lexer_new_from_file(qstr_from_str(file_path));
        qstr source_name = lex->source_name;
        mp_store_global(MP_QSTR___file__, MP_OBJ_NEW_QSTR(source_name));
        mp_parse_tree_t parse_tree = mp_parse(lex, MP_PARSE_FILE_INPUT);
        mp_obj_t module_fun = mp_compile(&parse_tree, source_name, false);
        mp_call_function_0(module_fun);
        nlr_pop();
    } else {
        // Uncaught exception: print it out.
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
    }
}

void mp_flipper_deinit() {
    mp_deinit();
}

// Called if an exception is raised outside all C exception-catching handlers.
void nlr_jump_fail(void* val) {
    mp_flipper_nlr_jump_fail(val);
}

#if MICROPY_ENABLE_GC
// Run a garbage collection cycle.
void gc_collect(void) {
    gc_collect_start();
    gc_helper_collect_regs_and_stack();
    gc_collect_end();
}
#endif

#ifndef NDEBUG
// Used when debugging is enabled.
void __assert_func(const char* file, int line, const char* func, const char* expr) {
    mp_flipper_assert_func(file, line, func, expr);
}

void NORETURN __fatal_error(const char* msg) {
    mp_flipper_fatal_error(msg);
}
#endif
