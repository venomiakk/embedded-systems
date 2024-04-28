#ifndef SERVO_H
#define SERVO_H

static float clockDiv = 64;
static float wrap = 39062;

extern void setMillis(int servoPin, float millis);
extern void setServo(int servoPin, float startMillis);

#endif