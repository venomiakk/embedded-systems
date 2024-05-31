#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <stdint.h>
// GPIO_PIN_26

void measure_light(void);
extern void init_light_sensor(void);
extern uint16_t get_light_value(void);

#endif // LIGHTSENSOR_H