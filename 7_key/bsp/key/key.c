#include "key.h"
#include "delay.h"
#include "gpio.h"

void key_init(void)
{
    gpio_pin_config_t config;
    config.direction = kGPIO_DigitalInput;
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18,0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0xf080);
    gpio_init(GPIO1,18,&config);
}

int key_scan(void)
{
    if(gpio_pin_read(GPIO1,18))
        return 0;
    else
        return 1;
}

int key_read(void)
{
    static int curr = 0;
    if((curr == 0)&&(key_scan()))
    {
        delay_ms(10);
        if(key_scan()){
            curr =1;
        }
    }
    else if((curr == 1)&&(!key_scan()))
    {
        delay_ms(10);
        if(!key_scan()){
            curr =0;
        }
    }
    else
    {
        curr = key_scan();
    }
    return curr;
}