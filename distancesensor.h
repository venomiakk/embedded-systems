#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include <stdint.h>

#define ECHO 21
#define TRIG 20

extern void init_distance_sensor(void);
extern float get_distance(void);

#endif // DISTANCESENSOR_H