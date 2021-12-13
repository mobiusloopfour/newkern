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
#include <kd.h>

__attribute__((noreturn))
void __ubsan_handle_divrem_overflow(const void* data_raw,
    const void* lhs_raw,
    const void* rhs_raw)
{
    const struct ubsan_overflow_data* data = (const struct ubsan_overflow_data*)data_raw;
    const ubsan_value_handle_t lhs = (const ubsan_value_handle_t)lhs_raw;
    const ubsan_value_handle_t rhs = (const ubsan_value_handle_t)rhs_raw;
    (void)lhs;
    (void)rhs;
    ubsan_abort(&data->location, "division remainder overflow");
}
