/**
 * @file platform.h
 * @brief Platform abstraction layer for hardware-specific operations.
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "particles.h"


/**
 * @brief Initializes the platform (e.g., display, input, peripherals).
 * 
 * @return true if initialization succeeds, false otherwise.
 */
bool platform_init();

/**
 * @brief Polls for user input or hardware events.
 */
void platform_poll_events();

/**
 * @brief This function returns the current GLFW time, in seconds.
 * 
 * @return The current time, in seconds, or zero if an
 *  error occurred.
 */

float platform_get_time();

/**
 * @brief Draws a particle on the screen.
 * 
 * This function renders a single particle as a point.
 * Uses platform specific function to render the particle
 *
 * @param p Pointer to the Particle to be drawn.
 */
void platform_draw_particle(Particle* p);


/**
 * @brief Update the global forces acting on the particles
*/
void platform_update_global_acceleration(float *ax, float *ay);

/**
 * @brief Checks if the platform should terminate (e.g., window close or system shutdown).
 * 
 * @return true if the platform should terminate, false otherwise.
 */
bool platform_should_terminate();

/**
 * @brief Clears the display or screen buffer.
 */
void platform_clear_display();

/**
 * @brief Updates the display or renders the frame buffer.
 */
void platform_update_display();

/**
 * @brief Terminates the platform and cleans up resources.
 */
void platform_terminate();

#endif // PLATFORM_H
