#include "clk.h"

void clk_enable(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;
}

void clk_init(void)
{
    if(!(CCM->CCSR & (1<<2)))
    {
        CCM->CCSR &= ~(1<<8);
        CCM->CCSR |= (1<<2);
    }
    CCM_ANALOG->PLL_ARM |= (1<<13);
    CCM_ANALOG->PLL_ARM &= ~(0x7f);
    CCM_ANALOG->PLL_ARM |= 0X58;
    CCM->CACRR |= 0x1;
    CCM->CCSR &= ~(1<<2);
}