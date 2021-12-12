/*
 * Copyright (c) 2021 MobiusLoopFour. All rights reserved.
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the GNU General Public License
 * Version 3.0 or later (the 'License'). You may not use this file except in
 * compliance with the License.
 *
 * Please obtain a copy of the License at
 * https://www.gnu.org/licenses/gpl-3.0.en.html and read it before using
 * this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND THE DEVELOPER HEREBY DISCLAIMS ALL SUCH
 * WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 */

#ifndef UBSAN_H_
#define UBSAN_H_

#include <nkdef.h>

struct ubsan_source_location {
    const char* file;
    uint32_t line;
    uint32_t column;
};

struct ubsan_type_descriptor {
    uint16_t type_kind;
    uint16_t type_info;
    char* type_name;
};

struct ubsan_type_mismatch_data {
    struct ubsan_source_location location;
    struct ubsan_type_descriptor* type;
    uintptr_t alignment;
    unsigned char type_check_kind;
};

struct ubsan_overflow_data {
    struct ubsan_source_location location;
    struct ubsan_type_descriptor* type;
};

struct ubsan_shift_out_of_bounds_data {
    struct ubsan_source_location location;
    struct ubsan_type_descriptor* lhs_type;
    struct ubsan_type_descriptor* rhs_type;
};

struct ubsan_out_of_bounds_data {
    struct ubsan_source_location location;
    struct ubsan_type_descriptor* array_type;
    struct ubsan_type_descriptor* index_type;
};

struct ubsan_unreachable_data {
    struct ubsan_source_location location;
};

struct ubsan_pointer_overflow_data {
    struct ubsan_source_location location;
};

struct ubsan_vla_bound_data {
    struct ubsan_source_location location;
    struct ubsan_type_descriptor* type;
};

struct ubsan_float_cast_overflow_data {
    struct ubsan_source_location location;
    struct ubsan_type_descriptor* from_type;
    struct ubsan_type_descriptor* to_type;
};

struct ubsan_invalid_value_data {
    struct ubsan_source_location location;
    struct ubsan_type_descriptor* type;
};

struct ubsan_function_type_mismatch_data {
    struct ubsan_source_location location;
    struct ubsan_type_descriptor* type;
};

struct ubsan_nonnull_return_data {
    struct ubsan_source_location location;
    struct ubsan_source_location attr_location;
};

struct ubsan_nonnull_arg_data {
    struct ubsan_source_location location;
    struct ubsan_source_location attr_location;
};

struct ubsan_cfi_bad_icall_data {
    struct ubsan_source_location location;
    struct ubsan_type_descriptor* type;
};

typedef uintptr_t ubsan_value_handle_t;

__attribute__((noreturn)) void ubsan_abort(struct ubsan_source_location* location, const char* violation);

#endif /* UBSAN_H_ */