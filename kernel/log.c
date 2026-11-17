#include "kernel/log.h"
#include "serial/serial.h"

void log_init(void)
{
    serial_init();
}

void log_write(const char *message)
{
    serial_write(message);
}

void log_write_char(char c)
{
    serial_write_char(c);
}

void log_write_u64(uint64_t value)
{
    char buffer[21];
    unsigned int index = 0;

    if (value == 0)
    {
        log_write_char('0');
        return;
    }

    while (value > 0)
    {
        buffer[index++] = '0' + (value % 10);
        value /= 10;
    }

    while (index > 0)
    {
        log_write_char(buffer[--index]);
    }
}

void log_write_hex(uint64_t value)
{
    static const char digits[] = "0123456789ABCDEF";

    log_write("0x");

    for (int shift = 60; shift >= 0; shift -= 4)
    {
        log_write_char(digits[(value >> shift) & 0xF]);
    }
}
