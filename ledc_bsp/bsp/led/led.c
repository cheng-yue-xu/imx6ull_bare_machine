#include "led.h"
void led_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0x10B0);
    GPIO1->GDIR = 0x8;
    GPIO1->DR = 0x0; 
}
void led_on(void)
{
    GPIO1->DR &= ~(1<<3);
}
void led_off(void)
{
    GPIO1->DR |= (1<<3);
}
void led_swich(int led,int status)
{
    switch (status)
    {
    case LED0:
        if(status == ON)
            GPIO1->DR &= ~(1<<3);
        else if(status == OFF)
            GPIO1->DR |= (1<<3);
        break;
    }
}