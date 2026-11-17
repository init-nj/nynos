
OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)

ENTRY(_start)

KERNEL_VMA = 0xFFFFFFFF80000000;

PHDRS
{
    text   PT_LOAD FLAGS(5);
    rodata PT_LOAD FLAGS(4);
    data   PT_LOAD FLAGS(6);
}

SECTIONS
{
    . = KERNEL_VMA;

    .text ALIGN(0x1000) :
    {
        KEEP(*(.text._start))
        *(.text .text.*)
    } :text

    .rodata ALIGN(0x1000) :
    {
        *(.rodata .rodata.*)
    } :rodata

    .data ALIGN(0x1000) :
    {
        . = ALIGN(8);
        KEEP(*(.limine_requests_start))

        . = ALIGN(8);
        KEEP(*(.limine_requests))

        . = ALIGN(8);
        KEEP(*(.limine_requests_end))

        . = ALIGN(8);
        *(.data .data.*)
    } :data

    .bss ALIGN(0x1000) (NOLOAD) :
    {
        *(COMMON)
        *(.bss .bss.*)
    } :data

    /DISCARD/ :
    {
        *(.comment)
        *(.eh_frame*)
        *(.note*)
    }
}
