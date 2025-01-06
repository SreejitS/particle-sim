/**
 * @file display.h
 * @brief Abstraction layer for embedded target for handling display
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

/**
 * @brief Initializes the display
 * 
 * @return true if initialization succeeds, false otherwise
 */
bool display_init();

/**
 * @brief Displays a single point in the display
 * 
 * @param x X co-ordinate of the point
 * @param y Y co-ordinate of the point
 */
void display_point(float x, float y);

/**
 * @brief Clears the display
 */
void display_clear();


#endif // DISPLAY_H