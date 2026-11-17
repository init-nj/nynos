#ifndef NYNOS_KERNEL_LOG_H
#define NYNOS_KERNEL_LOG_H

#include <stdint.h>

void log_init(void);
void log_write(const char *message);
void log_write_char(char c);
void log_write_u64(uint64_t value);
void log_write_hex(uint64_t value);

#endif
