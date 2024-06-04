#include "speaker.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>
#include "hardware/timer.h"



const uint16_t PWM_RANGE = 65535;

void init_pwm_speaker(void)
{
    gpio_set_function(SPEAKER_PIN, GPIO_FUNC_PWM);
    // slice: 0-7
    uint slice_num = pwm_gpio_to_slice_num(SPEAKER_PIN);
    // channel: A-B [0-1]
    uint channel_num = pwm_gpio_to_channel(SPEAKER_PIN);

    // pwm_set_enabled(slice_num, true);
    pwm_set_wrap(slice_num, PWM_RANGE);
}

void play_tone(float frequency)
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
    pwm_set_enabled(slice_num, true);
}

void play_tone_timer(float frequency, uint32_t duration_ms)
{
    uint slice_num = pwm_gpio_to_slice_num(SPEAKER_PIN);
    play_tone(frequency);
    repeating_timer_t timer;
    add_repeating_timer_ms(-duration_ms, timer_callback, &slice_num, &timer);
    sleep_ms(duration_ms + 30);
}

void disable_pwm(uint slice_num)
{
    pwm_set_enabled(slice_num, false);
}

bool timer_callback(repeating_timer_t *rt)
{
    disable_pwm(*(uint *)rt->user_data);
    return false;
}

void dst_warning1(void)
{
    play_tone_timer(NOTE_C4, 100);
    sleep_ms(100);
    play_tone_timer(NOTE_E4, 100);
    sleep_ms(100);
    play_tone_timer(NOTE_C4, 100);
}

void dst_warning2(void)
{
    play_tone_timer(NOTE_C6, 50);
    play_tone_timer(NOTE_E6, 50);
    sleep_ms(100);
    play_tone_timer(NOTE_C6, 50);
    play_tone_timer(NOTE_E5, 50);
}

void play_melody()
{
    for (int i = 0; i < 8; i++)
    {
        int noteDuration = 1000 / noteDurations[i];
        play_tone_timer(melody[i], noteDuration);
    }
}