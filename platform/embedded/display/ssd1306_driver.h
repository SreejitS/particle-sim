/**
 * @file ssd1306_driver.h
 * @brief Header file for the SSD1306 OLED display driver.
 */

#ifndef SSD1306_DRIVER_H
#define SSD1306_DRIVER_H

#include <stdbool.h>

// Define the size of the display we have attached. This can vary, make sure you
// have the right size defined or the output will look rather odd!
// Code has been tested on 128x32 and 128x64 OLED displays
#define SSD1306_HEIGHT              32
#define SSD1306_WIDTH               128

/**
 * @brief Initializes the SSD1306 OLED display.
 * 
 * This function sets up the I2C interface and configures the SSD1306 display for use.
 * It must be called before any other functions in this driver.
 * 
 * @return true if initialization was successful, false otherwise.
 */
bool ssd1306_driver_init();

/**
 * @brief Draws a pixel on the SSD1306 display.
 * 
 * This function plots a single pixel at the specified (x, y) coordinates.
 * The coordinates are in floating-point format and may be internally rounded
 * to the nearest valid integer values for the display resolution.
 * 
 * @param x The x-coordinate of the pixel (horizontal position).
 * @param y The y-coordinate of the pixel (vertical position).
 */
void ssd1306_draw_pixel(float x, float y);

/**
 * @brief Clears the entire SSD1306 display.
 * 
 * This function turns off all pixels on the display, effectively clearing it.
 */
void ssd1306_clear();

/**
 * @brief Renders the current frame buffer to the SSD1306 display.
 * 
 * This function updates the display with the contents of the frame buffer.
 * It should be called after drawing any graphics to the display.
 */
void ssd1306_render();

#endif // SSD1306_DRIVER_H
