#include "speaker.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>

#define SPEAKER_PIN 13
uint16_t PWM_RANGE = 65535;

void init_pwm_speaker(void)
{
    gpio_set_function(SPEAKER_PIN, GPIO_FUNC_PWM);
    // slice: 0-7
    uint slice_num = pwm_gpio_to_slice_num(SPEAKER_PIN);
    // channel: A-B [0-1]
    uint channel_num = pwm_gpio_to_channel(SPEAKER_PIN);

    pwm_set_enabled(slice_num, true);
    pwm_set_wrap(slice_num, PWM_RANGE);
}

void play_tone(float frequency, uint32_t duration_ms)
{
    (void)printf("playing %f Hz\n", frequency);
    uint slice_num = pwm_gpio_to_slice_num(SPEAKER_PIN);
    uint channel_num = pwm_gpio_to_channel(SPEAKER_PIN);

    // Ustaw dzielnik częstotliwości PWM
    pwm_set_clkdiv(slice_num, 125.0f);
    // Oblicz okres sygnału PWM
    uint32_t period_us = (uint32_t)(1.0f / frequency * 1000000);
    // Ustaw okres sygnału PWM
    pwm_set_wrap(slice_num, period_us);
    // Ustaw poziom sygnału PWM
    pwm_set_chan_level(slice_num, channel_num, period_us / 2);
    // Poczekaj przez czas trwania tonu
    // sleep_ms(duration_ms);
    // ! tego nie powinno sie chyba uzywac
    busy_wait_ms(duration_ms);
    // Wyłącz sygnał PWM
    pwm_set_chan_level(slice_num, channel_num, 0);
}