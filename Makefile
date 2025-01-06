# Define targets
TARGET ?= HOST
BUILD ?= DEBUG

# Compiler and flags for HOST
CC_HOST = gcc
CFLAGS_COMMON = -Wall -Wextra -I. -I./platform/host -I./platform/embedded -I./particles -I/platform/embedded/display
LDFLAGS_COMMON =

ifeq ($(BUILD), DEBUG)
    CFLAGS_COMMON += -g
else ifeq ($(BUILD), RELEASE)
    CFLAGS_COMMON += -O2
else
    $(error Unknown build configuration '$(BUILD)'. Supported: DEBUG, RELEASE)
endif

ifeq ($(TARGET), HOST)
    CC = $(CC_HOST)
    CFLAGS = $(CFLAGS_COMMON) -DPLATFORM_HOST
    LDFLAGS = $(LDFLAGS_COMMON) -lglfw -lGL -lm
    SRCS = main.c platform/host/platform.c particles/particles.c
else ifeq ($(TARGET), EMBEDDED)
    # RP2040-specific build
    ifndef PICO_SDK_PATH
        $(error PICO_SDK_PATH is not set. Please export PICO_SDK_PATH to the Pico SDK path.)
    endif
    CROSS_COMPILE = arm-none-eabi-
    BUILD_DIR = platform/embedded/build
    ELF_FILE = $(BUILD_DIR)/particles.elf
    BIN_FILE = $(BUILD_DIR)/particles.bin  # .bin extension for flashing
else
    $(error Unknown target '$(TARGET)'. Supported targets: HOST, EMBEDDED)
endif

# Object files
OBJS = $(SRCS:.c=.o)

# Output binary
OUTPUT = particles_$(TARGET)

# Quiet mode
VERBOSE ?= 1
ifeq ($(VERBOSE), 0)
    Q = @
else
    Q =
endif

all: $(OUTPUT)

# HOST target build
ifeq ($(TARGET), HOST)
$(OUTPUT): $(OBJS)
	$(Q)$(CC) $(OBJS) -o $(OUTPUT) $(LDFLAGS)

-include $(SRCS:.c=.d)

%.o: %.c
	$(Q)$(CC) $(CFLAGS) -MMD -c $< -o $@

# EMBEDDED target build
else ifeq ($(TARGET), EMBEDDED)
$(OUTPUT):
	$(Q)mkdir -p $(BUILD_DIR)
	$(Q)cd $(BUILD_DIR) && cmake -DPICO_SDK_PATH=$(PICO_SDK_PATH) -DPICO_BOARD=pico_w ..
	$(Q)cd $(BUILD_DIR) && $(MAKE)
	$(Q)$(CROSS_COMPILE)objcopy -O binary $(ELF_FILE) $(BIN_FILE)  # Convert ELF to BIN
	$(Q)cp $(BIN_FILE) $(OUTPUT)
endif

# Flash the RP2040 using pyOCD
flash: $(BIN_FILE)
	$(Q)pyocd flash -t rp2040 $(BIN_FILE)

run: $(OUTPUT)
ifeq ($(TARGET), HOST)
	$(Q)./$(OUTPUT)
else
	$(error 'run' is only supported for HOST target.)
endif

clean:
	$(Q)rm -rf $(BUILD_DIR)
	$(Q)rm -f $(OUTPUT) $(OBJS) $(SRCS:.c=.d)

.PHONY: all clean run flash
