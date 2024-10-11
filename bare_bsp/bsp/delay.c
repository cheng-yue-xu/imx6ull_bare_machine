#include "delay.h"

void delay_init(void)
{
    GPT1->CR = 0;
    GPT1->CR = 1 << 15;				/* bit15置1进入软复位 				*/
	while((GPT1->CR >> 15) & 0x01);	
    GPT1->CR |= (1<<6);
    GPT1->PR = 65;
	GPT1->OCR[0] = 0XFFFFFFFF;
    GPT1->CR |= (1<<0);
}
void delay_us(unsigned int n)
{
    unsigned long old,new;
    unsigned long value = 0;
    old = GPT1->CNT;
    while(1)
    {
        new = GPT1->CNT;
        if(new != old)
        {
                if(new > old)
            {
                value += new - old;
            }
            else
            {
                value += (0xffffffff - old) + new;
            }
            old = new;
            if(value >= n)
            {
                break;
            }
        }
    }
}

void delay_ms(unsigned int n)
{
    while(n--)
    {
        delay_us(1000);
    }
}