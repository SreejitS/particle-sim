# Particle-Sim

## Overview
This project demonstrates how application logic can be implemented on a host machine and then ported to an RP Pico 2040 with MPU6050 and SSD1306 OLED display with minimal changes to platform-specific details.

## Features
- Cross-platform application logic
- Easy porting to embedded systems
- Clean and modular code structure

## Getting Started

### Prerequisites
- Host machine (Windows/Linux/Mac)
- RP Pico 2040
- MPU6050 sensor
- SSD1306 OLED display
- Development tools for both platforms (e.g., GCC, ARM toolchain, etc.)

### Installation

#### Host Machine
1. Clone the repository:
    ```sh
    git clone https://github.com/SreejitS/particle-sim.git
    cd particle-sim
    ```
2. Build the project:
    ```sh
    make TARGET=HOST
    ```
3. Run the application:
    ```sh
    make run
    ```

#### RP Pico 2040
1. Clone the repository:
    ```sh
    git clone https://github.com/SreejitS/particle-sim.git
    cd particle-sim
    ```
2. Configure the build system for the RP Pico 2040:
    ```sh
    make TARGET=EMBEDDED
    ```
3. Flash the application to the RP Pico 2040:
    ```sh
    make flash TARGET=EMBEDDED
    ```
    ### Demo

    #### Host Machine
    ![Particle Sim Host Demo](particle-sim-host.gif)

    #### Embedded Target
    ![Particle Sim Host Demo](particle-sim-embedded.gif)

## Application Logic

### Host Machine
The application logic is implemented in a platform-independent manner. For example, the main application logic is contained in `main.c`:
```c
```c
#include "application.h"

int main() {
    // Initialize the application
    app_init();

    // Main loop
    while (1) {
        // Run the application logic
        app_run();
    }

    return 0;
}
```

### RP Pico 2040
The same application logic is adapted for the RP Pico 2040 with MPU6050 and SSD1306 OLED display. The platform-specific details are handled in `platform/embedded/platform.c`:
```c
```c
#include "platform.h"
#include "mpu6050.h"
#include "ssd1306.h"

void platform_init() {
    // Initialize I2C for MPU6050 and SSD1306
    i2c_init();

    // Initialize MPU6050 sensor
    mpu6050_init();

    // Initialize SSD1306 display
    ssd1306_init();
}

void platform_run() {
    // Read data from MPU6050
    mpu6050_data_t data;
    mpu6050_read(&data);

    // Display data on SSD1306
    ssd1306_display(data);
}
```