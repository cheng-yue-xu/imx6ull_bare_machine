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
    u32 reg = 0;
    if(!(CCM->CCSR & (1<<2)))
    {
        CCM->CCSR &= ~(1<<8);
        CCM->CCSR |= (1<<2);
    }
    // arm pll set
    CCM_ANALOG->PLL_ARM |= (1<<13);
    CCM_ANALOG->PLL_ARM &= ~(0x7f);
    CCM_ANALOG->PLL_ARM |= 88; //arm pll set output = 24*divider/2
    CCM->CACRR |= 0x1;           //设置arm pll为2分频
    CCM->CCSR &= ~(1<<2);
    
    //设置pll2的4路pfd
    reg = 0;
    reg = CCM_ANALOG->PFD_528;
    reg &= ~(0x3f|(0x3f<<8)|(0x3f<<16)|(0x3f<<24));
    reg |= (27|(16<<8)|(24<<16)|(32<<24));
    CCM_ANALOG->PFD_528 = reg;
    
    //设置pll3的4路pfd
    reg = 0;
    reg = CCM_ANALOG->PFD_480;
    reg &= ~(0x3f|(0x3f<<8)|(0x3f<<16)|(0x3f<<24));
    reg |= (12|(16<<8)|(17<<16)|(19<<24));
    CCM_ANALOG->PFD_480 = reg;
    
    //AHB
    reg = CCM->CBCMR;
    reg &= ~(3<<18);
    reg |= (1<<18);
    CCM->CBCMR = reg;

    reg = CCM->CBCDR;
    reg &= ~(1<<25);
    CCM->CBCDR = reg;
    while(CCM->CDHIPR & (1<<5));

    reg = CCM->CBCDR;
    reg &= ~(7<<10);
    reg |= (2<<10);
    CCM->CBCDR = reg;
    while (CCM->CDHIPR & (1<<1));
    //IPGCLK
    reg = CCM->CBCDR;
    reg &= ~(3<<8);
    reg |= (1<<8);
    CCM->CBCDR = reg;
    //PERCLK
    reg = CCM->CSCMR1;
    reg &= ~(1<<6);
    reg &= ~(0x3f);
    CCM->CSCMR1 = reg;
}