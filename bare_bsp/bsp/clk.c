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
    unsigned int reg = 0;
        /* 1、设置ARM内核时钟为792MHz */
        /* 1.1、判断当前ARM内核是使用的那个时钟源启动的，正常情况下ARM内核是由pll1_sw_clk驱动的，而
        *      pll1_sw_clk有两个来源：pll1_main_clk和tep_clk。
        *      如果我们要让ARM内核跑到792M的话那必须选择pll1_main_clk作为pll1的时钟源。
        *      如果我们要修改pll1_main_clk时钟的话就必须先将pll1_sw_clk从pll1_main_clk切换到step_clk,
        *		当修改完pll1_main_clk以后在将pll1_sw_clk切换回pll1_main_clk。而step_clk的时钟源可以选择
        * 		板子上的24MHz晶振。
        */
        
        if((((CCM->CCSR) >> 2) & 0x1 ) == 0) 	/* 当前pll1_sw_clk使用的pll1_main_clk*/
        {	
            CCM->CCSR &= ~(1 << 8);				/* 配置step_clk时钟源为24MH OSC */	
            CCM->CCSR |= (1 << 2);				/* 配置pll1_sw_clk时钟源为step_clk */
        }

        /* 1.2、设置pll1_main_clk为792MHz
        *      因为pll1_sw_clk进ARM内核的时候会被二分频！
        *      配置CCM_ANLOG->PLL_ARM寄存器
        *      bit13: 1 使能时钟输出
        *      bit[6:0]: 66, 由公式：Fout = Fin * div_select / 2.0，792=24*div_select/2.0,
        *              		得出：div_select=    66 
        */
        CCM_ANALOG->PLL_ARM = (1 << 13) | ((66 << 0) & 0X7F); 	/* 配置pll1_main_clk=792MHz */
        CCM->CCSR &= ~(1 << 2);									/* 将pll_sw_clk时钟重新切换回pll1_main_clk */
        CCM->CACRR = 0;											/* ARM内核时钟为pll1_sw_clk/1=792/1=792Mhz */

        /* 2、设置PLL2(SYS PLL)各个PFD */
        reg = CCM_ANALOG->PFD_528;
        reg &= ~(0X3F3F3F3F);		/* 清除原来的设置 						*/
        reg |= 32<<24;				/* PLL2_PFD3=528*18/32=297Mhz 	*/
        reg |= 24<<16;				/* PLL2_PFD2=528*18/24=396Mhz(DDR使用的时钟，最大400Mhz) */
        reg |= 16<<8;				/* PLL2_PFD1=528*18/16=594Mhz 	*/
        reg |= 27<<0;				/* PLL2_PFD0=528*18/27=352Mhz  	*/
        CCM_ANALOG->PFD_528=reg;	/* 设置PLL2_PFD0~3 		 		*/

        /* 3、设置PLL3(USB1)各个PFD */
        reg = 0;					/* 清零   */
        reg = CCM_ANALOG->PFD_480;
        reg &= ~(0X3F3F3F3F);		/* 清除原来的设置 							*/
        reg |= 19<<24;				/* PLL3_PFD3=480*18/19=454.74Mhz 	*/
        reg |= 17<<16;				/* PLL3_PFD2=480*18/17=508.24Mhz 	*/
        reg |= 16<<8;				/* PLL3_PFD1=480*18/16=540Mhz		*/
        reg |= 12<<0;				/* PLL3_PFD0=480*18/12=720Mhz	 	*/
        CCM_ANALOG->PFD_480=reg;	/* 设置PLL3_PFD0~3 					*/	

        /* 4、设置AHB时钟 最小6Mhz， 最大132Mhz (boot rom自动设置好了可以不用设置)*/
        CCM->CBCMR &= ~(3 << 18); 	/* 清除设置*/ 
        CCM->CBCMR |= (1 << 18);	/* pre_periph_clk=PLL2_PFD2=396MHz */
        CCM->CBCDR &= ~(1 << 25);	/* periph_clk=pre_periph_clk=396MHz */
        while(CCM->CDHIPR & (1 << 5));/* 等待握手完成 */
            
        CCM->CBCDR &= ~(7 << 10);	/* CBCDR的AHB_PODF清零 */
        CCM->CBCDR |= 2 << 10;		/* AHB_PODF 3分频，AHB_CLK_ROOT=132MHz */
        while(CCM->CDHIPR & (1 << 1));
        
        /* 5、设置IPG_CLK_ROOT最小3Mhz，最大66Mhz (boot rom自动设置好了可以不用设置)*/
        CCM->CBCDR &= ~(3 << 8);	/* CBCDR的IPG_PODF清零 */
        CCM->CBCDR |= 1 << 8;		/* IPG_PODF 2分频，IPG_CLK_ROOT=66MHz */
        
        /* 6、设置PERCLK_CLK_ROOT时钟 */
        CCM->CSCMR1 &= ~(1 << 6);	/* PERCLK_CLK_ROOT时钟源为IPG */
        CCM->CSCMR1 &= ~(7 << 0);	/* PERCLK_PODF位清零，即1分频 */
        
        /* 7、设置UART时钟 */
        CCM->CSCDR1 &= ~(1 << 6);
        CCM->CSCDR1 &= ~(0x3f << 0);
}