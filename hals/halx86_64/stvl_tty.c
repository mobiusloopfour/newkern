#include "stvl.h"
#include <hal.h>
#include <nkdef.h>

typedef void (*term_writer_t)(const char* string, size_t length);
static _Bool initialized = 0;
static term_writer_t writer;

static char* codes_fg[] = {
    [HAL_COLOR_BLACK] = "\033[30m",
    [HAL_COLOR_RED] = "\033[31m",
    [HAL_COLOR_GREEN] = "\033[32m",
    [HAL_COLOR_ORANGE] = "\033[33m",
    [HAL_COLOR_BLUE] = "\033[34m",
    [HAL_COLOR_MAGENTA] = "\033[35m",
    [HAL_COLOR_CYAN] = "\033[36m",
    [HAL_COLOR_LIGHT_GRAY] = "\033[37m",
};

static char* codes_bg[] = {
    [HAL_COLOR_BLACK] = "\033[40m",
    [HAL_COLOR_RED] = "	\033[41m",
    [HAL_COLOR_GREEN] = "\033[42m",
    [HAL_COLOR_ORANGE] = "\033[43m",
    [HAL_COLOR_BLUE] = "\033[44m",
    [HAL_COLOR_MAGENTA] = "\033[45m",
    [HAL_COLOR_CYAN] = "\033[46m",
    [HAL_COLOR_LIGHT_GRAY] = "\033[47m",
};

void
hal_putchar(char c)
{
    if (!initialized) {
        return;
    } else {
        writer(&c, 1);
    }
}

#define CBUF 6
#define CBUFL 7

void
hal_tty_set_color(hal_tty_color_t fg, hal_tty_color_t bg)
{
    if (fg == HAL_COLOR_RESET) {
        writer(codes_fg[HAL_COLOR_GREEN], CBUF);
    } else {
        writer(codes_fg[fg], CBUF);
    }
    if (bg == HAL_COLOR_RESET) {
        writer(codes_bg[HAL_COLOR_BLACK], CBUF);
    } else {
        writer(codes_bg[bg], CBUF);
    }
}

void
tty_init(stivale2_struct_t* st)
{
    if (initialized) {
        return; /* not an error really */
    }

    /* get terminal writer tag */
    struct stivale2_struct_tag_terminal* term_str_tag;
    term_str_tag = stivale2_get_tag(st, STIVALE2_STRUCT_TAG_TERMINAL_ID);

    if (term_str_tag == NULL) {
        /* cannot call hal_shutdown because it prints stuff */
        for (;;) {
            __asm__("hlt");
        }
    }

    void* term_write_ptr = (void*)term_str_tag->term_write;
    writer = term_write_ptr;

    initialized = 1;
    hal_tty_set_color(HAL_COLOR_RESET, HAL_COLOR_RESET);

    for (size_t y = 0; y < (160 * 90); y ++) {
        writer(" ", 1);
    }
    writer("\n", 1);
}
