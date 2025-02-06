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
The particle simulation logic is implemented in a platform-independent manner. For example, the main simulation logic is contained in `particles.c`, `particles.h`, and `main.c`. The platform-specific details are handled in `platform/host/platform.c`.

### RP Pico 2040
The same particle simulation logic is adapted for the RP Pico 2040 with MPU6050 and SSD1306 OLED display. The platform-specific details are handled in `platform/embedded/platform.c`.