#include "clk.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "main.h"

int main(void)
{
    clk_init();
    led_init();
    key_init();
    while(1)
    {
        if(key_read())
            led_on();
        else
            led_off();
    }
    return 0;
}