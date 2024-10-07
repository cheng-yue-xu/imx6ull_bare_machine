#include "delay.h"

void delay(volatile unsigned int n)
{
    while(n--)
    {
    }
}

void delay_ms(volatile unsigned int n)
{
    while(n--)
    {
        delay(0x7ff);
    }
}