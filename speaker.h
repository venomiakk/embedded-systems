#ifndef SPEAKER_H
#define SPEAKER_H

#include "pico/stdlib.h"

extern void init_pwm_speaker(void);

extern void play_tone(float frequency, uint32_t duration_ms);

extern void dst_warning(void);

extern void play_melody(void);

#endif
