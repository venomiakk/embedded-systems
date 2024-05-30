#include "diodes.h"
#include "pico/stdlib.h"

#define DIODE_14 14 // 330Ohm

void initialize_diodes(void)
{
    gpio_init(DIODE_14);
    gpio_set_dir(DIODE_14, GPIO_OUT);
    gpio_put(DIODE_14, 0);
}

void diode_14_mode(int mode)
{
    gpio_put(DIODE_14, mode);
}