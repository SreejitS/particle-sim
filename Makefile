# Define targets
TARGET ?= HOST
BUILD ?= DEBUG

# Compiler and flags for HOST
CC_HOST = gcc
CFLAGS_COMMON = -Wall -Wextra -I. -I./platform/host -I./platform/embedded -I./particles
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
    BUILD_DIR = platform/embedded/build
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
	$(Q)cd $(BUILD_DIR) && cmake -DPICO_SDK_PATH=$(PICO_SDK_PATH) ..
	$(Q)cd $(BUILD_DIR) && $(MAKE)
	$(Q)cp $(BUILD_DIR)/particles.elf $(OUTPUT)
endif

run: $(OUTPUT)
ifeq ($(TARGET), HOST)
	$(Q)./$(OUTPUT)
else
	$(error 'run' is only supported for HOST target.)
endif

clean:
	$(Q)rm -f $(OBJS) $(OUTPUT) $(SRCS:.c=.d)
ifeq ($(TARGET), EMBEDDED)
	$(Q)rm -rf $(BUILD_DIR)
endif

.PHONY: all clean run
