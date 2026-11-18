#include <stdint.h>
#include <limine.h>

#include "kernel/boot.h"
#include "kernel/log.h"

/*
 * Limine protocol request markers.
 */

__attribute__((used, section(".limine_requests_start")))
static volatile uint64_t limine_requests_start_marker[4] =
    LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests")))
static volatile uint64_t limine_base_revision[3] =
    LIMINE_BASE_REVISION(3);

__attribute__((used, section(".limine_requests")))
static volatile struct limine_bootloader_info_request bootloader_info_request = {
    .id = LIMINE_BOOTLOADER_INFO_REQUEST_ID,
    .revision = 0,
    .response = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0,
    .response = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST_ID,
    .revision = 0,
    .response = 0
};

__attribute__((used, section(".limine_requests_end")))
static volatile uint64_t limine_requests_end_marker[2] =
    LIMINE_REQUESTS_END_MARKER;


/*
 * Bootloader information.
 */

static void report_bootloader(void)
{
    log_write("\n[KINIT] Bootloader information\n");

    struct limine_bootloader_info_response *response =
        bootloader_info_request.response;

    if (response == 0)
    {
        log_write("[ERROR] Bootloader information unavailable.\n");
        return;
    }

    log_write("  Name: ");
    log_write(response->name ? response->name : "Unknown");
    log_write("\n");

    log_write("  Version: ");
    log_write(response->version ? response->version : "Unknown");
    log_write("\n");
}


/*
 * Framebuffer information.
 */

static void report_framebuffer(void)
{
    log_write("\n[KINIT] Framebuffer information\n");

    struct limine_framebuffer_response *response =
        framebuffer_request.response;

    if (response == 0)
    {
        log_write("[ERROR] Framebuffer response unavailable.\n");
        return;
    }

    if (response->framebuffer_count == 0 ||
        response->framebuffers == 0 ||
        response->framebuffers[0] == 0)
    {
        log_write("[ERROR] No usable framebuffer returned.\n");
        return;
    }

    struct limine_framebuffer *fb = response->framebuffers[0];

    log_write("  Address: ");
    log_write_hex((uint64_t)(uintptr_t)fb->address);
    log_write("\n");

    log_write("  Width: ");
    log_write_u64(fb->width);
    log_write("\n");

    log_write("  Height: ");
    log_write_u64(fb->height);
    log_write("\n");

    log_write("  Pitch: ");
    log_write_u64(fb->pitch);
    log_write(" bytes\n");

    log_write("  Bits per pixel: ");
    log_write_u64(fb->bpp);
    log_write("\n");

    log_write("  Memory model: ");
    log_write_u64(fb->memory_model);
    log_write("\n");

    log_write("  Red mask: ");
    log_write_u64(fb->red_mask_size);
    log_write(" bits, shift ");
    log_write_u64(fb->red_mask_shift);
    log_write("\n");

    log_write("  Green mask: ");
    log_write_u64(fb->green_mask_size);
    log_write(" bits, shift ");
    log_write_u64(fb->green_mask_shift);
    log_write("\n");

    log_write("  Blue mask: ");
    log_write_u64(fb->blue_mask_size);
    log_write(" bits, shift ");
    log_write_u64(fb->blue_mask_shift);
    log_write("\n");

    if (fb->address == 0 || fb->width == 0 ||
        fb->height == 0 || fb->pitch == 0)
    {
        log_write("[WARNING] Framebuffer parameters are incomplete.\n");
    }
    else if (fb->memory_model != LIMINE_FRAMEBUFFER_RGB)
    {
        log_write("[WARNING] Framebuffer is not RGB format.\n");
    }
    else
    {
        log_write("[KINIT] Framebuffer metadata validated.\n");
    }
}


/*
 * Physical memory map.
 */

static const char *memory_type_name(uint64_t type)
{
    switch (type)
    {
        case LIMINE_MEMMAP_USABLE:
            return "Usable";

        case LIMINE_MEMMAP_RESERVED:
            return "Reserved";

        case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
            return "ACPI reclaimable";

        case LIMINE_MEMMAP_ACPI_NVS:
            return "ACPI NVS";

        case LIMINE_MEMMAP_BAD_MEMORY:
            return "Bad memory";

        case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
            return "Bootloader reclaimable";

        case LIMINE_MEMMAP_EXECUTABLE_AND_MODULES:
            return "Kernel/modules";

        case LIMINE_MEMMAP_FRAMEBUFFER:
            return "Framebuffer";

        case LIMINE_MEMMAP_RESERVED_MAPPED:
            return "Reserved mapped";

        default:
            return "Unknown";
    }
}

static void report_memory_map(void)
{
    log_write("\n[KINIT] Physical memory map\n");

    struct limine_memmap_response *response =
        memmap_request.response;

    if (response == 0)
    {
        log_write("[ERROR] Memory map response unavailable.\n");
        return;
    }

    if (response->entries == 0)
    {
        log_write("[ERROR] Memory map entries unavailable.\n");
        return;
    }

    log_write("  Region count: ");
    log_write_u64(response->entry_count);
    log_write("\n");

    uint64_t usable_memory = 0;

    for (uint64_t i = 0; i < response->entry_count; i++)
    {
        struct limine_memmap_entry *entry = response->entries[i];

        if (entry == 0)
            continue;

        if (entry->type == LIMINE_MEMMAP_USABLE)
        {
            usable_memory += entry->length;
        }

        /*
         * Limit detailed output to the first 32 regions.
         */
        if (i < 32)
        {
            log_write("  Region ");
            log_write_u64(i);
            log_write(": ");

            log_write(memory_type_name(entry->type));

            log_write(" | Base: ");
            log_write_hex(entry->base);

            log_write(" | Length: ");
            log_write_hex(entry->length);

            log_write("\n");
        }
    }

    if (response->entry_count > 32)
    {
        log_write("  Additional regions omitted from log: ");
        log_write_u64(response->entry_count - 32);
        log_write("\n");
    }

    log_write("  Total usable memory: ");
    log_write_u64(usable_memory / (1024 * 1024));
    log_write(" MiB\n");

    log_write("[KINIT] Memory map processed.\n");
}


/*
 * Kernel initialization entry point.
 */

void boot_info_init(void)
{
    log_write("\n================================\n");
    log_write("       nynOS KINIT v0.0.2       \n");
    log_write("================================\n");

    if (!LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision))
    {
        log_write("[FATAL] Required Limine base revision unsupported.\n");
        log_write("[FATAL] Kernel initialization cannot continue.\n");

        for (;;)
        {
            __asm__ volatile ("cli; hlt");
        }
    }

    log_write("[KINIT] Limine base revision supported.\n");

    report_bootloader();
    report_framebuffer();
    report_memory_map();

    log_write("\n[KINIT] Initialization sequence completed.\n");
}

struct limine_framebuffer *boot_get_framebuffer(void)
{
    struct limine_framebuffer_response *response =
        framebuffer_request.response;

    if (response == 0 ||
        response->framebuffers == 0 ||
        response->framebuffer_count == 0)
    {
        return 0;
    }

    return response->framebuffers[0];
}
