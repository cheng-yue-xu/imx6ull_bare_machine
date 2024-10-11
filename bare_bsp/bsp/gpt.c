#include "gpt.h"
#include "int.h"
#include "led.h"
void gpt_init(unsigned int frac,unsigned int value)
{
    if(frac>4095)
        frac=4095;
    GPT1->CR = 0;
    GPT1->CR |= (1<<1) | (1<<6) ;
    GPT1->PR = (frac-1);
    GPT1->OCR[0] = 0;
    GPT1->OCR[0] |= (value);
    GPT1->IR = (1<<0);
    GIC_EnableIRQ(GPT1_IRQn);
    system_register_irqhandler(GPT1_IRQn,gpt_irqhandler,NULL);
}

void gpt_enable(void)
{
    GPT1->CR |= (1<<0);
}

void gpt_disable(void)
{
    GPT1->CR &= ~1;
}
void gpt_irqflagclear(void)
{
    GPT1->SR |= 1;
}
void gpt_irqhandler(unsigned int gicciar,void *param)
{
    static unsigned int status = 1;
    if(status)
    {
        led_on();
        status = 0;
    }
    else
    {
        led_off();
        status = 1;
    }
    gpt_irqflagclear();
}