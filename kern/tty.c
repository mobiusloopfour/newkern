#include <sys/vga.h>
#include <string.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;

static size_t ttyrow;
static size_t ttycol;
static uint8_t ttyclr;
static uint16_t *ttybuf;

/* Init terminal
 */
void
ttyini (void)
{
    ttyrow = 0;
    ttycol = 0;
    ttyclr = ttymkc (VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    ttybuf = VGA_MEMORY;
    size_t y, x;
    for (y = 0; y < VGA_HEIGHT; y++)
        {
            for (x = 0; x < VGA_WIDTH; x++)
                {
                    const size_t index = y * VGA_WIDTH + x;
                    ttybuf[index] = vga_entry (' ', ttyclr);
                }
        }
}

/* Set terminal color
 */
void
ttysetc (uint8_t color)
{
    ttyclr = color;
}

/* Entry at x, y
 */
void
ttyeat (unsigned char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    ttybuf[index] = vga_entry (c, color);
}

/* Scroll
 */
void
ttyscl (int line)
{
    int loop;
    char c;

    for (loop = line * (VGA_WIDTH * 2) + 0xB8000; loop < VGA_WIDTH * 2; loop++)
        {
            c = *(char*)loop;
            *((char*)loop - (VGA_WIDTH * 2)) = c;
        }
}

/* Delete last line
 */
void
ttydll ()
{
    int x, *ptr;

    for (x = 0; x < VGA_WIDTH * 2; x++)
        {
            ptr = (void*)(0xB8000 + (VGA_WIDTH * 2) * (VGA_HEIGHT - 1) + x);
            *ptr = 0;
        }
}

/* Put character
 */
void
ttyputc (char c)
{
    int line;
    unsigned char uc = c;

    if (c == '\n' || c == '\r')
        {
            ttyrow++;
            ttycol = 0;
            return;
        }

    ttyeat (uc, ttyclr, ttycol, ttyrow);
    if (++ttycol == VGA_WIDTH)
        {
            ttycol = 0;
            if (++ttyrow == VGA_HEIGHT)
                {
                    for (line = 1; line <= VGA_HEIGHT - 1; line++)
                        {
                            ttyscl (line);
                        }
                    ttydll ();
                    ttyrow = VGA_HEIGHT - 1;
                }
        }
}

/* Write to terminal
 */
void
ttyw (const char *data, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++)
        ttyputc (data[i]);
}

/* Write string to terminal
 */
void
ttystr (const char *data)
{
    ttyw (data, strlen (data));
}