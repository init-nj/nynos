
CC = gcc
NASM = nasm
LD = ld

BUILD = build
ISO_ROOT = $(BUILD)/iso_root
LIMINE_DIR = /usr/share/limine

CFLAGS = -std=gnu11 -O2 -Wall -Wextra \
         -ffreestanding -fno-stack-protector \
         -fno-pic -fno-pie -m64 \
         -mno-red-zone -mgeneral-regs-only \
         -fno-asynchronous-unwind-tables \
         -fno-unwind-tables

LDFLAGS = -m elf_x86_64 -nostdlib \
          -z max-page-size=0x1000 \
          -T linker.ld

.PHONY: all iso clean

all: $(BUILD)/nynOS.elf

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/entry.o: arch/x86_64/boot/entry.asm | $(BUILD)
	$(NASM) -f elf64 $< -o $@

$(BUILD)/kernel.o: kernel/kernel.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/nynOS.elf: $(BUILD)/entry.o $(BUILD)/kernel.o linker.ld
	$(LD) $(LDFLAGS) -o $@ $(BUILD)/entry.o $(BUILD)/kernel.o

iso: $(BUILD)/nynOS.elf
	mkdir -p $(ISO_ROOT)/EFI/BOOT
	mkdir -p $(ISO_ROOT)/boot

	cp $(LIMINE_DIR)/BOOTX64.EFI $(ISO_ROOT)/EFI/BOOT/
	cp $(LIMINE_DIR)/limine-uefi-cd.bin $(ISO_ROOT)/boot/
	cp $(LIMINE_DIR)/limine-bios-cd.bin $(ISO_ROOT)/boot/
	cp $(LIMINE_DIR)/limine-bios.sys $(ISO_ROOT)/
	cp $(BUILD)/nynOS.elf $(ISO_ROOT)/boot/
	cp boot/limine.conf $(ISO_ROOT)/limine.conf

	xorriso -as mkisofs -R -r -J \
		-b boot/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 \
		-boot-info-table -hfsplus \
		-apm-block-size 2048 \
		--efi-boot boot/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image \
		--protective-msdos-label \
		$(ISO_ROOT) -o $(BUILD)/nynOS.iso

	limine bios-install $(BUILD)/nynOS.iso

clean:
	rm -f $(BUILD)/entry.o $(BUILD)/kernel.o
	rm -f $(BUILD)/nynOS.elf $(BUILD)/nynOS.iso
	rm -rf $(ISO_ROOT)
