#ifndef SPEAKER_H
#define SPEAKER_H

#include "pico/stdlib.h"



#define SPEAKER_PIN 2

static const int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

static const int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4};

extern void init_pwm_speaker(void);

static void play_tone(float frequency);

extern void dst_warning1(void);
extern void dst_warning2(void);

extern void play_melody(void);

extern void play_tone_timer(float frequency, uint32_t duration_ms);

static void disable_pwm(uint slice_num);

static bool timer_callback(repeating_timer_t *rt);

#endif
