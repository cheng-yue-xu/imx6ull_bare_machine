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
