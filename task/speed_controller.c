/*
 * speed_controller.c
 *
 *  Created on: 2018Äê4ÔÂ25ÈÕ
 *      Author: Administrator
 */

#include "speed_controller.h"
#include "../bsp/encoder.h"
#include "../bsp/drv8308.h"
#include "utils/uartstdio.h"

#define MOTOR_MAX_SPEED 199

volatile speed_controller_state pid_state;

void speed_controller_init()
{
    pid_state.kp = 1.728f;
    pid_state.ki = 0.0724f;

    pid_state.last_encoder = encoder_get_value();
    pid_state.target_speed = 0;
    pid_state.last_pwm = 0;
    pid_state.rel_speed = 0;
    pid_state.last_err = 0;

    drv8308_set_brake(1);
    drv8308_set_pwm(0);
}

void speed_controller_period()
{
    static float a = 0.725f;
    float cur_pwm = 0.0f;
    int out_pwm = 0;
    int cur_encoder = encoder_get_value();
    pid_state.rel_speed = cur_encoder - pid_state.last_encoder;
    pid_state.rel_speed2 = encoder_get_speed();

    int err = pid_state.target_speed - pid_state.rel_speed;

    float increse = pid_state.kp * (err - pid_state.last_err)
                    + pid_state.ki * err;

    cur_pwm = pid_state.last_pwm + increse;

    if( cur_pwm > MOTOR_MAX_SPEED)
    {
        cur_pwm = MOTOR_MAX_SPEED;
    }

    if( cur_pwm < -MOTOR_MAX_SPEED)
    {
        cur_pwm = -MOTOR_MAX_SPEED;
    }

    cur_pwm = cur_pwm * a + pid_state.last_pwm * (1 - a);

    pid_state.last_pwm = cur_pwm;

    if ( cur_pwm > 0 )
    {
        out_pwm = cur_pwm;
        drv8308_set_dir(MOTOR_DIR_CW);
    }
    else
    {
        out_pwm = - cur_pwm;
        drv8308_set_dir(MOTOR_DIR_CCW);
    }

    if(out_pwm != 0 )
    {
        drv8308_set_brake(0);
    }

    drv8308_set_pwm(out_pwm);

    if(pid_state.target_speed == 0 && pid_state.rel_speed == 0)
    {
        drv8308_set_brake(1);
        pid_state.last_pwm = 0;
    }

    pid_state.last_encoder = cur_encoder;
    pid_state.last_err = err;
}

inline void speed_controller_set_speed(int speed)
{
    if(pid_state.target_speed == speed )
    {
        return;
    }

    /*
    if(pid_state.target_speed == 0 || pid_state.target_speed * speed < 0)
    {
        if(speed > 0)
        {
            pid_state.last_pwm = 10;
        }
        else
        {
            pid_state.last_pwm = -10;
        }
    }
    */
    pid_state.target_speed = speed;
}

inline int  speed_controller_get_encoder()
{
    return pid_state.last_encoder;
}

inline int  speed_controller_get_speed()
{
    return pid_state.rel_speed2;
}

void speed_controller_print()
{
    int pwm = pid_state.last_pwm;
    UARTprintf("Pid:\nS:%d,ts:%d,E:%d,PWM:%d,err:%d\n", pid_state.rel_speed,pid_state.target_speed,pid_state.last_encoder,pwm,pid_state.last_err);
}
