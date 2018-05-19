#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "bsp/driver.h"
#include "bsp/delay.h"
#include "task/pos_controller.h"
#include "task/distance.h"
#include "task/speed_controller.h"
#include "utils/uartstdio.h"

int _i = 0;
// you should change position like this.
// move to 20000, a = 2
void test_pos()
{
     int cur_encoder = pos_controller_get_encoder();
     if(_i < 50)
     {
         pos_controller_set_pos(_i * _i);
     }
     else if(_i >= 50 && _i < 200)
     {
         pos_controller_set_pos(_i * 100 - 2500);
     }
     else if(_i >= 200 && _i < 250)
     {
         pos_controller_set_pos(500 * _i -_i * _i - 42500);
     }
     else
     {
         pos_controller_set_pos(20000);
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
    //pos_controller_set_pos(-5000);
    //test_pos();
    while(1)
    {
        distance_thread();

        //Prints out the distance measured.
        //UARTprintf("dis: %2dcm \n" , distance_get_dis());
        //pos_controller_set_pos(0 - 15000);
        test_pos();
        delay_ms(10);
        _i ++;
    }
    return 1;
}
