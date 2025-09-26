# compilers, linkers and emulators
asm = nasm
ld = ld
cxx = gcc
qemu = qemu-system-i386
grub = grub-mkrescue

# flags
asm_flags = -f elf32
cflags = -m32 -ffreestanding -fno-builtin -nostdlib
ldflags = -m elf_i386 -z noexecstack

# folders
build = build
src = src
iso = iso
release = release
 
# subfolders
bootloader = $(src)/bootloader
kernel = $(src)/kernel
vga = $(kernel)/vga
idt = $(kernel)/idt
isr = $(kernel)/isr

# files
kernel_src = $(kernel)/kernel.c
boot_src = $(bootloader)/boot.asm
objs = $(wildcard build/*.o)
linker = linker.ld
binary = $(build)/kernel.bin
cp_bin_to_elf = $(iso)/boot/kernel.elf
nous = release/nous.iso

.PHONY: all build clean $(boot_src) $(kernel_src) $(binary) $(nous) qemu_iso qemu_kernel

all: build

build: $(boot_src) $(kernel_src) $(binary) $(nous)

$(boot_src):
	$(asm) $(asm_flags) $(boot_src) -o $(build)/boot.o
	$(asm) $(asm_flags) $(isr)/isr.asm -o $(build)/isr_asm.o

$(kernel_src):
	$(cxx) $(cflags) -c $(vga)/vga.c -o $(build)/vga.o
	$(cxx) $(cflags) -c $(idt)/idt.c -o $(build)/idt.o
	$(cxx) $(cflags) -c $(isr)/isr.c -o $(build)/isr_c.o
	$(cxx) $(cflags) -c $(kernel_src) -o $(build)/kernel.o

$(binary): $(boot_src) $(kernel_src)
	$(ld) $(ldflags) -T $(linker) -o $(binary) $(objs)

$(nous): $(binary)
	cp $(binary) $(cp_bin_to_elf)
	$(grub) -o $(nous) $(iso)

qemu_iso: $(nous)
	$(qemu) -cdrom $(nous) -m 512M

qemu_kernel: $(binary)
	$(qemu) -kernel $(binary)

clean:
	rm $(build)/*.o 
	rm $(build)/*.bin 
	rm $(iso)/boot/*.elf
	rm $(release)/*.iso
