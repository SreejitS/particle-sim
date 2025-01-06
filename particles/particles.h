#ifndef PARTICLES_H
#define PARTICLES_H

#include <math.h>  // For sqrtf
#include <stdlib.h> // For rand()

/**
 * @def NUM_OF_PARTICLES
 * Number of particles in the simulation.
 */
#define NUM_OF_PARTICLES 10

/**
 * @struct Particle
 * @brief Structure representing a single particle in the simulation.
 * 
 * This structure stores the physical properties of a particle, including
 * its position, velocity, acceleration, and radius.
 */
typedef struct {
    float x, y;    /**< Position of the particle (x, y). */
    float vx, vy;  /**< Velocity of the particle (vx, vy). */
    float ax, ay;  /**< Acceleration of the particle (ax, ay). */
    float radius;  /**< Radius of the particle. */
} Particle;

/**
 * @brief Initializes a particle with random values for position, velocity, and acceleration.
 * 
 * This function assigns random values to the particle's position and velocity
 * within a certain range. The acceleration is set to simulate gravity-like behavior.
 *
 * @param p Pointer to the Particle to be initialized.
 */
void particle_init(Particle* p);

/**
 * @brief Updates the position and velocity of a particle based on its acceleration.
 * 
 * This function updates the velocity and position of the particle using basic
 * kinematic equations. Reflective boundary conditions are also applied.
 *
 * @param p Pointer to the Particle to be updated.
 * @param dt Time step (delta time) for the update.
 */
void particle_update(Particle* p, float dt);

/**
 * @brief Checks and resolves collisions between two particles.
 * 
 * This function checks if two particles are colliding based on their distance.
 * If a collision occurs, their velocities are updated according to the physics
 * of elastic collisions and the coefficient of restitution.
 *
 * @param p1 Pointer to the first particle.
 * @param p2 Pointer to the second particle.
 * @param restitution The coefficient of restitution (0 = perfectly inelastic, 1 = elastic).
 */
void particle_check_collision(Particle* p1, Particle* p2, float restitution);

#endif // PARTICLES_H
