TOP_NAME = top
NPC_HOME = $(abspath .)
NEMU_HOME = $(abspath ../nemu)
AM_HOME = $(abspath ../abstract-machine)




#TEST_NAME ?= dummy


IMG ?= $(AM_HOME)/tests/cpu-tests/build/$(NAME)-riscv32e-npc.bin
ELF ?= $(NAME).elf
DIFF_REF_SO = $(NEMU_HOME)/build/riscv32-nemu-interpreter-so


VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc\
				-O3 --x-assign fast --x-initial fast --noassert \
				-I$(NPC_HOME)/build/config

# Match the configuration header used by the C++ simulator, including when
# this checkout has no Kconfig-generated auto.conf.
CONFIG_HEADER = $(NPC_HOME)/include/generated/autoconf.h
WAVE_ENABLED := $(shell $(CXX) -dM -E $(CONFIG_HEADER) | awk '$$2 == "CONFIG_WAVE" { print "y"; exit }')
ifeq ($(WAVE_ENABLED),y)
VERILATOR_CFLAGS +=   --trace
endif
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOP_NAME)


VSRCS = $(shell find ./vsrc -name "*.v")
CSRCS = $(shell find $(NPC_HOME)/csrc -name "*.cpp")
LDFLAGS += -lreadline -ldl -lSDL2

default: $(BIN)

$(BIN): $(VSRCS) $(CSRCS) $(shell find ./csrc ./include -name "*.h") Makefile
	@mkdir -p $(BUILD_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOP_NAME) \
		--Mdir $(OBJ_DIR) \
		--exe \
		-o $(abspath $@) \
		-LDFLAGS "$(LDFLAGS)" \
		$(VSRCS) $(CSRCS)


run: $(BIN)
	$(BIN) $(IMG) $(DIFF_REF_SO) $(ELF) $(ARGS)
clean:
	rm -rf $(BUILD_DIR)
.PHONY: lint

lint:
	verilator --lint-only \
		--top-module $(TOP_NAME) \
		$(VSRCS)

include script/config.mk
-include $(NPC_HOME)/include/config/auto.conf
-include $(NPC_HOME)/include/config/auto.conf.cmd
ifeq ($(CONFIG_BATCH), y)
ARGS += -b
endif
