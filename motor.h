#ifndef motor_h
#define motor_h

uint32_t motor_move(uint slice_num, uint chan, uint32_t freq, int speed);
void init_h_bridge(int ACW_PIN, int CW_PIN, int PWM_PIN);

#endif