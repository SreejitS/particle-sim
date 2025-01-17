#include "platform.h"
#include "display.h"
#include "mpu6050.h"
#include "pico/rand.h"
#include "pico/stdlib.h"

bool platform_init() {
    display_init();
    srand( get_rand_32() );
    imu_init();
    return true;
}

void platform_poll_events() {
}

float platform_get_time() {
    return time_us_64() / 1000000.0f;
}

void platform_draw_particle(Particle* p) {
    display_point(p->x, p->y);
}

void platform_update_global_acceleration(float *ax, float *ay) {
    imu_read(ax, ay);
}

bool platform_should_terminate() {
    return false;
}

void platform_clear_display() {
    display_clear();
}

void platform_update_display() {
    display_update();
}

void platform_terminate() {
}