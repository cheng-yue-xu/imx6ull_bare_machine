#include "clk.h"
#include "led.h"
#include "int.h"
#include "epit.h"
#include "exit.h"
#include "gpt.h"
#include "delay.h"
#include "beep.h"
#include "imx6ull.h"

int main(void)
{   
    int_init();
    clk_init();
    clk_enable();
    delay_init();	
    led_init();
    while(1)
    {   
        led_on();
        delay_ms(10000);
        led_off();
        delay_ms(10000);
    }
    return 0;
}