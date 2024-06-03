#ifndef MOTOR_H
#define MOTOR_H


#define MOTOR_PWM_PIN 16
#define MOTOR_CW_PIN 17
#define MOTOR_ACW_PIN 18


extern uint32_t motor_move(uint slice_num, uint chan, uint32_t freq, int speed);
extern void init_h_bridge(int ACW_PIN, int CW_PIN, int PWM_PIN);

#endif