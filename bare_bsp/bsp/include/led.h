#ifndef __LED_H__
#define __LED_H__

#include "imx6ull.h"

#define     LED0    0
void led_init(void);
void led_on(void);
void led_off(void);
void led_swich(int led,int status);
#endif







