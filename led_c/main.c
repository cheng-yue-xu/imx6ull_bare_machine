#include "main.h"

void clock_init(void){
    CCM_CCGR0 = 0xffffffff;
    CCM_CCGR1 = 0xffffffff;
    CCM_CCGR2 = 0xffffffff;
    CCM_CCGR3 = 0xffffffff;
    CCM_CCGR4 = 0xffffffff;
    CCM_CCGR5 = 0xffffffff;
    CCM_CCGR6 = 0xffffffff;
}

void gpio_init(void){
    SW_MUX_CTL_PAD_GPIO1_IO03_CTL = 0X5;
    SW_PAD_CTL_PAD_GPIO1_IO03_CTL = 0X10B0;
    GPIO1_GDIR = 0X8;
    GPIO1_DR = 0X0;
}

void delay(volatile unsigned int n)
{
    while(n--)
    {    
    }
}

void delay_ms(volatile unsigned int n)
{
    while(n--)
    {
        delay(0x7ff);
    }
}

int main(void){
    clock_init();
    gpio_init();
    while(1){
        GPIO1_DR &= ~(1<<3);
        delay_ms(500);
        GPIO1_DR |= (1<<3);
        delay_ms(500);
    }
    return 0;
}
    


