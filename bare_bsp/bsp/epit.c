#include "epit.h"
#include "int.h"
#include "led.h"
#include "gpio.h"
#include "beep.h"
void epit_init(unsigned int frac,unsigned int value)
{
    if(frac > 4095)
        frac = 4095;
    EPIT1->CR = 0;
    EPIT1->CR = (1<<1) | (1<<2) | (1<<3)\
                | (frac<<4) |(1<<24);
    EPIT1->LR = value;
    EPIT1->CMPR = 0;
    GIC_EnableIRQ(EPIT1_IRQn);
    system_register_irqhandler(EPIT1_IRQn,epit_irqhandler,NULL);
}
void epit_enable(void)
{
    EPIT1->CR |= 1;
}
void epit_disable(void)
{
    EPIT1->CR &= ~1;
}
void epit_irqflagclear(void)
{
    EPIT1->SR |= 1;
}

void epit_irqhandler(unsigned int gicciar,void *param)
{
    epit_disable();
    if(gpio_pin_read(GPIO1,18) == 0)
    {
        beep_ring();
    }
    else
    {
        beep_stop();
    }

    epit_irqflagclear();
    
}