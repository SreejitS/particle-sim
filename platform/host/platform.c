#include <GLFW/glfw3.h>
#include "platform.h"

static GLFWwindow* window = NULL;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void) window;
    (void) scancode;
    (void) mods;
    
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_RIGHT:
                break;
            case GLFW_KEY_LEFT:
                break;
            case GLFW_KEY_UP:
                break;
            case GLFW_KEY_DOWN:
                break;
            default:
                break;
        }
    }
}

bool platform_init() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return false;
    }

    window = glfwCreateWindow(800, 600, "Particle Simulation with Collisions [*Press Arrow Keys*]", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback); // Set the key callback for detecting key presses
    glPointSize(10.0f); // Set particle size

    // Initialize random seed
    srand(time(NULL));

    return true;
}

void platform_poll_events() {
    glfwPollEvents();
}

float platform_get_time() {
    return glfwGetTime();
}

void platform_draw_particle(Particle* p) {
    glBegin(GL_POINTS);
    glVertex2f(p->x, p->y);
    glEnd();
}

void platform_update_global_acceleration(float *ax, float *ay) {
    // Handle input for acceleration
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) *ax = 0.8f;
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) *ax = -0.8f;
    else *ax = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) *ay = 0.8f;
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) *ay = -0.8f;
    else *ay = 0.0f;
}

bool platform_should_terminate() {
    return glfwWindowShouldClose(window);
}

void platform_clear_display() {
    // Render
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
}

void platform_update_display() {
    glfwSwapBuffers(window);
}

void platform_terminate() {
    glfwTerminate();
}