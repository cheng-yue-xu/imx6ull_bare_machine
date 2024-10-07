#ifndef __KEY_H__
#define __KEY_H__

#include "imx6ull.h"

void key_init(void);
int key_scan(void);
int key_read(void);

#endif