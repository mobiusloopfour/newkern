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

#include "ubsan.h"

__attribute__((noreturn))
void __ubsan_handle_shift_out_of_bounds(void* data_raw,
    void* lhs_raw,
    void* rhs_raw)
{
    struct ubsan_shift_out_of_bounds_data* data = (struct ubsan_shift_out_of_bounds_data*)data_raw;
    ubsan_value_handle_t lhs = (ubsan_value_handle_t)lhs_raw;
    ubsan_value_handle_t rhs = (ubsan_value_handle_t)rhs_raw;
    (void)lhs;
    (void)rhs;
    ubsan_abort(&data->location, "shift out of bounds");
}
