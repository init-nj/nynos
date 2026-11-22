	
#include "kernel/log.h"
#include "kernel/boot.h"

#include "framebuffer/framebuffer.h"
#include "graphics/text.h"

__attribute__((noreturn))
void kernel_main(void)
{
    log_init();

    log_write("\n");
    log_write("================================\n");
    log_write("          KERNEL                \n");
    log_write("================================\n");
    log_write("Architecture: x86-64\n");
    log_write("Boot: SUCCESS\n");

    boot_info_init();

    struct limine_framebuffer *fb = boot_get_framebuffer();

    if (framebuffer_init(fb))
    {
        log_write("[GFX] Framebuffer driver initialized.\n");

        framebuffer_clear(12, 16, 28);

        /* Header */
        text_draw_string(
            40, 40,
            "!! WELCOME !!",
            255, 255, 255,
            12, 16, 28,
            3
        );

        /* System information */
        text_draw_string(
            40, 100,
            "KERNEL INITIALIZED",
            40, 220, 120,
            12, 16, 28,
            2
        );

        text_draw_string(
            40, 135,
            "X86-64 System",
            180, 190, 220,
            12, 16, 28,
            2
        );

        text_draw_string(
            40, 170,
            "FRAMEBUFFER: ACTIVE",
            180, 190, 220,
            12, 16, 28,
            2
        );

        text_draw_string(
            40, 220,
            "GRAPHICS TEST V0.0.4",
            255, 170, 40,
            12, 16, 28,
            2
        );

        log_write("[FONT] Bitmap font renderer initialized.\n");
        log_write("[GFX] Text rendering test completed.\n");
    }
    else
    {
        log_write("[GFX] Framebuffer initialization failed.\n");
    }

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}
