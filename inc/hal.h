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

#ifndef HAL_H_
#define HAL_H_

#include <nkdef.h>

typedef enum hal_tty_color {
    HAL_COLOR_RESET,
    HAL_COLOR_BLACK,
    HAL_COLOR_RED,
    HAL_COLOR_GREEN,
    HAL_COLOR_ORANGE,
    HAL_COLOR_BLUE,
    HAL_COLOR_CYAN,
    HAL_COLOR_MAGENTA,
    HAL_COLOR_LIGHT_GRAY
} hal_tty_color_t;

__attribute__((noreturn)) void hal_shutdown(void);
void hal_putchar(char c);
void hal_tty_set_color(hal_tty_color_t foreground, hal_tty_color_t background);

uint8_t hal_inb(uint16_t port);
void hal_outw(uint16_t port, uint16_t data);
uint8_t hal_inb(uint16_t port);

#endif /* HAL_H_ */