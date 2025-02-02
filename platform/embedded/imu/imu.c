#include "imu.h"
#include <stdio.h>

// Initialize the IMU
int imu_init() {
    mpu6050_init();
}

// Read data from the IMU
int imu_read( float *x, float *y ) {
    mpu6050_read( x, y );
}
