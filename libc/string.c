#include <stddef.h>
#include <stdint.h>

void *
memmove (void *dstptr, const void *srcptr, size_t size)
{
    unsigned char *dst = (unsigned char *)dstptr;
    const unsigned char *src = (const unsigned char *)srcptr;
    if (dst < src)
        {
            size_t i;
            for (i = 0; i < size; i++)
                dst[i] = src[i];
        }
    else
        {
            size_t i;
            for (i = size; i != 0; i--)
                dst[i - 1] = src[i - 1];
        }
    return dstptr;
}

size_t
strlen (const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

int
memcmp (const void *aptr, const void *bptr, size_t size)
{
    size_t i;
    const unsigned char *a = (const unsigned char *)aptr;
    const unsigned char *b = (const unsigned char *)bptr;
    for (i = 0; i < size; i++)
        {
            if (a[i] < b[i])
                return -1;
            else if (b[i] < a[i])
                return 1;
        }
    return 0;
}

void *
memset (void *bufptr, int value, size_t size)
{
    size_t i;
    unsigned char *buf = (unsigned char *)bufptr;
    for (i = 0; i < size; i++)
        buf[i] = (unsigned char)value;
    return bufptr;
}

void *
memcpy (void *dstptr, const void *srcptr, size_t size)
{
    size_t i;
    unsigned char *dst = (unsigned char *)dstptr;
    const unsigned char *src = (const unsigned char *)srcptr;
    for (i = 0; i < size; i++)
        dst[i] = src[i];
    return dstptr;
}