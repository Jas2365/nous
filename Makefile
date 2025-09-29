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
vga = $(src)/vga
idt = $(src)/idt
isr = $(src)/isr

# files
kernel_src = $(kernel)/kernel.c
boot_src = $(bootloader)/boot.asm
objs = $(wildcard build/**/**/*.o)
linker = linker.ld
kernel_bin = $(build)/kernel_bin/kernel.bin
kernel_elf = $(iso)/boot/kernel.elf
nous = release/nous.iso

.PHONY: all build clean boot kernel link $(boot_src) $(kernel_src) $(kernel_bin) $(nous) qemu_iso qemu_kernel

all: build qemu_iso
build: iso
boot:	
	@echo "===== Assembling ASM files ====="
	@for f in $(shell find $(src) -type f -name "*.asm" ); do \
	 out="$(build)/$${f#$(src)/}"; \
	 out="$${out%.asm}.o"; \
 	 mkdir -p "$$(dirname "$$out")"; \
	 $(asm) $(asm_flags) "$$f" -o "$$out"; \
	 echo "$$out"; \
	done
	@echo ""

kernel:
	@mkdir -p $(build)
	@echo "===== Compiling C files ====="
	@for f in $(shell find $(src) -type f -name "*.c" ); do \
	 out="$(build)/$${f#$(src)/}"; \
	 out="$${out%.c}.o"; \
 	 mkdir -p "$$(dirname "$$out")"; \
	 $(cxx) $(cflags) -c "$$f" -o "$$out"; \
	 echo "$$out"; \
	done
	@echo ""

link: boot kernel
	@echo "===== Linking all .o files ====="
	mkdir -p $(build)/kernel_bin
	$(ld) $(ldflags) -T $(linker) $(shell find $(build) -type f -name "*.o") -o $(kernel_bin)
	@echo ""

iso: link
	@echo "======= building iso ========="
	cp $(kernel_bin) $(kernel_elf)
	$(grub) -o $(nous) $(iso)
	@echo ""

# build: $(boot_src) $(kernel_src) $(kernel_bin) $(nous)

# $(boot_src):
# 	$(asm) $(asm_flags) $(boot_src) -o $(build)/boot.o
# 	$(asm) $(asm_flags) $(isr)/isr.asm -o $(build)/isr_asm.o

# $(kernel_src):
# 	$(cxx) $(cflags) -c $(vga)/vga.c -o $(build)/vga.o
# 	$(cxx) $(cflags) -c $(idt)/idt.c -o $(build)/idt.o
# 	$(cxx) $(cflags) -c $(isr)/isr.c -o $(build)/isr_c.o
# 	$(cxx) $(cflags) -c $(kernel_src) -o $(build)/kernel.o

# $(kernel_bin): $(boot_src) $(kernel_src)
# 	$(ld) $(ldflags) -T $(linker) -o $(kernel_bin) $(objs)

# $(nous):
# 	cp $(kernel_bin) $(kernel_elf)
# 	$(grub) -o $(nous) $(iso)

qemu_iso: 
	$(qemu) -cdrom $(nous) -m 512M

qemu_kernel:
	$(qemu) -kernel $(kernel_bin)

clean:
	rm $(build)/**/*.o 
	rm $(build)/**/*.bin 
	rm $(release)/*.iso
	rm $(iso)/boot/*.elf
