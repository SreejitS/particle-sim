cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(particles
  ../../main.c
  ../../particles/particles.c
  ../../platform/embedded/platform.c
  display/display.c
  display/ssd1306_driver.c
  imu/mpu6050.c
  imu/imu.c
)

# Include directories
target_include_directories(particles PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../particles
    ${CMAKE_CURRENT_LIST_DIR}/../../platform/embedded
    ${CMAKE_CURRENT_LIST_DIR}/display
    ${CMAKE_CURRENT_LIST_DIR}/imu
    
)

pico_enable_stdio_usb(particles 1)
pico_enable_stdio_uart(particles 1)
pico_add_extra_outputs(particles)
target_link_libraries(particles pico_stdlib hardware_i2c pico_rand)
