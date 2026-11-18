#include "kernel/log.h"
#include "kernel/boot.h"
#include "kernel/log.h"
#include "kernel/boot.h"
#include "framebuffer/framebuffer.h"

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

        framebuffer_draw_rect(
            40, 40, 220, 100,
            40, 140, 255
        );

        framebuffer_draw_rect(
            280, 40, 220, 100,
            40, 220, 120
        );

        framebuffer_draw_rect(
            520, 40, 220, 100,
            255, 170, 40
        );

        log_write("[GFX] Graphics test completed.\n");
    }
    else
    {
        log_write("[GFX] Framebuffer initialization failed.\n");
    }

    log_write("\n================================\n");
    log_write("               KERNEL             \n");
    log_write("==================================\n");

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}
