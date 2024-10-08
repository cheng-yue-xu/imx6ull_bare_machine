#include "exit.h"

void exit_init(void)
{
    gpio_pin_config_t config;
    config.direction = kGPIO_DigitalInput;
    config.interruptMode = kGPIO_IntFallingEdge;
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18,0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0xf080);
    gpio_init(GPIO1,18,&config);
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn,default_irqhandler,NULL);
    gpio_interrupt_enable(GPIO1,18);
}

void exit_handler(unsigned int gicciar,void *userparam)
{
    
}