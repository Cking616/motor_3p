#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "bsp/driver.h"
#include "bsp/delay.h"
#include "task/pos_controller.h"
#include "task/distance.h"
#include "task/speed_controller.h"
#include "utils/uartstdio.h"

int _i = 1;
int g_target_encoder = 0;
// you should change position like this.
// move to 20000, a = 2
void test_pos(int _tick)
{
     if(_tick < 50)
     {
         g_target_encoder = g_target_encoder + 2 * _tick;
         pos_controller_set_pos(g_target_encoder);
     }
     else if(_tick >= 50 && _tick < 200)
     {
         g_target_encoder = g_target_encoder + 100;
         pos_controller_set_pos(g_target_encoder);
     }
     else if(_tick >= 200 && _tick <= 250)
     {
         g_target_encoder = g_target_encoder + 2 * (250 - _tick);
         pos_controller_set_pos(g_target_encoder);
     }
}

void test_pos2(int _tick)
{
    if(_tick < 100)
    {
        g_target_encoder = g_target_encoder - 2 * _tick;
        pos_controller_set_pos(g_target_encoder);
    }
    else if(_tick >= 100 && _tick < 400)
    {
        g_target_encoder = g_target_encoder - 200;
        pos_controller_set_pos(g_target_encoder);
    }
    else if(_tick >= 400 && _tick <= 500)
    {
        g_target_encoder = g_target_encoder - 2 * (500 - _tick);
        pos_controller_set_pos(g_target_encoder);
    }
}

int main()
{
    driver_init_hardware();

    driver_init_system();
    speed_controller_init();
    pos_controller_init();
    UARTprintf("\n\nInit System!\n");
    UARTprintf("Address:%d!\n", driver_get_address());
    driver_start_tick();
    //pos_controller_set_pos(-5000);
    //test_pos();
    while(1)
    {
        distance_thread();

        if(_i <= 250)
        {
            test_pos(_i);
        }

        if(_i >= 550 && _i <= 1050)
        {
            test_pos2(_i - 550);
        }


        if(_i >= 1350 && _i <= 1600)
        {
            test_pos(_i - 1350);
        }

        if(_i >= 1900 && _i <= 2150)
        {
            test_pos(_i - 1900);
        }

        if(_i >= 2450 && _i <= 2700)
        {
            test_pos(_i - 2450);
        }

        if(_i == 3000)
        {
            _i = 1;
        }

        delay_ms(10);
        _i ++;
    }
    return 1;
}
