# Define targets
TARGET ?= HOST

# Compiler and flags
CC = gcc
CFLAGS_COMMON = -Wall -Wextra -I. -I./platform -I./particles
LDFLAGS_COMMON =

ifeq ($(TARGET), HOST)
    CFLAGS = $(CFLAGS_COMMON) -DPLATFORM_HOST
    LDFLAGS = $(LDFLAGS_COMMON) -lglfw -lGL -lm
    SRCS = main.c platform/platform.c particles/particles.c
else ifeq ($(TARGET), EMBEDDED)
    CC = arm-none-eabi-gcc
    CFLAGS = $(CFLAGS_COMMON) -DPLATFORM_EMBEDDED
    LDFLAGS = $(LDFLAGS_COMMON) -T linker_script.ld
    SRCS = main.c platform/platform_embedded.c particle_simulation/particle_simulation.c
else
    $(error Unknown target '$(TARGET)'. Supported targets: HOST, EMBEDDED)
endif

# Object files
OBJS = $(SRCS:.c=.o)

# Output binary
OUTPUT = particles_$(TARGET)

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CC) $(OBJS) -o $(OUTPUT) $(LDFLAGS)

# Run the program (for host)
run: $(OUTPUT)
	./$(OUTPUT)

clean:
	rm -f $(OBJS) $(OUTPUT)

