#include "speaker.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>
#include "hardware/timer.h"

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

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