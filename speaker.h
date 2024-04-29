#ifndef SPEAKER_H
#define SPEAKER_H

#include "pico/stdlib.h"

//GPIO_PIN_13

void init_pwm_speaker(void);

void play_tone(float frequency, uint32_t duration_ms);

#endif
