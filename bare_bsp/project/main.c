#include "clk.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "main.h"

int main(void)
{
    clk_init();
    clk_enable();
    led_init();
    key_init();
    while(1)
    {
        led_on();
        delay_ms(1000);
        led_off();
        delay_ms(1000);
    }
    return 0;
}