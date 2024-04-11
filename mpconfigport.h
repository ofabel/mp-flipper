#include <stdint.h>

#ifndef MP_FLIPPER_IS_COMPILER
#define MP_FLIPPER_IS_COMPILER (1)
#endif
#ifndef MP_FLIPPER_IS_RUNTIME
#define MP_FLIPPER_IS_RUNTIME (1)
#endif

// Type definitions for the specific machine

typedef int32_t mp_int_t; // must be pointer size
typedef uint32_t mp_uint_t; // must be pointer size
typedef long mp_off_t;

// Need to provide a declaration/definition of alloca()
#if defined(__FreeBSD__) || defined(__NetBSD__)
#include <stdlib.h>
#else
#include <alloca.h>
#endif

#define MICROPY_MPHALPORT_H "mp_flipper_halport.h"

#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_CORE_FEATURES)

#define MICROPY_PERSISTENT_CODE_LOAD (MP_FLIPPER_IS_RUNTIME)
#define MICROPY_PERSISTENT_CODE_SAVE (MP_FLIPPER_IS_COMPILER)
#define MICROPY_PERSISTENT_CODE_SAVE_FILE (0)

#define MICROPY_ENABLE_COMPILER (MP_FLIPPER_IS_COMPILER)
#define MICROPY_ENABLE_GC (1)
#define MICROPY_PY_GC_COLLECT_RETVAL (1)
#define MICROPY_ENABLE_PYSTACK (0)
#define MICROPY_STACK_CHECK (1)
#define MICROPY_ALLOC_PATH_MAX (256)

#define MICROPY_ENABLE_FINALISER (0)

#define MICROPY_ERROR_REPORTING (MICROPY_ERROR_REPORTING_TERSE)

#define MICROPY_GC_STACK_ENTRY_TYPE uint32_t

#define MICROPY_MIN_USE_CORTEX_CPU (1)
#define MICROPY_MIN_USE_STM32_MCU (1)

#define MICROPY_HW_BOARD_NAME "Flipper Zero"
#define MICROPY_HW_MCU_NAME "STM32WB55RG"

#define MICROPY_PY___FILE__ (1)
#define MICROPY_ENABLE_EXTERNAL_IMPORT (1)
#define MICROPY_READER_VFS (1)

#define MICROPY_ENABLE_VM_ABORT (0)

#define MICROPY_PY_ERRNO (0)
#define MICROPY_USE_INTERNAL_ERRNO (0)
#define MICROPY_PY_ERRNO_ERRORCODE (0)

#define MICROPY_PY_TIME (1)
#define MICROPY_PY_TIME_TIME_TIME_NS (0)

#define MICROPY_PY_RANDOM (1)
#define MICROPY_PY_RANDOM_EXTRA_FUNCS (0)

#define MICROPY_PY_RANDOM_SEED_INIT_FUNC (mp_flipper_seed_init())

#define MICROPY_PY_MATH (0)
#define MICROPY_PY_CMATH (0)
#define MICROPY_PY_BUILTINS_COMPLEX (0)
#define MICROPY_FLOAT_IMPL (MICROPY_FLOAT_IMPL_DOUBLE)

#define MICROPY_LONGINT_IMPL (MICROPY_LONGINT_IMPL_LONGLONG)

#define MICROPY_HELPER_REPL (MP_FLIPPER_IS_COMPILER)
#define MICROPY_REPL_INFO (0)
#define MICROPY_REPL_EMACS_KEYS (0)
#define MICROPY_REPL_EMACS_WORDS_MOVE (0)
#define MICROPY_REPL_EMACS_EXTRA_WORDS_MOVE (0)
#define MICROPY_REPL_AUTO_INDENT (0)
#define MICROPY_REPL_EVENT_DRIVEN (0)
#define MICROPY_READLINE_HISTORY_SIZE (0)

#define MICROPY_CPYTHON_COMPAT (1)
#define MICROPY_FULL_CHECKS (1)

#define MICROPY_MODULE_FROZEN_MPY (0)

#define MICROPY_MULTIPLE_INHERITANCE (0)
#define MICROPY_PY_FUNCTION_ATTRS (1)
#define MICROPY_PY_DESCRIPTORS (0)
#define MICROPY_PY_ASYNC_AWAIT (0)
#define MICROPY_PY_ASSIGN_EXPR (0)
#define MICROPY_PY_GENERATOR_PEND_THROW (0)
#define MICROPY_PY_BUILTINS_COMPILE (0)
#define MICROPY_PY_BUILTINS_EVAL_EXEC (0)
#define MICROPY_PY_BUILTINS_EXECFILE (0)
#define MICROPY_PY_BUILTINS_INPUT (0)
#define MICROPY_PY_COLLECTIONS (0)
#define MICROPY_PY_IO (0)
#define MICROPY_PY_STRUCT (0)
#define MICROPY_PY_SYS (0)
#define MICROPY_PY_SYS_MODULES (0)
#define MICROPY_PY_SELECT_SELECT (0)
#define MICROPY_PY_JSON (0)
#define MICROPY_PY_RE (0)
#define MICROPY_PY_CRYPTOLIB (0)
#define MICROPY_PY_VFS (0)
