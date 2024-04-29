#include "irsensor.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>

#define IR_SENSOR_PIN 14

void binary_detection()
{
    gpio_init(IR_SENSOR_PIN);
    gpio_set_dir(IR_SENSOR_PIN, GPIO_IN);
    while (true)
    {
        int is_detected = gpio_get(IR_SENSOR_PIN);
        (void)printf("%d\n", is_detected);
        sleep_ms(1000);
    }
}