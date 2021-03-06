/*
 * speed_controller.h
 *
 *  Created on: 2018��4��25��
 *      Author: Administrator
 */

#ifndef SPEED_CONTROLLER_H_
#define SPEED_CONTROLLER_H_

#include <stdint.h>
#include <stdbool.h>

#define PID_PERIOD_TIME 1 // unit: ms

// speed close loop use ki and kp
typedef struct
{
    float       kp;
    float       ki;
    //float       kd;

    int         last_encoder; // 4000 pulse per round

    int         target_speed; // unit: rpm / 4 ;max: 300 rpm => (300 / 60 * 4000) pulse per millosecond = 20 pulse / ms
    int         rel_speed;
    int         rel_speed2;
    int         last_err;

    float       last_pwm;   // pwm , max: 200
}speed_controller_state;

void speed_controller_init();
void speed_controller_set_speed(int speed);
inline int  speed_controller_get_speed();
inline int  speed_controller_get_encoder();
void speed_controller_period();
void speed_controller_print();

#endif /* speed_controller_H_ */
