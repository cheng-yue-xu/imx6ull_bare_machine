#ifndef __EPIT_H__
#define __EPIT_H__

#include "imx6ull.h"
void epit_init(unsigned int frac,unsigned int value);
void epit_enable(void);
void epit_disable(void);
void epit_irqflagclear(void);
void epit_irqhandler(unsigned int gicciar,void *param);
#endif