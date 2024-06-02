#include "diodes.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define DIODE_7 7 // 330 Ohm
uint16_t wrap = 500;

void init_pwm_led(void)
{
    gpio_init(DIODE_7);
    gpio_set_function(DIODE_7, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(DIODE_7);
    uint chan = pwm_gpio_to_channel(DIODE_7);

    pwm_set_wrap(slice_num, wrap);
    pwm_set_enabled(slice_num, true);
}

void set_pwm_led(uint16_t value)
{
    uint slice_num = pwm_gpio_to_slice_num(DIODE_7);
    uint chan = pwm_gpio_to_channel(DIODE_7);

    pwm_set_chan_level(slice_num, chan, value);
}

void initi_diodes(void)
{
    gpio_init(DIODE_7);
    gpio_set_dir(DIODE_7, GPIO_OUT);
    gpio_put(DIODE_7, 0);
}

void diode_14_mode(int mode)
{
    gpio_put(DIODE_7, mode);
}