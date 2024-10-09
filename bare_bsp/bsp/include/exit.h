#ifndef __EXIT_H__
#define __EXIT_H__
#include "imx6ull.h"
void exit_handler(unsigned int gicciar,void *userparam);
void exit_init(void);
#endif
