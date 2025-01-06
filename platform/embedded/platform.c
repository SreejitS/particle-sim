#include "platform.h"
#include "display.h"
#include "pico/rand.h"

bool platform_init() {
    display_init();
    srand( get_rand_32() );
    return true;
}

void platform_poll_events() {
}

float platform_get_time() {
    return 1.00;
}

void platform_draw_particle(Particle* p) {
    display_point(p->x, p->y);
}

void platform_update_global_acceleration(float *ax, float *ay) {
}

bool platform_should_terminate() {
    return false;
}

void platform_clear_display() {
}

void platform_update_display() {
}

void platform_terminate() {
}