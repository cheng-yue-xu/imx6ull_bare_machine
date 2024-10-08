#ifndef __GPIO_H__
#define __GPIO_H__

#include "imx6ull.h"

typedef enum _gpio_pin_direction
{
    kGPIO_DigitalInput = 0U,
    kGPIO_DigitalOutput = 1U
}gpio_pin_direction_t;

typedef enum _gpio_interrupt_mode
{
    kGPIO_NoIntmode = 0U,
    kGPIO_IntLowLevel = 1U,
    kGPIO_IntHighLevel = 2U,
    kGPIO_IntRisingEdge = 3U,
    kGPIO_IntFallingEdge = 4U,
    kGPIO_IntBothEdges = 5U
}gpio_interrupt_mode_t;

typedef struct _gpio_pin_config
{
    gpio_pin_direction_t direction;
    uint8_t outputLogic;
    gpio_interrupt_mode_t interruptMode;
}gpio_pin_config_t;

void gpio_init(GPIO_Type *base,int pin,gpio_pin_config_t *config);
void gpio_pin_write(GPIO_Type *base,int pin,int value);
int gpio_pin_read(GPIO_Type *base,int pin);
void gpio_interrupt_enable(GPIO_Type *base,int pin);
void gpio_interrupt_disable(GPIO_Type *base,int pin);
void gpio_clearintflags(GPIO_Type *base,int pin);
void gpio_intconfig(GPIO_Type *base,int pin,gpio_interrupt_mode_t mode);

#endif