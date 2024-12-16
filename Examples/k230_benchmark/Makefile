# Toolchain definitions
CC      = $(CROSS_COMPILE)gcc
CPP     = $(CROSS_COMPILE)cpp
AR      = $(CROSS_COMPILE)ar
LD      = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

# Project configuration
TARGET  = riscv_helloworld
CFLAGS  = -fPIC -fno-stack-protector -mcmodel=medlow -g

# Directory definitions
RTOS_ROOT    = $(CURDIR)/../../RTOS
PLATFORM_DIR = $(CURDIR)/Paltform
CONFIG_DIR   = $(CURDIR)/Config
ASW_DIR      = $(CURDIR)/ASW

# Include paths
CC_INCLUDE  = -I$(PLATFORM_DIR)/Include
CC_INCLUDE += -I$(RTOS_ROOT)/Kernel
CC_INCLUDE += -I$(RTOS_ROOT)/Portable/Processor/riscv
CC_INCLUDE += -I$(CONFIG_DIR)/OS_Config
CC_INCLUDE += -I$(ASW_DIR)/include

# Source files
SRCS  = $(wildcard $(CONFIG_DIR)/OS_Config/*.c)
SRCS += $(wildcard $(ASW_DIR)/src/*.c)
SRCS += $(wildcard $(RTOS_ROOT)/Kernel/*.c)
SRCS += $(wildcard $(RTOS_ROOT)/Portable/Processor/riscv/*.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Assembly flags
ASM_FLAG = $(CC_INCLUDE) -D__ASSEMBLY__

# Build rules
all: ${TARGET}.elf

${TARGET}.elf: start.o RV_PortASM.o $(OBJS)
	$(LD) $(CROSS_LDFLAGS) -melf32lriscv -T$(CURDIR)/Startup/link.ld $^ -o $@
	$(OBJCOPY) -O binary $@ ${TARGET}.bin
	$(OBJDUMP) -D $@ > ${TARGET}.asm

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(CC_INCLUDE) -o $@

start.o: $(CURDIR)/Startup/start.S
	$(CC) $(CFLAGS) -c $< $(ASM_FLAG)

RV_PortASM.o: $(RTOS_ROOT)/Portable/Processor/riscv/RV_PortASM.S
	$(CC) $(CFLAGS) -c $< $(ASM_FLAG)

clean:
	rm -f $(OBJS) *.o *.bin *.elf *.asm

.PHONY: all clean

