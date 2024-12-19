#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "platform.h"
#include "particles.h"

int main() {

    if (!platform_init()) {
        return -1;
    }
    
    // Create an array of NUM_OF_PARTICLES particles
    Particle particles[NUM_OF_PARTICLES];
    for (int i = 0; i < NUM_OF_PARTICLES; ++i) {
        particle_init(&particles[i]);
    }

    float ax = 0.0f; // Global x-axis acceleration
    float ay = -0.1f; // Global y-axis acceleration (gravity)

    while (!platform_should_terminate()) {

        platform_update_global_acceleration(&ax, &ay);
        
        // Update particles with the global acceleration
        float time = platform_get_time();
        static float lastTime = 0.0f;
        float deltaTime = time - lastTime;
        lastTime = time;

        for (int i = 0; i < NUM_OF_PARTICLES; ++i) {
            // Apply the global acceleration to each particle
            particles[i].ax = ax;
            particles[i].ay = ay;

            // Update particle based on acceleration
            particle_update(&particles[i], deltaTime);
        }

        float restitution = 0.9f; // Set restitution to 0.8 for some energy loss

        for (int i = 0; i < NUM_OF_PARTICLES; ++i) {
            for (int j = i + 1; j < NUM_OF_PARTICLES; ++j) {
                particle_check_collision(&particles[i], &particles[j], restitution);
            }
        }

        platform_clear_display();

        for (int i = 0; i < NUM_OF_PARTICLES; ++i) {
            platform_draw_particle(&particles[i]);
        }

        platform_update_display();
        platform_poll_events();
    }

    platform_terminate();
    return 0;
}
