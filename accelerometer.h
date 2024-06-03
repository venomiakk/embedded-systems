#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <stdint.h>

// Definicje I2C i ADXL345
#define I2C_PORT i2c0
#define SDA_PIN 4
#define SCL_PIN 5
#define ADXL345_ADDR 0x53

// Rejestry ADXL345
#define ADXL345_REG_DEVID 0x00
#define ADXL345_REG_POWER_CTL 0x2D
#define ADXL345_REG_DATA_FORMAT 0x31
#define ADXL345_REG_DATAX0 0x32

// Rejestry i dane do kalibracji
#define ADXL345_REG_OFSX 0x1E
#define ADXL345_REG_OFSY 0x1F
#define ADXL345_REG_OFSZ 0x20
#define X_OFFSET -1
#define Y_OFFSET 1
#define Z_OFFSET -8

extern void init_i2c0(void);
extern void init_adxl345(void);
static void i2c_write_reg(uint8_t reg, uint8_t value);
static void i2c_read_reg(uint8_t reg, uint8_t *buf, uint8_t len);
extern void adxl345_read_data(float *x, float *y, float *z);

/**
 * @brief   Kalibracja akcelerometru
 * @side effects:
 */
static void adxl345_calibrate(void);

#endif // ACCELEROMETER_H