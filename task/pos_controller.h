/*
 * pos_controller.h
 *
 *  Created on: 2018Äê5ÔÂ18ÈÕ
 *      Author: cking
 */

#ifndef TASK_POS_CONTROLLER_H_
#define TASK_POS_CONTROLLER_H_

// pos close loop use kd and kp,ki;
typedef struct
{
    float       kp;
    float       kp2;
    float       ki;
    float       kd;

    //int         last_encoder; // 4000 pulse per round
    int         target_pos;
    int         last_err;
    //int         last_err2;
    int         max_speed;   //unit: rpm / 4 ;300 rpm => (300 / 60 * 4000) pulse per millosecond = 20 pulse / ms
    float       max_acc;
    float       last_speed;
}pos_controller_state;

void pos_controller_init();
inline void pos_controller_set_pos(int pos);
inline int  pos_controller_get_encoder();
inline void pos_controller_set_max_speed(int max_speed);
void pos_controller_period();
void pos_controller_print();



#endif /* TASK_POS_CONTROLLER_H_ */
