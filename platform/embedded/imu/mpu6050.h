#ifndef MPU6050_H
#define MPU6050_H

/**
 * @file mpu6050.h
 * @brief Header file for MPU6050 IMU functions.
 *
 * This file contains the function declarations for initializing and reading data from the MPU6050 IMU.
 */

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initialize the IMU.
 *
 * This function initializes the MPU6050 IMU for use.
 *
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int mpu6050_init();

/**
 * @brief Read data from the IMU.
 *
 * This function reads the current data from the MPU6050 IMU.
 *
 * @param[out] x Pointer to a float where the X-axis data will be stored.
 * @param[out] y Pointer to a float where the Y-axis data will be stored.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int mpu6050_read(float *x, float *y);

#endif // MPU6050_H