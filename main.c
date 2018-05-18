#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "bsp/driver.h"
#include "bsp/delay.h"
#include "task/pos_controller.h"
#include "task/distance.h"
#include "task/speed_controller.h"
#include "utils/uartstdio.h"

// you should change position like this.
void test_pos()
{
     int cur_encoder = 0;
     pos_controller_set_pos(cur_encoder - 2000);
     //wait about 10ms until the next reading.
     delay_ms(150);
     pos_controller_set_pos(cur_encoder - 3000);
     delay_ms(150);
     pos_controller_set_pos(cur_encoder - 5000);
     delay_ms(150);
     pos_controller_set_pos(cur_encoder - 7000);
     delay_ms(300);
     pos_controller_set_pos(cur_encoder - 12000);
     delay_ms(150);
     pos_controller_set_pos(cur_encoder - 15000);
     delay_ms(150);
     pos_controller_set_pos(cur_encoder - 17000);
     delay_ms(150);
     pos_controller_set_pos(cur_encoder - 18000);
     delay_ms(150);
     pos_controller_set_pos(cur_encoder - 19000);
     delay_ms(150);
     pos_controller_set_pos(cur_encoder - 20000);
     delay_s(2);

     pos_controller_set_pos(cur_encoder - 15000);
     //wait about 10ms until the next reading.
     delay_ms(150);
     pos_controller_set_pos(cur_encoder - 12000);
     delay_ms(150);
     pos_controller_set_pos(cur_encoder - 7000);
     delay_ms(300);
     pos_controller_set_pos(cur_encoder - 5000);
     delay_ms(300);
     pos_controller_set_pos(cur_encoder - 3000);
     delay_ms(150);
     pos_controller_set_pos(cur_encoder - 2000);
     delay_ms(150);
     pos_controller_set_pos(cur_encoder);
     delay_s(2);
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
    while(1)
    {
        distance_thread();

        //Prints out the distance measured.
        //UARTprintf("dis: %2dcm \n" , distance_get_dis());
        //pos_controller_set_pos(0 - 15000);
        test_pos();
        delay_ms(10);
    }
    return 1;
}
