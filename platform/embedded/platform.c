#include "platform.h"

bool platform_init() {
    return true;
}

void platform_poll_events() {
}

float platform_get_time() {
    return 1.00;
}

void platform_draw_particle(Particle* p) {
}

void platform_update_global_acceleration(float *ax, float *ay) {
}

bool platform_should_terminate() {
    return true;
}

void platform_clear_display() {
}

void platform_update_display() {
}

void platform_terminate() {
}