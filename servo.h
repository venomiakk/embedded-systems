#ifndef SERVO_H
#define SERVO_H

#define SERVO_PIN 15

static float clockDiv = 64.0f;
static float wrap = 39062.0f;

/**
 * @brief Ustawienie wartosci dla serwa
 * @param servoPin Pin serwa
 * @param millis Wartosc obrotu w milisekundach
 */
extern void setMillis(int servoPin, float millis);

/**
 * @brief Ustawienie wartosci PMW dla serwa
 * @param servoPin Pin serwa 
 * @param startMillis poczatkowa wartosc obrotu w milisekundach
 */
extern void setServo(int servoPin, float startMillis);

#endif