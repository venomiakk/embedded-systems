#ifndef DIODES_H
#define DIODES_H

#include <stdint.h>

extern void init_pwm_led(void);
extern void set_pwm_led(uint16_t value);
extern void diode_14_mode(int mode);
extern void initi_diodes(void);

#endif // DIODES_H