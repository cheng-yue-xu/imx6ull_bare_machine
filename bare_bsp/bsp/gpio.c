#include "gpio.h"

void gpio_init(GPIO_Type *base,int pin,gpio_pin_config_t *config)
{
    if(config->direction == kGPIO_DigitalOutput)
    {
        base->GDIR |= (1<<pin);
        gpio_pin_write(base,pin,config->outputLogic);
    }
    else if(config->direction == kGPIO_DigitalInput)
    {
        base->GDIR &= ~(1<<pin);
    }
    gpio_intconfig(base,pin,config->interruptMode);
}

void gpio_pin_write(GPIO_Type *base,int pin,int value)
{
    if(value == 0)
    {
        base->DR &= ~(1<<pin);
    }
    else
    {
        base->DR |= (1<<pin);
    }
}

int gpio_pin_read(GPIO_Type *base,int pin)
{
    return (((base->DR)>>pin) & 0x1);
}

void gpio_interrupt_enable(GPIO_Type *base,int pin)
{
    base->IMR |= (1<<pin);
}

void gpio_interrupt_disable(GPIO_Type *base,int pin)
{
    base->IMR &= ~(1<<pin);
}

void gpio_clearintflags(GPIO_Type *base,int pin)
{
    base->ISR |= (1<<pin);
}

void gpio_intconfig(GPIO_Type *base,int pin,gpio_interrupt_mode_t mode)
{   
    volatile u32 *icr;
    u32 icrshift = pin;
    base->EDGE_SEL &= ~(1<<pin);
    if(pin<16)
    {
        icr = &(base->ICR1);
    }
    else
    {
        icr = &(base->ICR2);
    }
    switch (mode)
    {
        case kGPIO_IntLowLevel:
            *icr &= ~(3<<(2*icrshift));
            break;
        case kGPIO_IntHighLevel:
            *icr &= ~(3<<(2*icrshift));
            *icr |= (1<<(2*icrshift));
            break;
        case kGPIO_IntFallingEdge:
            *icr &= ~(3<<(2*icrshift));
            *icr |= (2<<(2*icrshift));
            break;
        case kGPIO_IntRisingEdge:
            *icr &= ~(3<<(2*icrshift));
            *icr |= (2<<(2*icrshift));
            break;
        case kGPIO_IntBothEdges:
            base->EDGE_SEL |= (1<<pin);
            break;
        default:
            break;
    }
    
}