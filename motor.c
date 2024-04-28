#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"

uint32_t motor_move(uint slice_num, uint chan, uint32_t freq, int speed)
{
    
    uint32_t clock = 125000000;
    uint32_t divider16 = clock / freq / 4096 + (clock % (freq * 4096) != 0);
    if (divider16 / 16 == 0)
    divider16 = 16;
    uint32_t wrap = clock * 16 / divider16 / freq - 1;
    pwm_set_clkdiv_int_frac(slice_num, divider16/16, divider16 & 0xF);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, chan, wrap * speed / 100);
    pwm_set_enabled(slice_num,true);
    return wrap;
}

void init_h_bridge(int ACW_PIN, int CW_PIN, int PWM_PIN){
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);
    gpio_set_dir(PWM_PIN, GPIO_OUT);
    uint slice_num=pwm_gpio_to_slice_num (PWM_PIN);
    uint chan=pwm_gpio_to_channel (PWM_PIN);
    pwm_set_enabled(slice_num, true);
    gpio_init(ACW_PIN);
    gpio_init(CW_PIN);
    gpio_set_dir(ACW_PIN, GPIO_OUT);
    gpio_set_dir(CW_PIN, GPIO_OUT);
}