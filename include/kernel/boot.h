#ifndef NYNOS_KERNEL_BOOT_H
#define NYNOS_KERNEL_BOOT_H

#include <limine.h>

void boot_info_init(void);

struct limine_framebuffer *boot_get_framebuffer(void);

#endif
