#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

void clk_init(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;
}

void gpio_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0x10B0);
    GPIO1->GDIR = 0x8;
    GPIO1->DR = 0x0; 
}

void delay(volatile unsigned int n)
{
    while (n--)
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
int main(void)
{
    clk_init();
    gpio_init();

    while(1)
    {
        GPIO1->DR ^= (1 << 3);
        delay_ms(500);
    }
}