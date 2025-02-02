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

# Set up build directories
BUILD_DIR_HOST = build
BUILD_DIR_EMBEDDED = platform/embedded/build

# Pico SDK path
PICO_SDK_PATH = platform/embedded/pico-sdk

# Check if Pico SDK exists, clone if not
ifeq ($(TARGET), EMBEDDED)
    ifeq ($(wildcard $(PICO_SDK_PATH)/CMakeLists.txt),)
        $(info Pico SDK not found. Cloning into $(PICO_SDK_PATH)...)
        $(shell mkdir -p $(PICO_SDK_PATH))
        $(shell git clone https://github.com/raspberrypi/pico-sdk.git $(PICO_SDK_PATH))
        $(shell git -C $(PICO_SDK_PATH) submodule update --init)
    endif
endif

ifeq ($(TARGET), HOST)
    CC = $(CC_HOST)
    BUILD_DIR = $(BUILD_DIR_HOST)
    CFLAGS = $(CFLAGS_COMMON) -DPLATFORM_HOST
    LDFLAGS = $(LDFLAGS_COMMON) -lglfw -lGL -lm
    SRCS = main.c platform/host/platform.c particles/particles.c
else ifeq ($(TARGET), EMBEDDED)
    CROSS_COMPILE = arm-none-eabi-
    BUILD_DIR = $(BUILD_DIR_EMBEDDED)
    ELF_FILE = $(BUILD_DIR)/particles.elf
    BIN_FILE = $(BUILD_DIR)/particles.bin  # .bin extension for flashing
    SRCS = platform/embedded/main.c platform/embedded/platform.c particles/particles.c
else
    $(error Unknown target '$(TARGET)'. Supported targets: HOST, EMBEDDED)
endif

# Object and dependency files in build directory
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

# Output binary
OUTPUT = $(BUILD_DIR)/particles_$(TARGET)

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
	@mkdir -p $(BUILD_DIR)
	$(Q)$(CC) $(OBJS) -o $(OUTPUT) $(LDFLAGS)

-include $(DEPS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(Q)$(CC) $(CFLAGS) -MMD -c $< -o $@

# EMBEDDED target build
else ifeq ($(TARGET), EMBEDDED)
$(OUTPUT):
	$(Q)mkdir -p $(BUILD_DIR)
	$(Q)cd $(BUILD_DIR) && cmake -DPICO_SDK_PATH=$(abspath $(PICO_SDK_PATH)) -DPICO_BOARD=pico_w ..
	$(Q)cd $(BUILD_DIR) && $(MAKE)
	$(Q)$(CROSS_COMPILE)objcopy -O binary $(ELF_FILE) $(BIN_FILE)
	$(Q)cp $(BIN_FILE) $(OUTPUT)
endif

# Flash the RP2040 using pyOCD
flash: $(BIN_FILE)
	$(Q)pyocd flash -t rp2040 $(BIN_FILE)

run: $(OUTPUT)
ifeq ($(TARGET), HOST)
	$(Q)./$(OUTPUT)
else
	$(Q)pyocd reset -t rp2040
endif

clean:
	$(Q)rm -rf $(BUILD_DIR_HOST) $(BUILD_DIR_EMBEDDED)

.PHONY: all clean run flash