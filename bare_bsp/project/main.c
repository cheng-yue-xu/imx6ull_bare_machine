#include "clk.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "int.h"
#include "beep.h"
#include "exit.h"
#include "imx6ull.h"

int main(void)
{   
    int_init();
    clk_init();
    clk_enable();
    led_init();
    beep_init();
    exit_init();
    while(1)
    {
        led_on();
        delay_ms(1000);
        led_off();
        delay_ms(1000);
    }
    return 0;
}