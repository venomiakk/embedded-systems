#include "lightsensor.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

void init_light_sensor(void)
{
    adc_init();
    adc_gpio_init(LIGHT_SENSOR_PIN);
    adc_select_input(0);
}

uint16_t get_light_value()
{
    uint16_t light_value = adc_read();
    return light_value;
}
