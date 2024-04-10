#include <string.h>

#include "py/compile.h"
#include "py/runtime.h"
#include "py/persistentcode.h"
#include "py/gc.h"
#include "py/stackctrl.h"
#include "shared/runtime/gchelper.h"

#include "mp_flipper.h"
#include "mp_flipper_halport.h"

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
        // Compile, parse and execute the given string
        mp_lexer_t* lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, code, strlen(code), 0);
        mp_store_global(MP_QSTR___file__, MP_OBJ_NEW_QSTR(lex->source_name));
        mp_parse_tree_t parse_tree = mp_parse(lex, MP_PARSE_FILE_INPUT);
        mp_obj_t module_fun = mp_compile(&parse_tree, lex->source_name, true);
        mp_call_function_0(module_fun);
        nlr_pop();
    } else {
        // Uncaught exception: print it out.
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
    }
}

void mp_flipper_exec_py_file(const char* file_path) {
    nlr_buf_t nlr;

    if(nlr_push(&nlr) == 0) {
        do {
            // check if file exists
            if(mp_flipper_import_stat(file_path) == MP_FLIPPER_IMPORT_STAT_NO_EXIST) {
                mp_raise_OSError_with_filename(MP_ENOENT, file_path);

                break;
            }

            // Compile, parse and execute the given file
            mp_lexer_t* lex = mp_lexer_new_from_file(qstr_from_str(file_path));
            mp_store_global(MP_QSTR___file__, MP_OBJ_NEW_QSTR(lex->source_name));
            mp_parse_tree_t parse_tree = mp_parse(lex, MP_PARSE_FILE_INPUT);
            mp_obj_t module_fun = mp_compile(&parse_tree, lex->source_name, false);
            mp_call_function_0(module_fun);
        } while(false);

        nlr_pop();
    } else {
        // Uncaught exception: print it out.
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
    }
}

void mp_flipper_exec_mpy_file(const char* file_path) {
    nlr_buf_t nlr;
    if(nlr_push(&nlr) == 0) {
        do {
            // check if file exists
            if(mp_flipper_import_stat(file_path) == MP_FLIPPER_IMPORT_STAT_NO_EXIST) {
                mp_raise_OSError_with_filename(MP_ENOENT, file_path);

                break;
            }

            // Execute the given .mpy file
            mp_module_context_t* context = m_new_obj(mp_module_context_t);
            context->module.globals = mp_globals_get();
            mp_compiled_module_t compiled_module;
            compiled_module.context = context;
            mp_raw_code_load_file(qstr_from_str(file_path), &compiled_module);
            mp_obj_t f = mp_make_function_from_proto_fun(compiled_module.rc, context, MP_OBJ_NULL);
            mp_call_function_0(f);
        } while(false);
        nlr_pop();
    } else {
        // Uncaught exception: print it out.
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
    }
}

void mp_flipper_compile_and_save_file(const char* py_file_path, const char* mpy_file_path) {
    mp_lexer_t* lex = mp_lexer_new_from_file(qstr_from_str(py_file_path));

    qstr source_name = qstr_from_str(lex->source_name);

    mp_store_global(MP_QSTR___file__, MP_OBJ_NEW_QSTR(lex->source_name));

    mp_parse_tree_t parse_tree = mp_parse(lex, MP_PARSE_FILE_INPUT);
    mp_compiled_module_t cm;
    cm.context = m_new_obj(mp_module_context_t);
    mp_compile_to_raw_code(&parse_tree, lex->source_name, false, &cm);

    mp_print_t* print = malloc(sizeof(mp_print_t));

    print->data = mp_flipper_print_data_alloc();
    print->print_strn = mp_flipper_print_strn;

    mp_raw_code_save(&cm, print);

    const char* data = mp_flipper_print_get_data(print->data);
    size_t size = mp_flipper_print_get_data_length(print->data);

    mp_flipper_save_file(mpy_file_path, data, size);

    mp_flipper_print_data_free(print->data);

    free(print);
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
    mp_flipper_assert(file, line, func, expr);
}

void NORETURN __fatal_error(const char* msg) {
    mp_flipper_fatal_error(msg);
}
#endif

void mp_flipper_raise_os_error(int errno) {
    mp_raise_OSError(errno);
}

void mp_flipper_raise_os_error_with_filename(int errno, const char* filename) {
    mp_raise_OSError_with_filename(errno, filename);
}
