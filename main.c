#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "particles.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_RIGHT:
                printf("Right Arrow Key Pressed - Positive X Acceleration\n");
                break;
            case GLFW_KEY_LEFT:
                printf("Left Arrow Key Pressed - Negative X Acceleration\n");
                break;
            case GLFW_KEY_UP:
                printf("Up Arrow Key Pressed - Positive Y Acceleration\n");
                break;
            case GLFW_KEY_DOWN:
                printf("Down Arrow Key Pressed - Negative Y Acceleration\n");
                break;
            default:
                break;
        }
    }
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Particle Simulation with Collisions", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback); // Set the key callback for detecting key presses
    glPointSize(10.0f); // Set particle size

    // Initialize random seed
    srand(time(NULL));

    // Create an array of NUM_OF_PARTICLES particles
    Particle particles[NUM_OF_PARTICLES];
    for (int i = 0; i < NUM_OF_PARTICLES; ++i) {
        initialize_particle(&particles[i]);
    }

    float ax = 0.0f; // Global x-axis acceleration
    float ay = -0.1f; // Global y-axis acceleration (gravity)

    while (!glfwWindowShouldClose(window)) {
        // Handle input for acceleration
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) ax = 0.8f;
        else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) ax = -0.8f;
        else ax = 0.0f;

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) ay = 0.8f;
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) ay = -0.8f;

        // Update particles with the global acceleration
        float time = glfwGetTime();
        static float lastTime = 0.0f;
        float deltaTime = time - lastTime;
        lastTime = time;

        for (int i = 0; i < NUM_OF_PARTICLES; ++i) {
            // Apply the global acceleration to each particle
            particles[i].ax = ax;
            particles[i].ay = ay;

            // Update particle based on acceleration
            update_particle(&particles[i], deltaTime);
        }

        float restitution = 0.9f; // Set restitution to 0.8 for some energy loss

        for (int i = 0; i < NUM_OF_PARTICLES; ++i) {
            for (int j = i + 1; j < NUM_OF_PARTICLES; ++j) {
                check_collision(&particles[i], &particles[j], restitution);
            }
        }


        // Render
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        for (int i = 0; i < NUM_OF_PARTICLES; ++i) {
            draw_particle(&particles[i]);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
