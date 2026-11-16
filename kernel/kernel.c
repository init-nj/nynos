#include <stdint.h>

#define COM1 0x3F8

static inline void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile (
        "outb %0, %1"
        :
        : "a"(value), "Nd"(port)
    );
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t value;

    __asm__ volatile (
        "inb %1, %0"
        : "=a"(value)
        : "Nd"(port)
    );

    return value;
}

static void serial_init(void)
{
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x80);
    outb(COM1 + 0, 0x03);
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);
    outb(COM1 + 2, 0xC7);
    outb(COM1 + 4, 0x0B);
}

static void serial_write_char(char c)
{
    while ((inb(COM1 + 5) & 0x20) == 0)
    {
        __asm__ volatile ("pause");
    }

    outb(COM1, (uint8_t)c);
}

static void serial_write(const char *message)
{
    while (*message)
    {
        serial_write_char(*message++);
    }
}

__attribute__((noreturn))
void kernel_main(void)
{
    serial_init();

    serial_write("\r\n");
    serial_write("================================\r\n");
    serial_write("           x-KERNEL-x           \r\n");
    serial_write("================================\r\n");
    serial_write("Architecture: x86-64\r\n");
    serial_write("Boot:        SUCCESS\r\n");
    serial_write("  Welcome to nynOS! \r\n");

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}
