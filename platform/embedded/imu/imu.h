#ifndef IMU_H
#define IMU_H

/**
 * @brief Initialize the IMU sensor.
 * 
 * @return int 0 if initialization was successful, non-zero otherwise.
 */
int IMU_Init(void);

/**
 * @brief Get the current IMU data.
 * 
 * @param x Pointer to store the x-axis acceleration.
 * @param y Pointer to store the y-axis acceleration.
 * @return int 0 if data retrieval was successful, non-zero otherwise.
 */
int IMU_GetData(float *x, float *y);

#endif // IMU_H