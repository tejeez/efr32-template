# Makefile for EFR32 programs using the Gecko SDK

#######################################
# Project configuration
#######################################

# Name of the binary
TARGET = example

BUILD_DIR = build

# Optimization flags
OPT = -O1

DEBUG = 1

# C sources
C_SOURCES = $(wildcard *.c */*.c)

# C include paths
C_INCLUDES = -I.

# C defines
C_DEFS =

# Other C flags
C_FLAGS = -std=gnu11 -Wall -Wextra -fdata-sections -ffunction-sections

# Assembly sources
ASM_SOURCES =

# Assembly include paths
AS_INCLUDES =

# Assembly defines
AS_DEFS =

# Other assembler flags
AS_FLAGS = -std=gnu11 -Wall -Wextra -fdata-sections -ffunction-sections

# Library paths
LIBDIR =

# Libraries
LIBS =

# Custom linker script
#LDSCRIPT =

# Other linker flags
LD_FLAGS =


#######################################
# CMSIS and Gecko SDK
#######################################

# Path to Gecko SDK
GECKOSDK = $(HOME)/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.7

# CMSIS
C_INCLUDES += -I$(GECKOSDK)/platform/CMSIS/Include

# EMLIB
C_SOURCES += $(wildcard $(GECKOSDK)/platform/emlib/src/*.c)
C_INCLUDES += -I$(GECKOSDK)/platform/emlib/inc

# EMDRV libraries
#C_INCLUDES += -I$(GECKOSDK)/platform/emdrv/common/inc
#C_SOURCES += $(wildcard $(GECKOSDK)/platform/emdrv/rtcdrv/src/*.c)
#C_INCLUDES += -I$(GECKOSDK)/platform/emdrv/rtcdrv/inc -I$(GECKOSDK)/platform/emdrv/rtcdrv/config


#######################################
# EFR32 chip specific parts
#######################################

# Define for part number
C_DEFS += -DEFR32FG13P231F512GM48

# Include paths
C_INCLUDES += -I$(GECKOSDK)/platform/Device/SiliconLabs/EFR32FG13P/Include

# Startup and system code
ASM_SOURCES += $(GECKOSDK)/platform/Device/SiliconLabs/EFR32FG13P/Source/GCC/startup_efr32fg13p.S
C_SOURCES += $(GECKOSDK)/platform/Device/SiliconLabs/EFR32FG13P/Source/system_efr32fg13p.c

# Linker script
LDSCRIPT ?= $(GECKOSDK)/platform/Device/SiliconLabs/EFR32FG13P/Source/GCC/efr32fg13p.ld

# RAIL library
C_INCLUDES += -I$(GECKOSDK)/platform/radio/rail_lib/common
C_INCLUDES += -I$(GECKOSDK)/platform/radio/rail_lib/chip/efr32/efr32xg1x
LIBDIR += -L$(GECKOSDK)/platform/radio/rail_lib/autogen/librail_release
LIBS += -lrail_efr32xg13_gcc_release

# Processor core
MCU = -mcpu=cortex-m4 -mthumb

# Float ABI
MCU += -mfpu=fpv4-sp-d16 -mfloat-abi=softfp


#######################################
# Compiler flags
#######################################

# Link the standard library
LIBS += -lc -lm -lnosys
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections $(LD_FLAGS)

ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) $(AS_FLAGS)
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) $(C_FLAGS)

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# ARM toolchain
#######################################

PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S


#######################################
# Build targets and commands
#######################################

# default action: build all
#all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin

# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

clean:
	-rm -fR $(BUILD_DIR)

.PHONY: all clean

# Dependencies
-include $(wildcard $(BUILD_DIR)/*.d)
