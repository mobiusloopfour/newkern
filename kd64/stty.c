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

#include "def_video.h"
#include "nkdef.h"
#include "offsets.h"
#include "kd.h"
#include "stdarg.h"
#include "printf.h"

extern int evil_printf_(const char str[], ...);

int kd_log(const char* format, ...)
{
    va_list va;
    va_start(va, format);
    char buffer[1];
    const int ret = vprintf_(format, va);
    va_end(va);
    return ret;
}

#if 0
void kd_log(const char* str, ...)
{
    vga_puts(str);
}

#endif

int kd_err(const char* format, ...)
{
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_RED);
    va_list va;
    va_start(va, format);
    char buffer[1];
    const int ret = vprintf_(format, va);
    va_end(va);
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    return ret;
}

int kd_errln(const char* str)
{
    return kd_err("\n[*] %s\n", str);
}

int kd_logln(const char* str)
{
    return kd_log("\n[*] %s\n", str);
}