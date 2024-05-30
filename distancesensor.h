#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include <stdint.h>
//GPIO 12 - ECHO
//GPIO 13 - TRIG
#define ECHO 12
#define TRIG 13

extern void initialise_distance_sensor(void);
extern float get_distance(void);

#endif //DISTANCESENSOR_H