# RISC-V toolchain
CROSS_COMPILE := riscv64-linux-gnu-

AS      := $(CROSS_COMPILE)as
LD      := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

# RV32E
ASFLAGS := -march=rv32e_zicsr -mabi=ilp32e

# NPC reset PC = 0x80000000
LDFLAGS := -m elf32lriscv -Ttext=0x80000000

# 找到当前目录所有 .S
SRCS := $(wildcard *.S)

# lw.S -> lw.o / lw.elf / lw.bin
OBJS := $(SRCS:.S=.o)
ELFS := $(SRCS:.S=.elf)
BINS := $(SRCS:.S=.bin)

all: $(BINS)

# .S -> .o
%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@

# .o -> .elf
%.elf: %.o
	$(LD) $(LDFLAGS) $< -o $@

# .elf -> .bin
%.bin: %.elf
	$(OBJCOPY) -O binary $< $@
	@echo "Generated $@"

# 查看反汇编
%.txt: %.elf
	$(OBJDUMP) -d $< > $@
	@echo "Generated $@"

disasm: $(ELFS:.elf=.txt)

# Build separately from the interactive simulator and use the real RAM backend.
NPC_ROOT := $(abspath ..)
STORE_BUILD := $(NPC_ROOT)/build/store-check
STORE_RTL := $(wildcard $(NPC_ROOT)/vsrc/*.v)
STORE_CHECK := $(STORE_BUILD)/store-check

$(STORE_CHECK): store-check.cpp $(STORE_RTL) $(NPC_ROOT)/csrc/mem.cpp $(NPC_ROOT)/csrc/define.h $(NPC_ROOT)/include/generated/autoconf.h Makefile
	verilator --cc --exe --build -j 2 --top-module top \
		--Mdir $(STORE_BUILD) -o $(STORE_CHECK) \
		-LDFLAGS "-Wl,--wrap=pmem_write" \
		$(STORE_RTL) $(abspath store-check.cpp) $(NPC_ROOT)/csrc/mem.cpp

store-test: store.bin $(STORE_CHECK)
	$(STORE_CHECK) $(abspath store.bin)

clean:
	rm -f *.o *.elf *.bin *.txt

.PHONY: all clean disasm store-test
