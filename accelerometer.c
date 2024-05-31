#include "accelerometer.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

void init_i2c0(void)
{
    // Inicjalizacja I2C
    i2c_init(I2C_PORT, 400 * 1000); // 400 kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);

    // Dzieki temu nie trzeba uzywac rezystorow podciagajacych
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

void init_adxl345(void)
{
    // Ustawienie trybu pracy
    i2c_write_reg(ADXL345_REG_POWER_CTL, 0x08); // Measure mode
    // Ustawienie formatu danych
    i2c_write_reg(ADXL345_REG_DATA_FORMAT, 0x08); // Full resolution, +/-2g
    // Kalibracja akcelerometru
    adxl345_calibrate();
}

void i2c_write_reg(uint8_t reg, uint8_t value)
{
    uint8_t buf[2] = {reg, value};
    i2c_write_blocking(I2C_PORT, ADXL345_ADDR, buf, 2, false);
}

void i2c_read_reg(uint8_t reg, uint8_t *buf, uint8_t len)
{
    i2c_write_blocking(I2C_PORT, ADXL345_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, ADXL345_ADDR, buf, len, false);
}

void adxl345_read_data(float *x, float *y, float *z)
{
    int16_t raw_x, raw_y, raw_z;
    uint8_t buf[6];
    i2c_read_reg(ADXL345_REG_DATAX0, buf, 6);
    raw_x = ((int16_t)buf[1] << 8) | buf[0];
    raw_y = ((int16_t)buf[3] << 8) | buf[2];
    raw_z = ((int16_t)buf[5] << 8) | buf[4];
    *x = (float)raw_x / 256.0;
    *y = (float)raw_y / 256.0;
    *z = (float)raw_z / 256.0;
}

void adxl345_calibrate(void)
{
    // Kalibracja
    i2c_write_reg(ADXL345_REG_OFSX, X_OFFSET);
    i2c_write_reg(ADXL345_REG_OFSY, Y_OFFSET);
    i2c_write_reg(ADXL345_REG_OFSZ, Z_OFFSET);
}
