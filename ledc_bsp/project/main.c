#include "main.h"
#include "led.h"
#include "clk.h"
#include "delay.h"


int main(void)
{
    clk_init();
    led_init();

    while(1)
    {
        led_on();
        delay_ms(5000);
        led_off();
        delay_ms(5000);
    }
}