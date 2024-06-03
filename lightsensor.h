#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <stdint.h>

#define LIGHT_SENSOR_PIN 26

/**
 * @brief Inicjalizacja pinu ADC dla czujnika światła
 * @side effects:
 */
extern void init_light_sensor(void);

/**
 * @brief Odczytanie surowej wartości z czujnika światła
 * @return Wartosc natezenia swiatla
 */
extern uint16_t get_light_value(void);

#endif // LIGHTSENSOR_H