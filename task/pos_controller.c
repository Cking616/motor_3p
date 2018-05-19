/*
 * pos_controller.c
 *
 *  Created on: 2018Äê5ÔÂ18ÈÕ
 *      Author: cking
 */
#include "pos_controller.h"
#include "speed_controller.h"
#include "../bsp/encoder.h"

volatile pos_controller_state pos_state;

void pos_controller_init()
{
    pos_state.kp = 0.0039;
    //pos_state.kp2 = 0.0045;
    pos_state.ki = 0.000042;
    pos_state.kd = 0.00021;
    pos_state.last_err = 0;
    pos_state.last_speed = 0;
    pos_state.target_pos = speed_controller_get_encoder();
    pos_state.max_speed = 22;
}

inline void pos_controller_set_pos(int pos)
{
    pos_state.target_pos = pos;
}

inline int  pos_controller_get_encoder()
{
    return speed_controller_get_encoder();
}

inline void pos_controller_set_max_speed(int max_speed)
{
    pos_state.max_speed = max_speed;
}

void pos_controller_period()
{
    static float a = 0.676;
    float speed =  pos_state.last_speed;
    int err = pos_state.target_pos - encoder_get_value();
    int abs_err = err > 0? err: -err;
    if(abs_err > 500)
    {
        speed = pos_state.kp * err + pos_state.kd * (err - pos_state.last_err);
    }
    else if(abs_err > 10 && abs_err <= 500)
    {
        //speed = pos_state.kp  * pos_state.last_err;
        float increase = pos_state.ki * err +  pos_state.kp * (err - pos_state.last_err);
        speed = speed + increase;
    }
    else
    {
        speed = 0;
    }

    speed = a * speed + (1 - a) * pos_state.last_speed;
    if(speed > pos_state.max_speed)
        speed =  pos_state.max_speed;
    if(speed < -pos_state.max_speed)
        speed =  -pos_state.max_speed;
    speed_controller_set_speed(speed);
    pos_state.last_speed = speed;
    pos_state.last_err = err;
}

void pos_controller_print()
{

}
