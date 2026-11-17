#include "kernel/log.h"
#include "kernel/boot.h"

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

    log_write("\n================================\n");
    log_write("               KERNEL             \n");
    log_write("==================================\n");

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}
