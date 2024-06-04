#include "diodes.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

static const uint16_t wrap = 595;

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

void init_diode22(void)
{
    gpio_init(DIODE_22);
    gpio_set_dir(DIODE_22, GPIO_OUT);
    gpio_put(DIODE_22, 0);
}

void diode_22_mode(int mode)
{
    gpio_put(DIODE_22, mode);
}