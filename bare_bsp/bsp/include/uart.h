#ifndef __UART_H_
#define __UART_H_

#include "imx6ull.h"
void uart_disable(UART_Type *base);
void uart_enable(UART_Type *base);
void uart_reset(UART_Type *base);
void uart_config(UART_Type *base);
void uart_init(void);
void putc(unsigned char c);
unsigned char getc(void);
void puts(char *str);
void uart_setbaudrate(UART_Type *base, unsigned int baudrate, unsigned int srcclock_hz);
void raise(int sig_nr);
#endif