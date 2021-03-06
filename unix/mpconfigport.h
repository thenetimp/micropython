/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// options to control how Micro Python is built

#define MICROPY_EMIT_X64            (1)
#define MICROPY_EMIT_THUMB          (0)
#define MICROPY_EMIT_INLINE_THUMB   (0)
#define MICROPY_ENABLE_GC           (1)
#define MICROPY_ENABLE_FINALISER    (1)
#define MICROPY_ENABLE_FROZENSET    (1)
#define MICROPY_MEM_STATS           (1)
#define MICROPY_DEBUG_PRINTERS      (1)
#define MICROPY_ENABLE_REPL_HELPERS (1)
#define MICROPY_ENABLE_LEXER_UNIX   (1)
#define MICROPY_ENABLE_SOURCE_LINE  (1)
#define MICROPY_FLOAT_IMPL          (MICROPY_FLOAT_IMPL_DOUBLE)
#define MICROPY_LONGINT_IMPL        (MICROPY_LONGINT_IMPL_MPZ)
#define MICROPY_PATH_MAX            (PATH_MAX)
#define MICROPY_STREAMS_NON_BLOCK   (1)
#define MICROPY_USE_COMPUTED_GOTO   (1)
#define MICROPY_MOD_SYS_EXIT        (1)
#define MICROPY_MOD_SYS_STDFILES    (1)
#define MICROPY_ENABLE_MOD_CMATH    (1)
// Define to MICROPY_ERROR_REPORTING_DETAILED to get function, etc.
// names in exception messages (may require more RAM).
#define MICROPY_ERROR_REPORTING     (MICROPY_ERROR_REPORTING_DETAILED)

extern const struct _mp_obj_module_t mp_module_time;
extern const struct _mp_obj_module_t mp_module_socket;
extern const struct _mp_obj_module_t mp_module_ffi;

#if MICROPY_MOD_FFI
#define MICROPY_MOD_FFI_DEF { MP_OBJ_NEW_QSTR(MP_QSTR_ffi), (mp_obj_t)&mp_module_ffi },
#else
#define MICROPY_MOD_FFI_DEF
#endif
#if MICROPY_MOD_TIME
#define MICROPY_MOD_TIME_DEF { MP_OBJ_NEW_QSTR(MP_QSTR_time), (mp_obj_t)&mp_module_time },
#else
#define MICROPY_MOD_TIME_DEF
#endif

#define MICROPY_EXTRA_BUILTIN_MODULES \
    MICROPY_MOD_FFI_DEF \
    MICROPY_MOD_TIME_DEF \
    { MP_OBJ_NEW_QSTR(MP_QSTR_microsocket), (mp_obj_t)&mp_module_socket }, \

// type definitions for the specific machine

#ifdef __LP64__
typedef long machine_int_t; // must be pointer size
typedef unsigned long machine_uint_t; // must be pointer size
#else
// These are definitions for machines where sizeof(int) == sizeof(void*),
// regardless for actual size.
typedef int machine_int_t; // must be pointer size
typedef unsigned int machine_uint_t; // must be pointer size
#endif

#define BYTES_PER_WORD sizeof(machine_int_t)

typedef void *machine_ptr_t; // must be of pointer size
typedef const void *machine_const_ptr_t; // must be of pointer size

extern const struct _mp_obj_fun_native_t mp_builtin_input_obj;
extern const struct _mp_obj_fun_native_t mp_builtin_open_obj;
#define MICROPY_EXTRA_BUILTINS \
    { MP_OBJ_NEW_QSTR(MP_QSTR_input), (mp_obj_t)&mp_builtin_input_obj }, \
    { MP_OBJ_NEW_QSTR(MP_QSTR_open), (mp_obj_t)&mp_builtin_open_obj },
