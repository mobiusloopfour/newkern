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

#include "hal.h"
#include "kd.h"
#include "krnl.h"
#include "multiboot.h"
#include "nkdef.h"
#include "printf.h"

uint8_t // error code
kmain(void)
{
    /* check if there is a missing
     * feature and return it's error
     * code to the hal, exiting the
     * kernel */
    uint8_t x;
    if ((x = hal_check_features())) {
        return x;
    }

    kd_log("Hello, world");
    return 0;
}
