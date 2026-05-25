# Makefile for STM32H743 GUI Dashboard

ARM_TOOLCHAIN_PATH ?= /opt/gcc-arm-none-eabi-9-2020-q2-update/bin
CC = $(ARM_TOOLCHAIN_PATH)/arm-none-eabi-gcc
OBJCOPY = $(ARM_TOOLCHAIN_PATH)/arm-none-eabi-objcopy
SIZE = $(ARM_TOOLCHAIN_PATH)/arm-none-eabi-size

# Project name
PROJECT_NAME = STM32H743_GUI

# Directories
SRC_DIR = src
DRIVER_DIR = $(SRC_DIR)/drivers
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Output files
ELF_FILE = $(BUILD_DIR)/$(PROJECT_NAME).elf
BIN_FILE = $(BUILD_DIR)/$(PROJECT_NAME).bin
HEX_FILE = $(BUILD_DIR)/$(PROJECT_NAME).hex
MAP_FILE = $(BUILD_DIR)/$(PROJECT_NAME).map

# Source files
SOURCES = $(SRC_DIR)/main.c \
          $(DRIVER_DIR)/clock.c \
          $(DRIVER_DIR)/gpio_init.c \
          $(DRIVER_DIR)/sdram_init.c \
          $(DRIVER_DIR)/lcd_driver.c \
          $(DRIVER_DIR)/backlight.c \
          $(DRIVER_DIR)/keypad.c \
          $(DRIVER_DIR)/uart_debug.c

# STM32 HAL source files
SOURCES += stm32h7xx_hal.c \
           stm32h7xx_hal_rcc.c \
           stm32h7xx_hal_cortex.c \
           stm32h7xx_hal_gpio.c \
           stm32h7xx_hal_uart.c \
           stm32h7xx_hal_tim.c \
           stm32h7xx_hal_ltdc.c \
           stm32h7xx_hal_fmc.c \
           stm32h7xx_it.c \
           stm32h7xx_hal_msp.c

# Object files
OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCES:.c=.o)))

# Include directories
INCLUDES = -I. \
           -I$(SRC_DIR) \
           -I$(DRIVER_DIR) \
           -ISTM32H7xx_HAL_Driver/Inc \
           -ICMSIS/Device/ST/STM32H7xx/Include \
           -ICMSIS/Include

# Compiler flags
CFLAGS = -mcpu=cortex-m7 \
         -mthumb \
         -mfpu=fpv5-d16 \
         -mfloat-abi=hard \
         -Wall \
         -Wextra \
         -O2 \
         -g3 \
         -DSTM32H743xx \
         -DUSE_HAL_DRIVER \
         $(INCLUDES)

# Linker script
LDSCRIPT = stm32h743xih6_flash.ld

# Linker flags
LDFLAGS = -Wl,--gc-sections \
          -Wl,-Map=$(MAP_FILE) \
          -mcpu=cortex-m7 \
          -mthumb \
          -mfpu=fpv5-d16 \
          -mfloat-abi=hard \
          -T$(LDSCRIPT) \
          -lc -lm -lnosys

# Default target
all: $(BIN_FILE) $(HEX_FILE) size

# Create output directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR) $(OBJ_DIR)

# Object file compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(DRIVER_DIR)/%.c | $(BUILD_DIR)
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Link ELF file
$(ELF_FILE): $(OBJECTS)
	@echo "[LD] $@"
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@

# Generate BIN file
$(BIN_FILE): $(ELF_FILE)
	@echo "[OBJCOPY] $@"
	@$(OBJCOPY) -O binary $< $@

# Generate HEX file
$(HEX_FILE): $(ELF_FILE)
	@echo "[OBJCOPY] $@"
	@$(OBJCOPY) -O ihex $< $@

# Display size information
size: $(ELF_FILE)
	@echo "=== Binary Size ==="
	@$(SIZE) $(ELF_FILE)

# Flash to device
flash: $(BIN_FILE)
	@echo "[FLASH] Writing to STM32H743..."
	@st-flash write $(BIN_FILE) 0x08000000

# Clean build
clean:
	@echo "[CLEAN] Removing build directory..."
	@rm -rf $(BUILD_DIR)

.PHONY: all clean flash size
