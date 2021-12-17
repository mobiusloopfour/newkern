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
#include "printf.h"

#define WIDTH 80
#define HEIGHT 25
#define START 0

static uint16_t current_width = START, current_height = 0;
const static volatile uintptr_t raw_buffer = P2V(0x000b8000);
static uint8_t color;

const static uint8_t
mk_color(const enum basic_color_t fg, const enum basic_color_t bg)
{
    return fg | bg << 4;
}

const static uint16_t
mk_entry(const uint8_t character, const uint8_t color)
{
    return (uint16_t)character | (uint16_t)color << 8;
}

static void
put_entry(const uint8_t c, const uint8_t color, const uint64_t x, const uint64_t y)
{
    const uint64_t index = y * 80 + x;
    ((uint16_t*)raw_buffer)[index] = mk_entry(c, color);
}

static void
scroll(const uint64_t line)
{
    uintptr_t loop;
    uint8_t c;

    for (loop = line * (160) + raw_buffer; loop < 80 * 2; loop++) {
        c = *(char*)loop;
        *((char*)loop - 160) = c;
    }
}

static void
del_last(void)
{
    uint64_t x;
    uintptr_t* ptr;

    for (x = 0; x < 160; x++) {
        ptr = (uintptr_t*)(raw_buffer + 160 * (HEIGHT - 1) + x);
        *ptr = 0;
    }
}

static inline void
do_putchar(const char c, const _Bool normal)
{
    uint64_t line;
    const uint8_t uc = c;
    uint8_t entry;

    if (c == '\0') {
        return;
    }

    if (normal)
        entry = color;
    else
        entry = mk_color(VGA_COLOR_WHITE, VGA_COLOR_RED);

    if (c == '\n' || c == '\r') {
        current_height++;
        current_width = 0;
    } else {
        put_entry(uc, entry, current_width, current_height);
    }

    if (++current_width == 80) {
        current_width = 0;
        if (++current_height == HEIGHT) {
            for (line = 1; line <= HEIGHT - 1; line++) {
                scroll(line);
            }
            del_last();
            current_height = HEIGHT - 1;
        }
    }
}

static void
evil_putchar(char c)
{
    do_putchar(c, 0);
}

static void
putchar(char c)
{
    do_putchar(c, 1);
}

static void
do_puts(const char* str, char normal)
{
    do {
        if (normal)
            putchar(*str);
        else
            evil_putchar(*str);
    } while (*str++);
}

void
vga_puts(const char* str)
{
    do_puts(str, 1);
}

void
vga_err(const char* str)
{
    do_puts(str, 0);
}

void
vga_clear(const enum basic_color_t fg, const basic_color_t bg)
{
    uint64_t y, x;

    color = mk_color(fg, bg);
    for (y = 0; y < HEIGHT; y++) {
        for (x = START; x < (START + WIDTH); x++) {
            const uint64_t index = y * 80 + x;
            ((uint16_t*)raw_buffer)[index] = mk_entry(' ', color);
        }
    }
}

/* for tinyprintf */
void
_putchar(const char c)
{
    putchar(c);
}

void
vga_init(void)
{
    current_width = 0;
    current_height = 0;
    vga_clear(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    printf_("\n");
}

void
vga_set_color(const enum basic_color_t fg, const enum basic_color_t bg)
{
    color = mk_color(fg, bg);
}