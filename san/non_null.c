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
#include <nkdef.h>

void
__ubsan_handle_nonnull_return(const void* data_raw)
{
    const struct ubsan_nonnull_return_data* data = (struct ubsan_nonnull_return_data*)data_raw;
    ubsan_abort(&data->location, "null return");
}

void
__ubsan_handle_nonnull_arg(const void* data_raw,
    const intptr_t index_raw)
{
    const struct ubsan_nonnull_arg_data* data = (const struct ubsan_nonnull_arg_data*)data_raw;
    const ubsan_value_handle_t index = (const ubsan_value_handle_t)index_raw;
    (void)index;
    ubsan_abort(&data->location, "null argument");
}
