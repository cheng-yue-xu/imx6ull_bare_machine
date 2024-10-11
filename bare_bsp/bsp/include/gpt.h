#ifndef _GPT_H_
#define _GPT_H_
#include "imx6ull.h"
void gpt_init(unsigned int frac,unsigned int value);
void gpt_enable(void);
void gpt_disable(void);
void gpt_irqflagclear(void);
void gpt_irqhandler(unsigned int gicciar,void *userparam);
#endif