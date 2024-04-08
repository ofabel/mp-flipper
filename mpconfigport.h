#include <stdint.h>

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

#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_BASIC_FEATURES)

#define MICROPY_ENABLE_COMPILER (1)
#define MICROPY_ENABLE_GC (1)
#define MICROPY_ENABLE_PYSTACK (0)
#define MICROPY_STACK_CHECK (1)
#define MICROPY_ALLOC_PATH_MAX (128)

#define MICROPY_ENABLE_FINALISER (1)

#define MICROPY_GC_STACK_ENTRY_TYPE uint32_t

#define MICROPY_MIN_USE_CORTEX_CPU (1)
#define MICROPY_MIN_USE_STM32_MCU (1)

#define MICROPY_HW_BOARD_NAME "Flipper Zero"
#define MICROPY_HW_MCU_NAME "STM32WB55RG"

#define MICROPY_PY___FILE__ (1)
#define MICROPY_ENABLE_EXTERNAL_IMPORT (1)
#define MICROPY_READER_VFS (1)

#define MICROPY_ENABLE_VM_ABORT (1)

#define MICROPY_PY_TIME (1)
#define MICROPY_PY_TIME_TIME_TIME_NS (1)

#define MICROPY_PY_RANDOM (1)
#define MICROPY_PY_RANDOM_EXTRA_FUNCS (1)

#define MICROPY_PY_RANDOM_SEED_INIT_FUNC (mp_flipper_seed_init())

#define MICROPY_PY_MATH (0)
#define MICROPY_PY_BUILTINS_COMPLEX (0)
#define MICROPY_FLOAT_IMPL (MICROPY_FLOAT_IMPL_FLOAT)

#define MICROPY_LONGINT_IMPL (MICROPY_LONGINT_IMPL_MPZ)

#define MICROPY_HELPER_REPL (1)
#define MICROPY_REPL_INFO (0)
#define MICROPY_REPL_EMACS_KEYS (0)
#define MICROPY_REPL_EMACS_WORDS_MOVE (0)
#define MICROPY_REPL_EMACS_EXTRA_WORDS_MOVE (0)
#define MICROPY_REPL_AUTO_INDENT (1)
#define MICROPY_REPL_EVENT_DRIVEN (0)
#define MICROPY_READLINE_HISTORY_SIZE (8)