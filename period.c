/*
 * period.c
 *
 *  Created on: 2018Äê5ÔÂ15ÈÕ
 *      Author: cking
 */
#include <stdbool.h>
#include <stdint.h>
#include "bsp/driver.h"
#include "task/blinky.h"
#include "task/cmdpool.h"
#include "task/speed_controller.h"
#include "task/pos_controller.h"
#include "utils/uartstdio.h"


int _testspeed[5] = {5, 20, 25, 15, 5};
int _testi = 0;
int _tick = 0;
volatile unsigned int _tick_second = 0;

// period: 1ms
inline void on_sys_period(void)
{
    speed_controller_period();

    if(_tick % 5 == 1)
    {
        //cmd_thread(driver_get_address());
        pos_controller_period();
    }

    if(_tick % 500 == 1)
    {
        speed_controller_print();
    }

    if(_tick == 999)
    {
        _tick = 0;

        blinky_thread();

        _tick_second++;
        //if(_tick_second % 4 == 1)
        //{
            //_testi = (_testi + 1) % 5;
            //speed_controller_set_speed(_testspeed[_testi]);
        //}

        UARTprintf("Tick Time!\n");
    }
    else
    {
        _tick++;
    }
}

void SysTickIntHandler(void)
{
    on_sys_period();
}

