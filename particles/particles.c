#include "particles.h"

void initialize_particle(Particle* p) {
    p->x = (float)(rand() % 200 - 100) / 100.0f; // Random x between -1.0 and 1.0
    p->y = (float)(rand() % 200 - 100) / 100.0f; // Random y between -1.0 and 1.0
    p->vx = (float)(rand() % 200 - 100) / 100.0f; // Random velocity
    p->vy = (float)(rand() % 200 - 100) / 100.0f; // Random velocity
    p->ax = 0.0f;  // No acceleration by default
    p->ay = -0.1f; // Gravity-like acceleration
    p->radius = 0.025f; // Fixed radius for all particles
}

void update_particle(Particle* p, float dt) {
    // Update velocity using acceleration
    p->vx += p->ax * dt;
    p->vy += p->ay * dt;

    // Update position using velocity
    p->x += p->vx * dt;
    p->y += p->vy * dt;

    // Reflective boundary conditions
    if (p->x > 1.0f - p->radius || p->x < -1.0f + p->radius) {
        p->vx = -p->vx;
        p->x = (p->x > 1.0f - p->radius) ? (1.0f - p->radius) : (-1.0f + p->radius);
    }
    if (p->y > 1.0f - p->radius || p->y < -1.0f + p->radius) {
        p->vy = -p->vy;
        p->y = (p->y > 1.0f - p->radius) ? (1.0f - p->radius) : (-1.0f + p->radius);
    }
}

void check_collision(Particle* p1, Particle* p2, float restitution) {
    // Calculate distance between two particles
    float dx = p1->x - p2->x;
    float dy = p1->y - p2->y;
    float distance = sqrtf(dx * dx + dy * dy);

    // Check for collision
    if (distance < (p1->radius + p2->radius)) {
        // Calculate normalized collision vector
        float nx = dx / distance;
        float ny = dy / distance;

        // Calculate relative velocity
        float dvx = p1->vx - p2->vx;
        float dvy = p1->vy - p2->vy;

        // Calculate relative velocity along the normal
        float dot = dvx * nx + dvy * ny;

        // Only proceed if particles are moving toward each other
        if (dot < 0) {
            // Apply the coefficient of restitution (energy loss factor)
            float impulse = 2.0f * dot / (p1->radius + p2->radius);

            // Modify the velocities based on the restitution factor
            p1->vx -= impulse * p2->radius * nx * restitution;
            p1->vy -= impulse * p2->radius * ny * restitution;
            p2->vx += impulse * p1->radius * nx * restitution;
            p2->vy += impulse * p1->radius * ny * restitution;
        }
    }
}

