#include "diodes.h"
#include "pico/stdlib.h"

#define LIGHT_RED_PIN 14

void light_red_on(void)
{
    gpio_init(LIGHT_RED_PIN);
    gpio_set_dir(LIGHT_RED_PIN, GPIO_OUT);
    gpio_put(LIGHT_RED_PIN, 1);
}