#include "lightsensor.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define LIGHT_SENSOR_PIN 26

void measure_light()
{
    adc_init();
    adc_gpio_init(LIGHT_SENSOR_PIN);
    adc_select_input(0);

    /* //TODO
     *   light_value - im wiecej tym ciemniej
     *   3000 - od tego momentu mozna zapalic diode
     *   4000 - dioda na maksa
     */

    while (true)
    {
        uint16_t light_value = adc_read();
        (void)printf("%d\n", light_value);
        sleep_ms(1000);
    }
}