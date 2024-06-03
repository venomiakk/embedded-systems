#ifndef SERVO_H
#define SERVO_H

#define SERVO_PIN 15


static float clockDiv = 64.0f;
static float wrap = 39062.0f;

extern void setMillis(int servoPin, float millis);
extern void setServo(int servoPin, float startMillis);

#endif