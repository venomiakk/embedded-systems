#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_PWM_PIN 18
#define MOTOR_CW_PIN 17
#define MOTOR_ACW_PIN 16

/**
 * @brief Uruchomienie silnika
 * @param slice_num Numer kanalu PMW [0-7]
 * @param chan Numer kanalu PWM [A-B]
 * @param freq Czestotliwosc PWM
 * @param speed Wypelnienie
 * @return
 */
extern uint32_t motor_move(uint slice_num, uint chan, uint32_t freq, int speed);
/**
 * @brief Inicjalizacja mostak H
 * @param ACW_PIN Kierunek obrotu zgodnie z ruchem wskazowek zegara
 * @param CW_PIN Kiernunek obrotu przeciwnie do ruchu wskazowek zegara
 * @param PWM_PIN Pin PWM
 */
extern void init_h_bridge(int ACW_PIN, int CW_PIN, int PWM_PIN);

#endif