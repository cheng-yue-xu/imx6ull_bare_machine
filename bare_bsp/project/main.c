#include "clk.h"
#include "led.h"
#include "int.h"
#include "epit.h"
#include "exit.h"
#include "beep.h"
#include "imx6ull.h"

int main(void)
{   
    int_init();
    clk_init();
    clk_enable();
    led_init();
    beep_init();
    exit_init();
    epit_init(659,1000);
    while(1)
    {
    }
    return 0;
}