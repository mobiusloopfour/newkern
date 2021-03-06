#include "kd.h"
#include "stvl.h"
#include <hal.h>
#include <nkdef.h>
#include <printf.h>
#include <kd.h>

/* too little code to make a header for this */
extern uint8_t kmain(void);
extern void tty_init(stivale2_struct_t* st);

uint8_t stack[8192];

/* stivale2 offers a runtime terminal service which can be ditched at any
 * time, but it provides an easy way to print out to graphical terminal,
 * especially during early boot. */
static struct stivale2_header_tag_terminal terminal_hdr_tag = {
    /* All tags need to begin with an identifier and a pointer to the next tag. */
    .tag = {
        /* Identification constant defined in stivale2.h and the specification. */
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        /* If next is 0, it marks the end of the linked list of header tags. */
        .next = 0 },
    /* The terminal header tag possesses a flags field, leave it as 0 for now
     * as it is unused. */
    .flags = (uint64_t)NULL
};

/* This tag tells the bootloader that we want a graphical framebuffer instead
 * of a CGA-compatible text mode. Omitting this tag will make the bootloader
 * default to text mode, if available. */
static struct stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
    /* Same as above. */
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        /* Instead of 0, we now point to the previous header tag. The order in
         * which header tags are linked does not matter. */
        .next = (uint64_t)&terminal_hdr_tag },
    /* We set all the framebuffer specifics to 0 as we want the bootloader
     * to pick the best it can. */
    .framebuffer_width = 1280,
    .framebuffer_height = 720,
    .framebuffer_bpp = 0
};

__attribute__((section(".stivale2hdr"), used)) static struct stivale2_header stivale_hdr = {
    /* The entry_point member is used to specify an alternative entry
     * point that the bootloader should jump to instead of the executable's
     * ELF entry point. We do not care about that so we leave it zeroed. */
    .entry_point = 0,
    /* Let's tell the bootloader where our stack is.
     * We need to add the sizeof(stack) since in x86(_64) the stack grows
     * downwards. */
    .stack = (uintptr_t)stack + sizeof(stack),
    /* Bit 1, if set, causes the bootloader to return to us pointers in the
     * higher half, which we likely want since this is a higher half kernel.
     * Bit 2, if set, tells the bootloader to enable protected memory ranges,
     * that is, to respect the ELF PHDR mandated permissions for the executable's
     * segments.
     * Bit 3, if set, enables fully virtual kernel mappings, which we want as
     * they allow the bootloader to pick whichever *physical* memory address is
     * available to load the kernel, rather than relying on us telling it where
     * to load it.
     * Bit 4 disables a deprecated feature and should always be set. */
    .flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4),
    /* This header structure is the root of the linked list of header tags and
     * points to the first one in the linked list. */
    .tags = (uintptr_t)&framebuffer_hdr_tag
};

/* retrieve from linked list */
void*
stivale2_get_tag(stivale2_struct_t* stivale2_struct, uint64_t id)
{
    struct stivale2_tag* current_tag = (void*)stivale2_struct->tags;
    for (;;) {
        if ((!current_tag) || current_tag->identifier == id)
            return current_tag;

        current_tag = (void*)current_tag->next;
    }
}

extern uint64_t hal_cpuid(void);

int 
hal_check_features(void)
{
    if (hal_cpuid() & (1 << 9)) {
        kd_logln("Have APIC");
    } else {
        kd_errln("No APIC support detected. Returning...");
        return -1;
    }

    return 0; // success
}

void
_start(stivale2_struct_t* env)
{
    uint8_t x;
    tty_init(env);
    if ((x = kmain())) {
        kd_errln("Kernel exited with non-zero exit code, not shutting down\n");
        kd_err("Errno: %u", x);
        for (;;) {
            __asm__ volatile("hlt");
        }
    } else {
        hal_shutdown();
    }
}