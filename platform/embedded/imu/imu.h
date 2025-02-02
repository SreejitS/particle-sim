#ifndef IMU_H
#define IMU_H

#include "mpu6050.h"

/**
 * @brief Initialize the IMU sensor.
 * 
 * @return int 0 if initialization was successful, non-zero otherwise.
 */
int imu_init(void);

/**
 * @brief Get the current IMU data.
 * 
 * @param x Pointer to store the x-axis acceleration.
 * @param y Pointer to store the y-axis acceleration.
 * @return int 0 if data retrieval was successful, non-zero otherwise.
 */
int imu_read(float *x, float *y);

#endif // IMU_H