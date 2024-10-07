#ifndef __KEY_H__
#define __KEY_H__

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

void key_init(void);
int key_scan(void);
int key_read(void);

#endif