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

#define MICROPY_MIN_USE_CORTEX_CPU (1)
#define MICROPY_MIN_USE_STM32_MCU (1)

#define MICROPY_HW_BOARD_NAME "Flipper Zero"
#define MICROPY_HW_MCU_NAME "STM32WB55RG"

#define MICROPY_ENABLE_EXTERNAL_IMPORT (1)
#define MICROPY_READER_VFS (1)

#define MICROPY_PY_TIME (1)
#define MICROPY_PY_TIME_TIME_TIME_NS (1)

#define MICROPY_PY_RANDOM (1)
#define MICROPY_PY_RANDOM_EXTRA_FUNCS (1)

#define MICROPY_PY_RANDOM_SEED_INIT_FUNC (mp_flipper_seed_init())

#define MICROPY_PY_MATH (0)
#define MICROPY_PY_BUILTINS_COMPLEX (0)
#define MICROPY_FLOAT_IMPL (MICROPY_FLOAT_IMPL_FLOAT)
