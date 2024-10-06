#include "main.h"
#include "beep.h"
#include "clk.h"
#include "delay.h"


int main(void)
{
    clk_init();
    beep_init();

    while(1)
    {
        beep_ring();
        delay_ms(100);
        beep_stop();
        delay_ms(1000);
    }
}