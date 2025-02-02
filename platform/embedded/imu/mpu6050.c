#include "mpu6050.h"
#include "imu.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

/* Example code to talk to a MPU6050 MEMS accelerometer and gyroscope

   This is taking to simple approach of simply reading registers. It's perfectly
   possible to link up an interrupt line and set things up to read from the
   inbuilt FIFO to make it more useful.

   NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Pico
   GPIO (and therefore I2C) cannot be used at 5v.

   You will need to use a level shifter on the I2C lines if you want to run the
   board at 5v.

*/


// By default these devices  are on bus address 0x68
static int addr = 0x68;

#define MPU6050_I2C_SDA_PIN    16      // GP16 for SDA
#define MPU6050_I2C_SCL_PIN    17      // GP17 for SCL

#define BUFFER_SIZE             6
#define ACCEL_SIZE              3

static void mpu6050_reset() {
    // Two byte reset. First byte register, second byte data
    // There are a load more options to set up the device in different ways that could be added here
    uint8_t buf[] = {0x6B, 0x80};
    i2c_write_blocking(i2c0, addr, buf, 2, false);
    sleep_ms(100); // Allow device to reset and stabilize

    // Clear sleep mode (0x6B register, 0x00 value)
    buf[1] = 0x00;  // Clear sleep mode by writing 0x00 to the 0x6B register
    i2c_write_blocking(i2c0, addr, buf, 2, false); 
    sleep_ms(10); // Allow stabilization after waking up
}

static void mpu6050_read_raw(int16_t accel[3]) {
    // For this particular device, we send the device the register we want to read
    // first, then subsequently read from the device. The register is auto incrementing
    // so we don't need to keep sending the register we want, just the first.

    uint8_t buffer[3 * 2]; // 3 16-bit values

    // Start reading acceleration registers from register 0x3B for 6 bytes
    uint8_t val = 0x3B;
    i2c_write_blocking(i2c0, addr, &val, 1, true); // true to keep master control of bus
    i2c_read_blocking(i2c0, addr, buffer, 6, false);

    for (int i = 0; i < 3; i++) {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

}

int mpu6050_init() {
    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c0, 400 * 1000);
    gpio_set_function(MPU6050_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(MPU6050_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(MPU6050_I2C_SDA_PIN);
    gpio_pull_up(MPU6050_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(MPU6050_I2C_SDA_PIN, MPU6050_I2C_SCL_PIN, GPIO_FUNC_I2C));

    mpu6050_reset();

}

int mpu6050_read(float *x, float *y) {
    int16_t accel[3];
    mpu6050_read_raw(accel);

    // convert to -1.0 to 1.0 range
    *y = (float)accel[0] / 4098.0f;
    *x = (float)accel[1] / 4098.0f;

    
}