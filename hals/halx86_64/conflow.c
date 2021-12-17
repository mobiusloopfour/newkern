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

#include "kd.h"
#include <hal.h>

__attribute__((noreturn)) void
hal_shutdown(void)
{
    kd_logln("Shutting down...");

    /* emulators -- qemu */
    hal_outw(0x604, 0x2000);

    /* emulators -- vbox */
    hal_outw(0x4004, 0x3400);

    /* emulators -- qemu and bochs */
    hal_outw(0xB004, 0x2000);

    for (;;)
        __asm__ volatile(
            "cli\n"
            "hlt\n");
}