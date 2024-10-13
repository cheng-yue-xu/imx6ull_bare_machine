#include "clk.h"
#include "led.h"
#include "int.h"
#include "epit.h"
#include "exit.h"
#include "gpt.h"
#include "delay.h"
#include "beep.h"
#include "uart.h"
#include "imx6ull.h"
#include "stdio.h"

int main(void)
{   
	int a , b;
    int_init();
    clk_init();
    clk_enable();
    uart_init();
    led_init();
    unsigned char c = 0;
    while(1)
    {   
        printf("输入两个整数，使用空格隔开:");
		scanf("%d %d", &a, &b);					 		/* 输入两个整数 */
		printf("\r\n数据%d + %d = %d\r\n\r\n", a, b, a+b);	/* 输出两个数相加的和 */
    }
    return 0;
}