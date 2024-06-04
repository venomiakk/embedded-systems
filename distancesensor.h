#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include <stdint.h>

#define ECHO 21
#define TRIG 20

/**
 * @brief Inicjalizacja pinów ECHO i TRIG dla czujnika odległości
 */
extern void init_distance_sensor(void);

/**
 * @brief Mierzenie odległości na podstawie czasu trwania wysokiego impulsu na pinie ECHO
 * @return Odleglosc [m], w przypadku zbyt dlugiego czasu oczekiwania -1
 */
extern float get_distance(void);

#endif // DISTANCESENSOR_H