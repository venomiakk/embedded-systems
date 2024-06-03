#ifndef DIODES_H
#define DIODES_H

#include <stdint.h>

#define DIODE_7 7   // 330 Ohm
#define DIODE_22 22 // 330 Ohm

/*!
 *  @brief    Inicjalizacja i ustawienie PWM dla diody LED
 *  @side effects:
 *            efekty uboczne
 */
extern void init_pwm_led(void);

/*!
 *  @brief    Ustawienie jasności diody LED porzez wypełnienie sygnału PWM (0-500)
 *  @side effects:
 *            efekty uboczne
 */
extern void set_pwm_led(uint16_t value);

/*!
 *  @brief    Inicjalizacja GPIO dla diody LED
 *  @side effects:
 *            efekty uboczne
 */
extern void diode_22_mode(int mode);

/*!
 *  @brief    Wlacz/Wylacz diode LED
 *  @side effects:
 *            efekty uboczne
 */
extern void init_diode22(void);

#endif // DIODES_H